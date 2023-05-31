#include <iostream>
#include <cstring>
#include <cstdio>

#include "crypto/ECC.cpp"

void cout_repo_ad()
{
    std::cout << "To get more help with iris, check out the github repo at https://github.com/ramity/iris" << std::endl;
}

void cout_iris_ascii_art()
{
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
    std::cout << "Usage: iris COMMAND" << std::endl;
    std::cout << std::endl;
    std::cout << "A portable management tool forcryptography operations" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  keypair      Keypair related operations" << std::endl;
    std::cout << "  identity     Identity related operations" << std::endl;
    std::cout << "  escrow       Perform or request operations from a trusted third party" << std::endl;
    std::cout << "  onion        A special message type that requires group cooperation to open" << std::endl;
    std::cout << std::endl;
    std::cout << "Run 'iris COMMAND --help' for more information on a command." << std::endl;
    std::cout << std::endl;
    cout_repo_ad();
}

void cout_keypair_help_prompt()
{
    cout_iris_ascii_art();
    std::cout << std::endl;
    std::cout << "Usage: iris keypair COMMAND" << std::endl;
    std::cout << std::endl;
    std::cout << "Keypair related operations" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  generate" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "    --seed" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << "    seed" << std::endl;
    std::cout << "  delete" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << "  encrypt" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --public_key_path" << std::endl;
    std::cout << "    --text" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    public_key_path" << std::endl;
    std::cout << "    text" << std::endl;
    std::cout << "  decrypt" << std::endl;
    std::cout << "  - named parameters:" << std::endl;
    std::cout << "    --private_key_path" << std::endl;
    std::cout << "    --ciphertext" << std::endl;
    std::cout << "  - ordered parameters:" << std::endl;
    std::cout << "    private_key_path" << std::endl;
    std::cout << "    ciphertext" << std::endl;
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
    std::cout << "Usage: iris identity COMMAND" << std::endl;
    std::cout << std::endl;
    std::cout << "Identity related operations" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  add KEY_PATH KEY_TEXT" << std::endl;
    std::cout << "  remove KEY_PATH" << std::endl;
    std::cout << "  list KEY_DIR" << std::endl;
    std::cout << "  verify_signature KEY_PATH SIGNATURE MESSAGE_HASH" << std::endl;
    std::cout << std::endl;
    cout_repo_ad();
}

void cout_escrow_help_prompt()
{
    cout_iris_ascii_art();
    std::cout << std::endl;
    std::cout << "Usage: iris escrow COMMAND" << std::endl;
    std::cout << std::endl;
    std::cout << "Perform or request operations from a trusted third party" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  request TYPE TRUSTED_IDENTITY_KEY_PATH" << std::endl;
    std::cout << "  generate TYPE KEY_PATH" << std::endl;
    std::cout << "  process TYPE TRUSTED_IDENTITY_KEY_PATH" << std::endl;
    std::cout << std::endl;
    cout_repo_ad();
}

void cout_onion_help_prompt()
{
    cout_iris_ascii_art();
    std::cout << std::endl;
    std::cout << "Usage: iris onion COMMAND" << std::endl;
    std::cout << std::endl;
    std::cout << "A special message type that requires group cooperation to open" << std::endl;
    std::cout << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  create TYPE [IDENTITY_KEY_PATH_ARRAY] TEXT" << std::endl;
    std::cout << "  decrypt TYPE KEY_PATH" << std::endl;
    std::cout << std::endl;
    cout_repo_ad();
}

int main(int arg_count, char * arg_values[])
{
    // Check for --help flag

    if (arg_count == 1 || strcmp(arg_values[1], "--help") == 0)
    {
        cout_general_help_prompt();
        return 0;
    }

    // keypair

    else if (strcmp(arg_values[1], "keypair") == 0)
    {
        // Check for --help flag

        if (arg_count == 2 || strcmp(arg_values[2], "--help") == 0)
        {
            cout_keypair_help_prompt();
            return 0;
        }

        // generate
        // - named parameters:
        //   --private_key_path
        //   --public_key_path
        //   --seed
        // - ordered parameters:
        //   private_key_path
        //   public_key_path
        //   seed

        else if (strcmp(arg_values[2], "generate") == 0)
        {
            // Possible params
            std::string private_key_path;
            std::string public_key_path;
            std::string seed;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if(parameter.find("--private_key_path=") == 0)
                {
                    private_key_path = parameter.substr(19);
                }
                else if(parameter.find("--public_key_path=") == 0)
                {
                    public_key_path = parameter.substr(18);
                }
                else if(parameter.find("--seed=") == 0)
                {
                    seed = parameter.substr(7);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (private_key_path.empty() && arg_count >= 3)
            {
                private_key_path = arg_values[3];
            }
            if (public_key_path.empty() && arg_count >= 4)
            {
                public_key_path = arg_values[4];
            }
            if (seed.empty() && arg_count >= 5)
            {
                seed = arg_values[5];
            }

            // Conditionally perform ops
            ECC ecc = ECC();
            if (!private_key_path.empty())
                ecc.set_private_key_path(private_key_path);
            if (!public_key_path.empty())
                ecc.set_public_key_path(public_key_path);
            if (!seed.empty())
                ecc.set_seed(seed);
            ecc.generate_keys();
            ecc.write_keys();
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
            // Possible params
            std::string private_key_path;
            std::string public_key_path;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if(parameter.find("--private_key_path=") == 0)
                {
                    private_key_path = parameter.substr(19);
                }
                else if(parameter.find("--public_key_path=") == 0)
                {
                    public_key_path = parameter.substr(18);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (private_key_path.empty() && arg_count >= 3)
            {
                private_key_path = arg_values[3];
            }
            if (public_key_path.empty() && arg_count >= 4)
            {
                public_key_path = arg_values[4];
            }

            // Conditionally perform ops
            if (!private_key_path.empty())
            {
                if (std::remove(private_key_path.c_str()))
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
                if (std::remove(public_key_path.c_str()))
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
            // Possible params
            std::string public_key_path;
            std::string text;

            // Check named params:
            for (int z = 3; z < arg_count; z++)
            {
                std::string parameter = arg_values[z];

                if(parameter.find("--public_key_path=") == 0)
                {
                    public_key_path = parameter.substr(18);
                }
                else if(parameter.find("--text=") == 0)
                {
                    text = parameter.substr(7);
                }
            }

            // Check ordered params w/ precedence to named params:
            if (public_key_path.empty() && arg_count >= 3)
            {
                public_key_path = arg_values[3];
            }
            if (text.empty() && arg_count >= 4)
            {
                text = arg_values[4];
            }

            // Conditionally perform ops
            if (!public_key_path.empty() && !text.empty())
            {
                // ISSUE #14 - Support just reading the public key for encryption
                // ECC ecc = ECC();
                // ecc.set_public_key_path(public_key_path);
                // ecc.set_raw_plaintext(text);
                // ecc.encrypt();
                // std::cout << ecc.get_raw_ciphertext() << std::endl;
            }
        }

        // decrypt KEY_PATH TEXT

        else if (strcmp(arg_values[2], "decrypt") == 0)
        {

        }

        // sign KEY_PATH MESSAGE

        else if (strcmp(arg_values[2], "sign") == 0)
        {

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
            return 0;
        }

        // add KEY_PATH KEY_TEXT

        else if (strcmp(arg_values[2], "add") == 0)
        {

        }

        // remove KEY_PATH

        else if (strcmp(arg_values[2], "remove") == 0)
        {

        }

        // list KEY_DIR

        else if (strcmp(arg_values[2], "list") == 0)
        {

        }

        // verify_signature KEY_PATH SIGNATURE MESSAGE_HASH

        else if (strcmp(arg_values[2], "verify_signature") == 0)
        {

        }

        // incorrect input

        else
        {
            std::cout << "iris identity '" << arg_values[2] << "' is not an iris command. See 'iris identity --help'." << std::endl;
        }
    }

    // escrow

    else if (strcmp(arg_values[1], "escrow") == 0)
    {
        // Check for --help flag

        if (arg_count == 2 || strcmp(arg_values[2], "--help") == 0)
        {
            cout_escrow_help_prompt();
            return 0;
        }

        // request TYPE TRUSTED_IDENTITY_KEY_PATH

        else if (strcmp(arg_values[2], "request") == 0)
        {

        }

        // generate TYPE KEY_PATH

        else if (strcmp(arg_values[2], "generate") == 0)
        {

        }

        // process TYPE TRUSTED_IDENTITY_KEY_PATH

        else if (strcmp(arg_values[2], "process") == 0)
        {

        }

        // incorrect input

        else
        {
            std::cout << "iris escrow '" << arg_values[2] << "' is not an iris command. See 'iris escrow --help'." << std::endl;
        }
    }

    // onion
 
    else if (strcmp(arg_values[1], "onion") == 0)
    {
        // Check for --help flag

        if (arg_count == 2 || strcmp(arg_values[2], "--help") == 0)
        {
            cout_identity_help_prompt();
            return 0;
        }

        // create TYPE [IDENTITY_KEY_PATH_ARRAY] TEXT

        else if (strcmp(arg_values[2], "process") == 0)
        {

        }

        // decrypt TYPE KEY_PATH

        else if (strcmp(arg_values[2], "process") == 0)
        {

        }

        // incorrect input

        else
        {
            std::cout << "iris onion '" << arg_values[2] << "' is not an iris command. See 'iris onion --help'." << std::endl;
        }
    }

    // incorrect input

    else
    {
        std::cout << "iris '" << arg_values[1] << "' is not an iris command. See 'iris --help'." << std::endl;
    }

    return 1;
}
