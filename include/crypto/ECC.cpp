#ifndef __ECC_CPP__
#define __ECC_CPP__

#include "ECC.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <cryptopp/sha.h>
#include <cryptopp/files.h>

ECC::ECC():
    output_sink(this->output),
    encoder(new CryptoPP::Redirector(this->output_sink), false),
    decoder(new CryptoPP::Redirector(this->output_sink)),
    hasher(this->hash_method, new CryptoPP::Redirector(this->output_sink))
{
    // Config
    this->set_public_key_path("/root/iris/data/public_key");
    this->set_private_key_path("/root/iris/data/private_key");
    this->curve = CryptoPP::ASN1::secp521r1();
    this->output = "";
}

ECC::ECC(std::string public_key_path, std::string private_key_path):
    output_sink(this->output),
    encoder(new CryptoPP::Redirector(this->output_sink), false),
    decoder(new CryptoPP::Redirector(this->output_sink)),
    hasher(this->hash_method, new CryptoPP::Redirector(this->output_sink))
{
    // Config
    this->set_public_key_path(public_key_path);
    this->set_private_key_path(private_key_path);
    this->curve = CryptoPP::ASN1::secp521r1();
    this->output = "";
}

ECC::~ECC()
{
    delete this->encryptor;
    delete this->decryptor;
    delete this->signer;
    delete this->verifier;
}

std::string ECC::encode(std::string input)
{
    this->output = "";
    CryptoPP::StringSource(input, true, new CryptoPP::Redirector(this->encoder));
    return this->output;
}

std::string ECC::decode(std::string input)
{
    this->output = "";
    CryptoPP::StringSource(input, true, new CryptoPP::Redirector(this->decoder));
    return this->output;
}

std::string ECC::hash(std::string input)
{
    this->output = "";
    CryptoPP::StringSource(input, true, new CryptoPP::Redirector(this->hasher));
    return this->output;
}

void ECC::set_public_key_path(std::string path)
{
    this->public_key_path = path;
}

void ECC::set_private_key_path(std::string path)
{
    this->private_key_path = path;
}

std::string ECC::get_public_key_path()
{
    return this->public_key_path;
}

std::string ECC::get_private_key_path()
{
    return this->private_key_path;
}

void ECC::set_seed(std::string seed)
{
    std::string hash = this->hash(seed);
    this->set_seed_hash(hash);
}

void ECC::set_seed_hash(std::string hash)
{
    this->use_drng = true;
    int key_size = 32;
    int iv_size = 16;
    std::string key_string = hash.substr(0, key_size);
    std::string iv_string = hash.substr(key_size, iv_size);
    CryptoPP::SecByteBlock key(reinterpret_cast<const CryptoPP::byte *>(key_string.data()), key_size);
    CryptoPP::SecByteBlock iv(reinterpret_cast<const CryptoPP::byte *>(iv_string.data()), iv_size);
    this->drng.SetKeyWithIV(key, key_size, iv, iv_size);
}

void ECC::generate_keypair()
{
    if (this->use_drng)
    {
        this->private_key.Initialize(this->drng, this->curve);
    }
    else
    {
        this->private_key.Initialize(this->prng, this->curve);
    }

    this->private_key.MakePublicKey(this->public_key);
    this->init_keypair_operations();
}

void ECC::read_private_key()
{
    this->output = "";
    std::ifstream private_file(this->private_key_path);
    CryptoPP::FileSource private_source(private_file, true, new CryptoPP::Redirector(this->decoder));
    this->private_key.Load(CryptoPP::StringSource(this->output, true).Ref());
    private_file.close();

    this->init_private_key_operations();
}

void ECC::read_public_key()
{
    this->output = "";
    std::ifstream public_file(this->public_key_path);
    CryptoPP::FileSource public_source(public_file, true, new CryptoPP::Redirector(this->decoder));
    this->public_key.Load(CryptoPP::StringSource(this->output, true).Ref());
    public_file.close();

    this->init_public_key_operations();
}

void ECC::read_keypair()
{
    this->read_private_key();
    this->read_public_key();
}

void ECC::init_private_key_operations()
{
    this->decryptor = new CryptoPP::ECIES<CryptoPP::ECP>::Decryptor(this->private_key);
    this->signer = new CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA512>::Signer(this->private_key);

    this->decryptor_filter = new CryptoPP::PK_DecryptorFilter(
        this->prng,
        *this->decryptor,
        new CryptoPP::Redirector(this->output_sink)
    );
    this->signer_filter = new CryptoPP::SignerFilter(
        this->prng,
        *this->signer,
        new CryptoPP::Redirector(this->output_sink)
    );

    // Convert private_key to all private_key variants
    this->output = "";
    private_key.Save(this->output_sink);
    this->raw_private_key = this->output;
    this->encoded_private_key = this->encode(this->raw_private_key);
    this->raw_private_key_hash = this->hash(this->raw_private_key);
    this->encoded_private_key_hash = this->encode(this->raw_private_key_hash);
}

void ECC::init_public_key_operations()
{
    this->encryptor = new CryptoPP::ECIES<CryptoPP::ECP>::Encryptor(this->public_key);
    this->verifier = new CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA512>::Verifier(this->public_key);

    this->encryptor_filter = new CryptoPP::PK_EncryptorFilter(
        this->prng,
        *this->encryptor,
        new CryptoPP::Redirector(this->output_sink)
    );
    this->verifier_filter = new CryptoPP::SignatureVerificationFilter(
        *this->verifier
    );

    // Convert public_key to all public_key variants
    this->output = "";
    public_key.Save(this->output_sink);
    this->raw_public_key = this->output;
    this->encoded_public_key = this->encode(this->raw_public_key);
    this->raw_public_key_hash = this->hash(this->raw_public_key);
    this->encoded_public_key_hash = this->encode(this->raw_public_key_hash);
}

void ECC::init_keypair_operations()
{
    this->init_private_key_operations();
    this->init_public_key_operations();
}

void ECC::write_private_key()
{
    std::ofstream private_file(this->private_key_path);
    CryptoPP::FileSink private_sink(private_file);
    CryptoPP::Base64Encoder temp_base64_private_key_encoder(new CryptoPP::Redirector(private_sink), false);
    this->private_key.Save(temp_base64_private_key_encoder);
    temp_base64_private_key_encoder.MessageEnd();
    private_file.close();
}

void ECC::write_public_key()
{
    std::ofstream public_file(this->public_key_path);
    CryptoPP::FileSink public_sink(public_file);
    CryptoPP::Base64Encoder temp_base64_public_key_encoder(new CryptoPP::Redirector(public_sink), false);
    this->public_key.Save(temp_base64_public_key_encoder);
    temp_base64_public_key_encoder.MessageEnd();
    public_file.close();
}

void ECC::write_keypair()
{
    this->write_private_key();
    this->write_public_key();
}

void ECC::encrypt()
{
    // Takes raw_plaintext and creates all ciphertext variants

    this->output = "";
    CryptoPP::StringSource(
        this->raw_plaintext,
        true,
        new CryptoPP::Redirector(*this->encryptor_filter)
    );

    this->raw_ciphertext = this->output;    
    this->encoded_ciphertext = this->encode(this->raw_ciphertext);
    this->raw_ciphertext_hash = this->hash(this->raw_ciphertext);
    this->encoded_ciphertext_hash = this->encode(this->raw_ciphertext_hash);
    return;
}

void ECC::decrypt()
{
    // Takes raw_ciphertext and creates all plaintext variants

    this->output = "";
    CryptoPP::StringSource(
        this->raw_ciphertext,
        true,
        new CryptoPP::Redirector(*this->decryptor_filter)
    );

    this->raw_plaintext = output;
    this->encoded_plaintext = this->encode(this->raw_plaintext);
    this->raw_plaintext_hash = this->hash(this->raw_plaintext);
    this->encoded_plaintext_hash = this->encode(this->raw_plaintext_hash);
}

void ECC::sign()
{
    // Takes raw_plaintext_hash and creates all signature variants

    this->output = "";
    CryptoPP::StringSource(
        this->raw_plaintext_hash,
        true,
        new CryptoPP::Redirector(*this->signer_filter) 
    );

    this->raw_signature = this->output;
    this->encoded_signature = this->encode(this->raw_signature);
    this->raw_signature_hash = this->hash(this->raw_signature);
    this->encoded_signature_hash = this->encode(this->raw_signature_hash);
}

bool ECC::verify()
{
    // Takes raw_signature and plaintext_hash and returns validity

    CryptoPP::StringSource(
        this->raw_signature + this->raw_plaintext_hash,
        true,
        new CryptoPP::Redirector(*this->verifier_filter)
    );

    return this->verifier_filter->GetLastResult();
}

// Plaintext
std::string ECC::get_raw_plaintext()
{
    return this->raw_plaintext;
}

std::string ECC::get_encoded_plaintext()
{
    return this->encoded_plaintext;
}

std::string ECC::get_raw_plaintext_hash()
{
    return this->raw_plaintext_hash;
}

std::string ECC::get_encoded_plaintext_hash()
{
    return this->encoded_plaintext_hash;
}

void ECC::set_raw_plaintext(std::string raw_plaintext)
{
    this->raw_plaintext = raw_plaintext;
}

void ECC::set_encoded_plaintext(std::string encoded_plaintext)
{
    this->encoded_plaintext = encoded_plaintext;
}

void ECC::set_raw_plaintext_hash(std::string raw_plaintext_hash)
{
    this->raw_plaintext_hash = raw_plaintext_hash;
}

void ECC::set_encoded_plaintext_hash(std::string encoded_plaintext_hash)
{
    this->encoded_plaintext_hash = encoded_plaintext_hash;
}

// Ciphertext
std::string ECC::get_raw_ciphertext()
{
    return this->raw_ciphertext;
}

std::string ECC::get_encoded_ciphertext()
{
    return this->encoded_ciphertext;
}

std::string ECC::get_raw_ciphertext_hash()
{
    return this->raw_ciphertext_hash;
}

std::string ECC::get_encoded_ciphertext_hash()
{
    return this->encoded_ciphertext_hash;
}

void ECC::set_raw_ciphertext(std::string raw_ciphertext)
{
    this->raw_ciphertext = raw_ciphertext;
}

void ECC::set_encoded_ciphertext(std::string encoded_ciphertext)
{
    this->encoded_ciphertext = encoded_ciphertext;
}

void ECC::set_raw_ciphertext_hash(std::string raw_ciphertext_hash)
{
    this->raw_ciphertext_hash = raw_ciphertext_hash;
}

void ECC::set_encoded_ciphertext_hash(std::string encoded_ciphertext_hash)
{
    this->encoded_ciphertext_hash = encoded_ciphertext_hash;
}

// Signature
std::string ECC::get_raw_signature()
{
    return this->raw_signature;
}

std::string ECC::get_encoded_signature()
{
    return this->encoded_signature;
}

std::string ECC::get_raw_signature_hash()
{
   return this->raw_signature_hash;
}

std::string ECC::get_encoded_signature_hash()
{
   return this->encoded_signature_hash;
}

void ECC::set_raw_signature(std::string raw_signature)
{
    this->raw_signature = raw_signature;
}

void ECC::set_encoded_signature(std::string encoded_signature)
{
    this->encoded_signature = encoded_signature;
}

void ECC::set_raw_signature_hash(std::string raw_signature_hash)
{
   this->raw_signature_hash = raw_signature_hash;
}

void ECC::set_encoded_signature_hash(std::string encoded_signature_hash)
{
   this->encoded_signature_hash = encoded_signature_hash;
}

// Public key
std::string ECC::get_raw_public_key()
{
    return this->raw_public_key;
}

std::string ECC::get_encoded_public_key()
{
    return this->encoded_public_key;
}

std::string ECC::get_raw_public_key_hash()
{
    return this->raw_public_key_hash;
}

std::string ECC::get_encoded_public_key_hash()
{
    return this->encoded_public_key_hash;
}

void ECC::set_raw_public_key(std::string raw_public_key)
{
    this->raw_public_key = raw_public_key;
}

void ECC::set_encoded_public_key(std::string encoded_public_key)
{
    this->encoded_public_key = encoded_public_key;
}

void ECC::set_raw_public_key_hash(std::string raw_public_key_hash)
{
    this->raw_public_key_hash = raw_public_key_hash;
}

void ECC::set_encoded_public_key_hash(std::string encoded_public_key_hash)
{
    this->encoded_public_key_hash = encoded_public_key_hash;
}


// Private key
std::string ECC::get_raw_private_key()
{
    return this->raw_private_key;
}

std::string ECC::get_encoded_private_key()
{
    return this->encoded_private_key;
}

std::string ECC::get_raw_private_key_hash()
{
    return this->raw_private_key_hash;
}

std::string ECC::get_encoded_private_key_hash()
{
    return this->encoded_private_key_hash;
}

void ECC::set_raw_private_key(std::string raw_private_key)
{
    this->raw_private_key = raw_private_key;
}

void ECC::set_encoded_private_key(std::string encoded_private_key)
{
    this->encoded_private_key = encoded_private_key;
}

void ECC::set_raw_private_key_hash(std::string raw_private_key_hash)
{
    this->raw_private_key_hash = raw_private_key_hash;
}

void ECC::set_encoded_private_key_hash(std::string encoded_private_key_hash)
{
    this->encoded_private_key_hash = encoded_private_key_hash;
}

#endif
