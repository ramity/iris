#include <iostream>
#include <cstring>

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
    std::cout << "  generate DIR_PATH" << std::endl;
    std::cout << "  delete KEY_PATH" << std::endl;
    std::cout << "  encrypt KEY_PATH TEXT" << std::endl;
    std::cout << "  decrypt KEY_PATH TEXT" << std::endl;
    std::cout << "  sign KEY_PATH MESSAGE" << std::endl;
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

        // generate DIR_PATH

        else if (strcmp(arg_values[2], "generate") == 0)
        {

        }

        // delete KEY_PATH

        else if (strcmp(arg_values[2], "delete") == 0)
        {

        }

        // encrypt KEY_PATH TEXT

        else if (strcmp(arg_values[2], "encrypt") == 0)
        {

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
