#include <iostream>
#include <string>

#include "crypto/ECC.cpp"

// Handle platform specific variations and create get_current_path macro
#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
    #define get_current_path _getcwd
    const char path_separator = '\\';
#else
    #include <unistd.h>
    #define get_current_path getcwd
    const char path_separator = '/';
#endif

int main()
{
    // Setup pathed vars
    char current_path_chars[FILENAME_MAX];
    get_current_path(current_path_chars, sizeof(current_path_chars));
    std::string current_path(current_path_chars);
    std::string data_path = current_path + path_separator + "data";
    std::string public_key_path = data_path + path_separator + "public_key";
    std::string private_key_path = data_path + path_separator + "private_key";

    // Config
    std::string message = "Hello, world!";

    // Init
    ECC ecc = ECC();
    ecc.set_public_key_path(public_key_path);
    ecc.set_private_key_path(private_key_path);
    ecc.generate_keypair();
    ecc.set_raw_plaintext(message);

    // Make sure decryptoed output == message
    ecc.encrypt();
    ecc.decrypt();
    if (ecc.get_raw_plaintext() != message)
    {
        std::cout << "[-] Failed ecc decryption" << std::endl;
        return 1;
    }

    // Sign and verify the plaintext message hash
    ecc.sign();
    if (!ecc.verify())
    {
        std::cout << "[-] Failed verification" << std::endl;
        return 1;
    }

    // Write keys, create new ECC instance, read keys, transfer raw ciphertext, decrypt, check if raw_plaintexts match 
    ecc.write_keypair();
    ECC ecc2 = ECC();
    ecc2.set_public_key_path(public_key_path);
    ecc2.set_private_key_path(private_key_path);
    ecc2.read_keypair();
    ecc2.set_raw_ciphertext(ecc.get_raw_ciphertext());
    ecc2.decrypt();
    if (ecc.get_raw_plaintext() != ecc2.get_raw_plaintext())
    {
        std::cout << "[-] Failed write, read, decrypt, compare test" << std::endl;
        return 1;
    }

    // Verify deterministic key generation
    std::string seed = "Unlimited games but no games";
    ECC ecc3 = ECC();
    ecc3.set_seed(seed);
    ecc3.generate_keypair();
    ECC ecc4 = ECC();
    ecc4.set_seed(seed);
    ecc4.generate_keypair();

    std::cout << ecc3.get_encoded_public_key() << std::endl << std::endl;
    std::cout << ecc4.get_encoded_public_key() << std::endl << std::endl;

    if (ecc3.get_raw_public_key() != ecc4.get_raw_public_key())
    {
        std::cout << "[-] Failed seeded key generation test" << std::endl;
        return 1;
    }

    // Verify deterministic key generation from hash chain
    seed = ecc.hash(seed);
    ecc3.set_seed(seed);
    ecc4.set_seed(seed);
    ecc3.generate_keypair();
    ecc4.generate_keypair();

    std::cout << ecc3.get_encoded_public_key() << std::endl << std::endl;
    std::cout << ecc4.get_encoded_public_key() << std::endl << std::endl;

    if (ecc3.get_raw_public_key() != ecc4.get_raw_public_key())
    {
        std::cout << "[-] Failed seeded key generation test" << std::endl;
        return 1;
    }

    return 0;
}
