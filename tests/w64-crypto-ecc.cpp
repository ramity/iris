#include <iostream>
#include <string>

#include "crypto/ECC.cpp"

int main()
{
    // Config
    std::string message = "Hello, world!";

    // Init
    ECC ecc = ECC();
    ecc.set_public_key_path("C:\\Users\\ramit\\Downloads\\data\\public_key");
    ecc.set_private_key_path("C:\\Users\\ramit\\Downloads\\data\\private_key");
    ecc.generate_keys();
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
    ecc.write_keys();
    ECC ecc2 = ECC();
    ecc2.set_public_key_path("C:\\Users\\ramit\\Downloads\\data\\public_key");
    ecc2.set_private_key_path("C:\\Users\\ramit\\Downloads\\data\\private_key");
    ecc2.read_keys();
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
    ecc3.generate_keys();
    ECC ecc4 = ECC();
    ecc4.set_seed(seed);
    ecc4.generate_keys();

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
    ecc3.generate_keys();
    ecc4.generate_keys();

    std::cout << ecc3.get_encoded_public_key() << std::endl << std::endl;
    std::cout << ecc4.get_encoded_public_key() << std::endl << std::endl;

    if (ecc3.get_raw_public_key() != ecc4.get_raw_public_key())
    {
        std::cout << "[-] Failed seeded key generation test" << std::endl;
        return 1;
    }


    // Keep prompt open
    std::cout << "Press Enter to exit...";
    std::cin.get();

    return 0;
}
