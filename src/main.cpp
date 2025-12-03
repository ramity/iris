#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>

#include "crypto/ECC.cpp"

// Define globals
int generation_difficulty = 1000000;
std::string program_name;
char current_path_chars[FILENAME_MAX];
std::string current_path;
std::string default_keys_path;
std::string default_public_key_path;
std::string default_private_key_path;
std::string default_identities_path;
std::vector<std::string> names;
std::vector<std::string *> addresses;

// Handle platform specific variations and create get_current_path macro
#if defined(_WIN32) || defined(_WIN64)
    #include <direct.h>
    #define get_current_path _getcwd
    const char path_separator = '\\';
    #include <windows.h>
#else
    #include <unistd.h>
    #define get_current_path getcwd
    const char path_separator = '/';
    #include <dirent.h>
#endif

void cout_repo_ad()
{
    std::cout << "To get more help with iris, check out the github repo at https://github.com/ramity/iris" << std::endl;
}

void cout_iris_ascii_art()
{
    std::cout << std::endl;
    std::cout << "::::::::::: :::::::::  ::::::::::: :::::::: " << std::endl;
    std::cout << "    :+:     :+:    :+:     :+:    :+:    :+:" << std::endl;
    std::cout << "    +:+     +:+    +:+     +:+    +:+       " << std::endl;
    std::cout << "    +#+     +#++:++#:      +#+    +#++:++#++" << std::endl;
    std::cout << "    +#+     +#+    +#+     +#+           +#+" << std::endl;
    std::cout << "    #+#     #+#    #+#     #+#    #+#    #+#" << std::endl;
    std::cout << "########### ###    ### ########### ######## " << std::endl;
}

void cout_general_help_prompt()
{
    cout_iris_ascii_art();
    std::cout << std::endl;
    std::cout << "Usage: " << program_name << " COMMAND" << std::endl;
    std::cout << std::endl;
    std::cout << "A portable management tool for cryptography operations" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  keypair      Keypair related operations" << std::endl;
    std::cout << "  identity     Identity related operations" << std::endl;
    std::cout << std::endl;
    std::cout << "Run '" << program_name << " COMMAND --help' for more information on a command." << std::endl;
    std::cout << std::endl;
    cout_repo_ad();
}

void cout_keypair_help_prompt()
{
    cout_iris_ascii_art();
    std::cout << std::endl;
    std::cout << "Usage: " << program_name << " keypair COMMAND" << std::endl;
    std::cout << std::endl;
    std::cout << "Description: Keypair related operations" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << std::endl;
    std::cout << "  generate" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "    --seed" << std::endl;
    std::cout << "    --n" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << "    seed" << std::endl;
    std::cout << "    n" << std::endl;
    std::cout << "  - examples:" << std::endl;
    std::cout << "    'Generate the 23rd keypair derived from a master seed':" << std::endl;
    std::cout << "    " << program_name << " keypair generate --private_key_path=" << default_private_key_path << " --public_key_path=" << default_public_key_path << " --seed=UnlimitedGamesButNoGames --n=23" << std::endl;
    std::cout << "    " << program_name << " keypair generate " << default_private_key_path << " " << default_public_key_path << " UnlimitedGamesButNoGames 23" << std::endl;
    std::cout << std::endl;
    std::cout << "  delete" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << std::endl;
    std::cout << "  encrypt" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "    --text" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << "    text" << std::endl;
    std::cout << std::endl;
    std::cout << "  decrypt" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --ciphertext" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    ciphertext" << std::endl;
    std::cout << std::endl;
    std::cout << "  sign" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --text" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    text" << std::endl;
    std::cout << std::endl;
    cout_repo_ad();
}

void cout_identity_help_prompt()
{
    cout_iris_ascii_art();
    std::cout << std::endl;
    std::cout << "Usage: " << program_name << " identity COMMAND" << std::endl;
    std::cout << std::endl;
    std::cout << "Description: Identity related operations" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << std::endl;
    std::cout << "  add" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --path" << std::endl;
    std::cout << "    --public_key" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    path" << std::endl;
    std::cout << "    public_key" << std::endl;
    std::cout << std::endl;
    std::cout << "  remove" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --path" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    path" << std::endl;
    std::cout << std::endl;
    std::cout << "  list" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --path" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    path" << std::endl;
    std::cout << std::endl;
    std::cout << "  verify" << std::endl;
    std::cout << "  - named arguments:" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "    --signature" << std::endl;
    std::cout << "    --message_hash" << std::endl;
    std::cout << "  - ordered arguments:" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << "    signature" << std::endl;
    std::cout << "    message_hash" << std::endl;
    std::cout << std::endl;
    cout_repo_ad();
}

void define_globals(int arg_count, char * arg_values[])
{
    program_name = arg_values[0];
    get_current_path(current_path_chars, sizeof(current_path_chars));
    current_path = current_path_chars;
    default_keys_path = current_path + path_separator + "keys";
    default_public_key_path = default_keys_path + path_separator + "public_key";
    default_private_key_path = default_keys_path + path_separator + "private_key";
    default_identities_path = current_path + path_separator + "identities";
}

std::vector<std::string> ls(std::string path)
{
    std::vector<std::string> files;

    #ifdef _WIN32
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA((path + "/*").c_str(), &findData);
    if (hFind != INVALID_HANDLE_VALUE)
    {
        while (FindNextFileA(hFind, &findData))
        {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                files.push_back(findData.cFileName);
            }
        }
        FindClose(hFind);
    }
    else
    {
        std::cout << "Failed to open " << path << std::endl;
    }

    #else
    DIR * dir = opendir(path.c_str());
    if (dir)
    {
        dirent * entry;
        while ((entry = readdir(dir)) != nullptr)
        {
            if (entry->d_type == DT_REG)
            {
                files.push_back(entry->d_name);
            }
        }
        closedir(dir);
    }
    else
    {
        std::cout << "Failed to open " << path << std::endl;
    }

    #endif
    return files;
}

void process_arguments(int arg_count, char * arg_values[])
{
    // Store size and lengths to save CPU cycles
    int names_size = names.size();
    std::vector<int> name_lengths;
    for (int z = 0; z < names_size; z++)
    {
        name_lengths.push_back(names[z].length());
    }

    // Extract named arguments:
    for (int z = 3; z < arg_count; z++)
    {
        std::string argument = arg_values[z];

        for (int y = 0; y < names_size; y++)
        {
            if (argument.find(names[y]) == 0)
            {
                *addresses[y] = argument.substr(name_lengths[y]);
            }
        }
    }

    // Extract positional arguments w/ precedence to named arguments:
    for (int z = 3; z < arg_count; z++)
    {
        if ((*addresses[z - 3]).empty())
        {
            *addresses[z - 3] = arg_values[z];
        }
    }
}

int main(int arg_count, char * arg_values[])
{
    // Define globals, defaults, and handle platform specific variations
    define_globals(arg_count, arg_values);

    // Check for --help flag
    if (arg_count == 1 || strcmp(arg_values[1], "--help") == 0)
    {
        cout_general_help_prompt();
    }

    // keypair
    else if (strcmp(arg_values[1], "keypair") == 0)
    {
        // Check for --help flag at end of input
        if (strcmp(arg_values[arg_count - 1], "--help") == 0)
        {
            cout_keypair_help_prompt();
        }

        // generate
        else if (strcmp(arg_values[2], "generate") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/positional arguments" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Extract named/positional CLI arguments
            std::string private_key_path;
            std::string public_key_path;
            std::string seed;
            std::string n;
            names.push_back("--private_key_path=");
            names.push_back("--public_key_path=");
            names.push_back("--seed=");
            names.push_back("--n=");
            addresses.push_back(&private_key_path);
            addresses.push_back(&public_key_path);
            addresses.push_back(&seed);
            addresses.push_back(&n);
            process_arguments(arg_count, arg_values);

            // Conditionally perform ops
            ECC ecc = ECC();
            ecc.set_private_key_path(private_key_path);
            ecc.set_public_key_path(public_key_path);
            if (!seed.empty())
            {
                int rounds = std::stoi(n) * generation_difficulty;
                int step = rounds / 100;
                for (int z = 0; z < rounds; z++)
                {
                    seed = ecc.hash(seed);

                    if (z % step == 0)
                        std::cout << "\r" << z / step  << "%" << std::flush;
                }
                std::cout << "\rComplete" << std::endl;
                ecc.set_seed_hash(seed);
            }
            ecc.generate_keypair();
            ecc.write_keypair();
        }

        // delete
        else if (strcmp(arg_values[2], "delete") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/positional arguments" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Extract named/positional CLI arguments
            std::string private_key_path;
            std::string public_key_path;
            names.push_back("--private_key_path=");
            names.push_back("--public_key_path=");
            addresses.push_back(&private_key_path);
            addresses.push_back(&public_key_path);
            process_arguments(arg_count, arg_values);

            // Conditionally perform ops
            if (!private_key_path.empty())
            {
                if (remove(private_key_path.c_str()) == 0)
                {
                    std::cout << "Successfully removed " << private_key_path << std::endl;
                }
                else
                {
                    std::cout << "Failed to remove " << private_key_path << std::endl;
                }
            }
            if (!public_key_path.empty())
            {
                if (remove(public_key_path.c_str()) == 0)
                {
                    std::cout << "Successfully removed " << public_key_path << std::endl;
                }
                else
                {
                    std::cout << "Failed to remove " << public_key_path << std::endl;
                }
            }
        }

        // encrypt
        else if (strcmp(arg_values[2], "encrypt") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/positional arguments" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Extract named/positional CLI arguments
            std::string public_key_path;
            std::string text;
            names.push_back("--public_key_path=");
            names.push_back("--text=");
            addresses.push_back(&public_key_path);
            addresses.push_back(&text);
            process_arguments(arg_count, arg_values);

            // Conditionally perform ops
            if (!public_key_path.empty() && !text.empty())
            {
                ECC ecc = ECC();
                ecc.set_public_key_path(public_key_path);
                ecc.read_public_key();
                ecc.set_raw_plaintext(text);
                ecc.encrypt();
                std::cout << ecc.get_encoded_ciphertext() << std::endl;
            }
        }

        // decrypt
        else if (strcmp(arg_values[2], "decrypt") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/positional arguments" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Extract named/positional CLI arguments
            std::string private_key_path;
            std::string ciphertext;
            names.push_back("--private_key_path=");
            names.push_back("--ciphertext=");
            addresses.push_back(&private_key_path);
            addresses.push_back(&ciphertext);
            process_arguments(arg_count, arg_values);

            // Conditionally perform ops
            if (!private_key_path.empty() && !ciphertext.empty())
            {
                ECC ecc = ECC();
                ecc.set_private_key_path(private_key_path);
                ecc.read_private_key();
                std::string raw_ciphertext = ecc.decode(ciphertext);
                ecc.set_raw_ciphertext(raw_ciphertext);
                ecc.decrypt();
                std::cout << ecc.get_raw_plaintext() << std::endl;
            }
        }

        // sign
        else if (strcmp(arg_values[2], "sign") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/positional arguments" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Extract named/positional CLI arguments
            std::string private_key_path;
            std::string text;
            names.push_back("--private_key_path=");
            names.push_back("--text=");
            addresses.push_back(&private_key_path);
            addresses.push_back(&text);
            process_arguments(arg_count, arg_values);

            // Conditionally perform ops
            if (!private_key_path.empty() && !text.empty())
            {
                ECC ecc = ECC();
                ecc.set_private_key_path(private_key_path);
                ecc.read_private_key();
                std::string text_hash = ecc.hash(ecc.hash(text));
                ecc.set_raw_plaintext_hash(text_hash);
                ecc.sign();
                std::cout << ecc.encode(text_hash) << std::endl;
                std::cout << ecc.get_encoded_signature() << std::endl;
            }
        }

        // incorrect input
        else
        {
            std::cout << "iris keypair '" << arg_values[2] << "' is not an iris command. See 'iris keypair --help'." << std::endl;
            return 1;
        }
    }

    // identity
    else if (strcmp(arg_values[1], "identity") == 0)
    {
        // Check for --help flag at end of input
        if (strcmp(arg_values[arg_count - 1], "--help") == 0)
        {
            cout_identity_help_prompt();
        }

        // add
        else if (strcmp(arg_values[2], "add") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/positional arguments" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Extract named/positional CLI arguments
            std::string path;
            std::string public_key;
            names.push_back("--path=");
            names.push_back("--public_key=");
            addresses.push_back(&path);
            addresses.push_back(&public_key);
            process_arguments(arg_count, arg_values);

            if (path.empty() || public_key.empty())
            {
                std::cout << "Error" << std::endl;
                return 1;
            }

            std::ofstream output_file(path);
            if (output_file.is_open())
            {
                output_file << public_key;
                output_file.close();
                std::cout << "File written successfully" << std::endl;
            }
            else
            {
                std::cout << "Unable to open file" << std::endl;
                return 1;
            }
        }

        // remove
        else if (strcmp(arg_values[2], "remove") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/positional arguments" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Extract named/positional CLI arguments
            std::string path;
            names.push_back("--path=");
            addresses.push_back(&path);
            process_arguments(arg_count, arg_values);

            // Conditionally perform ops
            if (!path.empty())
            {
                if (remove(path.c_str()) == 0)
                {
                    std::cout << "Successfully removed " << path << std::endl;
                }
                else
                {
                    std::cout << "Failed to remove " << path << std::endl;
                }
            }
        }

        // list
        else if (strcmp(arg_values[2], "list") == 0)
        {
            // Extract named/positional CLI arguments
            std::string path;
            names.push_back("--path=");
            addresses.push_back(&path);
            process_arguments(arg_count, arg_values);

            // If not set, fallback to use default identities path
            if (path.empty())
            {
                path = default_identities_path;
            }

            // Handle if no identities are present
            std::vector<std::string> files = ls(path);
            int file_count = files.size();
            if (file_count == 0)
            {
                std::cout << std::endl;
                std::cout << "No identities present in " << path << std::endl;
                std::cout << std::endl;
                return 1;
            }

            // Output tab formatted index filename pairs in path
            std::cout << std::endl;
            std::cout << "Index\tFilename" << std::endl;
            for (int z = 0; z < file_count; z++)
            {
                std::cout << z << '\t' << files[z] << std::endl;
            }
            std::cout << std::endl;
        }

        // verify
        else if (strcmp(arg_values[2], "verify") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/positional arguments" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Extract named/positional CLI arguments
            std::string public_key_path;
            std::string signature;
            std::string message_hash;
            names.push_back("--public_key_path=");
            names.push_back("--signature=");
            names.push_back("--message_hash=");
            addresses.push_back(&public_key_path);
            addresses.push_back(&signature);
            addresses.push_back(&message_hash);
            process_arguments(arg_count, arg_values);

            // Error if required args not met
            if (public_key_path.empty() || signature.empty() ||  message_hash.empty())
            {
                std::cout << "Error" << std::endl;
                return 1;
            }

            ECC ecc = ECC();
            ecc.set_public_key_path(public_key_path);
            ecc.read_public_key();
            ecc.set_raw_signature(
                ecc.decode(signature)
            );
            ecc.set_raw_plaintext_hash(
                ecc.decode(message_hash)
            );
            if (ecc.verify())
            {
                std::cout << "Valid signature" << std::endl;
            }
            else
            {
                std::cout << "Invalid signature" << std::endl;
            }
        }

        // incorrect input
        else
        {
            std::cout << "iris identity '" << arg_values[2] << "' is not an iris command. See 'iris identity --help'." << std::endl;
        }
    }

    // incorrect input
    else
    {
        std::cout << "iris '" << arg_values[1] << "' is not an iris command. See 'iris --help'." << std::endl;
    }

    return 0;
}
