#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>

#include "crypto/ECC.cpp"

// Define globals
int generation_difficulty = 133337;
std::string program_name;
char current_path_chars[FILENAME_MAX];
std::string current_path;
std::string default_keys_path;
std::string default_public_key_path;
std::string default_private_key_path;
std::string default_identities_path;

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
    std::cout << "A portable management tool forcryptography operations" << std::endl;
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
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "    --seed" << std::endl;
    std::cout << "    --n" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
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
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << std::endl;
    std::cout << "  encrypt" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "    --text" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << "    text" << std::endl;
    std::cout << std::endl;
    std::cout << "  decrypt" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --ciphertext" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    ciphertext" << std::endl;
    std::cout << std::endl;
    std::cout << "  sign" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --text" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
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
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --path" << std::endl;
    std::cout << "    --public_key" << std::endl;
    std::cout << "    --n" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    path" << std::endl;
    std::cout << "    public_key" << std::endl;
    std::cout << std::endl;
    std::cout << "  remove" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --path" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    path" << std::endl;
    std::cout << std::endl;
    std::cout << "  list" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --path" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    path" << std::endl;
    std::cout << std::endl;
    std::cout << "  verify" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "    --signature" << std::endl;
    std::cout << "    --message_hash" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
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
        // Check for --help flag
        if (arg_count == 2 || strcmp(arg_values[2], "--help") == 0)
        {
            cout_keypair_help_prompt();
        }

        // generate
        // - named parameters:
        //   --private_key_path
        //   --public_key_path
        //   --seed
        //   --n
        // - ordered parameters:
        //   private_key_path
        //   public_key_path
        //   seed
        //   n
        else if (strcmp(arg_values[2], "generate") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/ordered parameters" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Possible params
            std::string private_key_path;
            std::string public_key_path;
            std::string seed;
            int n = 0;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if (parameter.find("--private_key_path=") == 0)
                {
                    private_key_path = parameter.substr(19);
                }
                else if (parameter.find("--public_key_path=") == 0)
                {
                    public_key_path = parameter.substr(18);
                }
                else if (parameter.find("--seed=") == 0)
                {
                    seed = parameter.substr(7);
                }
                else if (parameter.find("--n=") == 0)
                {
                    n = std::stoi(parameter.substr(4));
                }
            }

            // Check ordered params w/ precedence to named params:
            if (private_key_path.empty() && arg_count > 3)
            {
                private_key_path = arg_values[3];
            }
            if (public_key_path.empty() && arg_count > 4)
            {
                public_key_path = arg_values[4];
            }
            if (seed.empty() && arg_count > 5)
            {
                seed = arg_values[5];
            }
            if (arg_count > 6)
            {
                n = std::atoi(arg_values[6]);
            }

            // Conditionally perform ops
            ECC ecc = ECC();
            if (!private_key_path.empty())
                ecc.set_private_key_path(private_key_path);
            if (!public_key_path.empty())
                ecc.set_public_key_path(public_key_path);
            if (!seed.empty())
            {
                int rounds = n * generation_difficulty;
                int step = rounds / 100;
                for (int z = 0; z < rounds; z++)
                {
                    seed = ecc.hash(seed);

                    if (z % step == 0)
                        std::cout << "\r" << z / step  << "%" << std::flush;
                }
                std::cout << "\rComplete" << std::endl;
                ecc.set_seed(seed);
            }
            ecc.generate_keypair();
            ecc.write_keypair();
        }

        // delete
        // - named parameters:
        //   --private_key_path
        //   --public_key_path
        // - ordered parameters:
        //   private_key_path
        //   public_key_path
        else if (strcmp(arg_values[2], "delete") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/ordered parameters" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Possible params
            std::string private_key_path;
            std::string public_key_path;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if (parameter.find("--private_key_path=") == 0)
                {
                    private_key_path = parameter.substr(19);
                }
                else if (parameter.find("--public_key_path=") == 0)
                {
                    public_key_path = parameter.substr(18);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (private_key_path.empty() && arg_count > 3)
            {
                private_key_path = arg_values[3];
            }
            if (public_key_path.empty() && arg_count > 4)
            {
                public_key_path = arg_values[4];
            }

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
        // - named parameters:
        //   --public_key_path
        //   --text
        // - ordered parameters:
        //   public_key_path
        //   text
        else if (strcmp(arg_values[2], "encrypt") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/ordered parameters" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Possible params
            std::string public_key_path;
            std::string text;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if (parameter.find("--public_key_path=") == 0)
                {
                    public_key_path = parameter.substr(18);
                }
                else if (parameter.find("--text=") == 0)
                {
                    text = parameter.substr(7);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (public_key_path.empty() && arg_count > 3)
            {
                public_key_path = arg_values[3];
            }
            if (text.empty() && arg_count > 4)
            {
                text = arg_values[4];
            }

            // Conditionally perform ops
            if (!public_key_path.empty() && !text.empty())
            {
                ECC ecc = ECC();
                ecc.set_public_key_path(public_key_path);
                ecc.set_raw_plaintext(text);
                ecc.encrypt();
                std::cout << ecc.get_encoded_ciphertext() << std::endl;
            }
        }

        // decrypt
        // - named parameters:
        //   --private_key_path
        //   --ciphertext
        // - ordered parameters:
        //   private_key_path
        //   text
        else if (strcmp(arg_values[2], "decrypt") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/ordered parameters" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Possible params
            std::string private_key_path;
            std::string ciphertext;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if (parameter.find("--private_key_path=") == 0)
                {
                    private_key_path = parameter.substr(19);
                }
                else if (parameter.find("--ciphertext=") == 0)
                {
                    ciphertext = parameter.substr(13);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (private_key_path.empty() && arg_count > 3)
            {
                private_key_path = arg_values[3];
            }
            if (ciphertext.empty() && arg_count > 4)
            {
                ciphertext = arg_values[4];
            }

            // Conditionally perform ops
            if (!private_key_path.empty() && !ciphertext.empty())
            {
                ECC ecc = ECC();
                ecc.set_private_key_path(private_key_path);
                std::string raw_ciphertext = ecc.decode(ciphertext);
                ecc.set_raw_ciphertext(raw_ciphertext);
                ecc.decrypt();
                std::cout << ecc.get_raw_plaintext() << std::endl;
            }
        }

        // sign
        // - named parameters:
        //   --private_key_path
        //   --text
        // - ordered parameters:
        //   private_key_path
        //   text
        else if (strcmp(arg_values[2], "sign") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/ordered parameters" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Possible params
            std::string private_key_path;
            std::string text;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if (parameter.find("--private_key_path=") == 0)
                {
                    private_key_path = parameter.substr(19);
                }
                else if (parameter.find("--text=") == 0)
                {
                    text = parameter.substr(7);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (private_key_path.empty() && arg_count > 3)
            {
                private_key_path = arg_values[3];
            }
            if (text.empty() && arg_count > 4)
            {
                text = arg_values[4];
            }

            // Conditionally perform ops
            if (!private_key_path.empty() && !text.empty())
            {
                ECC ecc = ECC();
                ecc.set_private_key_path(private_key_path);
                std::string text_hash = ecc.hash(ecc.hash(text));
                ecc.set_raw_plaintext_hash(text_hash);
                ecc.sign();
                std::cout << text_hash << std::endl;
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
        // Check for --help flag
        if (arg_count == 2 || strcmp(arg_values[2], "--help") == 0)
        {
            cout_identity_help_prompt();
        }

        // add
        // - named parameters:
        //   --path
        //   --public_key
        //   --n
        // - ordered parameters:
        //   path
        //   public_key
        else if (strcmp(arg_values[2], "add") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/ordered parameters" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Possible params
            std::string path;
            std::string public_key;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if (parameter.find("--path=") == 0)
                {
                    path = parameter.substr(7);
                }
                else if(parameter.find("--public_key=") == 0)
                {
                    public_key = parameter.substr(13);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (path.empty() && arg_count > 3)
            {
                path = arg_values[3];
            }
            if (public_key.empty() && arg_count > 4)
            {
                public_key = arg_values[4];
            }

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
        // - named parameters:
        //   --path
        // - ordered parameters:
        //   path
        else if (strcmp(arg_values[2], "remove") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/ordered parameters" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Possible params
            std::string path;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if(parameter.find("--path=") == 0)
                {
                    path = parameter.substr(7);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (path.empty() && arg_count >= 3)
            {
                path = arg_values[3];
            }

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
        // - named parameters:
        //   --path
        // - ordered parameters:
        //   path
        else if (strcmp(arg_values[2], "list") == 0)
        {
            // Possible params
            std::string path;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if(parameter.find("--path=") == 0)
                {
                    path = parameter.substr(7);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (path.empty() && arg_count > 3)
            {
                path = arg_values[3];
            }

            // If not set, fallback to use default identities path
            if (path.empty())
            {
                path = default_identities_path;
            }

            // Output tab formatted index filename pairs in path
            std::cout << std::endl;
            std::cout << "Index\tFilename" << std::endl;
            std::vector<std::string> files = ls(path);
            int file_count = files.size();
            for (int z = 0; z < file_count; z++)
            {
                std::cout << z << '\t' << files[z] << std::endl;
            }
            std::cout << std::endl;
        }

        // verify
        // - named parameters:
        //   --public_key_path
        //   --signature
        //   --message_hash
        // - ordered parameters:
        //   public_key_path
        //   signature
        //   message_hash
        else if (strcmp(arg_values[2], "verify") == 0)
        {
            // Missing args
            if (arg_count == 3)
            {
                std::cout << std::endl;
                std::cout << "ERROR: Missing named/ordered parameters" << std::endl;
                cout_keypair_help_prompt();
                return 1;
            }

            // Possible params
            std::string public_key_path;
            std::string signature;
            std::string message_hash;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if (parameter.find("--public_key_path=") == 0)
                {
                    public_key_path = parameter.substr(7);
                }
                else if (parameter.find("--signature=") == 0)
                {
                    signature = parameter.substr(12);
                }
                else if (parameter.find("--message_hash=") == 0)
                {
                    message_hash = parameter.substr(15);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (public_key_path.empty() && arg_count > 3)
            {
                public_key_path = arg_values[3];
            }
            if (signature.empty() && arg_count > 4)
            {
                signature = arg_values[4];
            }
            if (message_hash.empty() && arg_count > 5)
            {
                message_hash = arg_values[5];
            }

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
