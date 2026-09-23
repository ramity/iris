#!/bin/bash

# Function to check if the script is running in a Windows environment

is_windows() {
    case "$OSTYPE" in
        msys*|cygwin*|mingw*|win*) return 0 ;;
        *) return 1 ;;
    esac
}

# Conditionally use ./iris or ./iris depending on if windows

if is_windows; then
    executable="./iris.exe"
else
    executable="./iris"
fi

# Constants

divider="------------------------------------------------"

# Enter loop to ask user for which option to select from a series of cooked iris commands

while true; do

    echo "$divider"
    echo
    echo "S: What would you like to do?"
    echo
    echo "$divider"
    echo "0. Exit"
    echo "1. Generate my keypair"
    echo "2. Share my identity"
    echo "3. Import an identity"
    echo "4. Encrypt an outgoing message"
    echo "5. Decrypt an incoming message"
    echo "6. Encrypt an outgoing file"
    echo "7. Decrypt an incoming file"
    echo "$divider"
    echo
    echo -n "U: "
    read option
    echo
    echo "$divider"

    case $option in
        # Exit
        0)
            exit
            ;;

        # Generate keypair
        1)
            # Validate user has not already generated keypair
            # If they have, inform the user and skip this command
            if [ -f "./keys/my_private_key" ] || [ -f "./identities/my_public_key" ]; then
                echo "Error: Keypair already exists"
                continue
            fi

            # Generate the default keypair
            $executable keypair generate ./keys/my_private_key ./identities/my_public_key
            ;;

        # Share identity
        2)
            echo
            echo "S: What name would you like to go by?"
            echo
            echo "$divider"
            echo
            echo -n "U: "
            read name
            echo
            echo "$divider"
            echo
            echo "S: Copy the following and send it to the person you want to import your identity:"
            echo
            echo "$divider"

            public_key=$(cat ./identities/my_public_key)

            echo
            echo "$name@$public_key"
            echo
            ;;

        # Import an identity
        3)
            echo
            echo "S: Paste the identity below:"
            echo
            echo "$divider"
            echo
            echo -n "U: "
            read identity
            echo
            echo "$divider"
            echo

            # Extract the leading name
            name=${identity%@*}

            # Get the remaining public key
            pub_key=${identity#*@}

            echo "S: Importing identity:"
            echo
            echo "name: $name"
            echo "public key: $pub_key"
            echo

            # Create the identity file
            $executable identity add ./identities/${name}_public_key $pub_key

            echo "S: Successfully imported identity"
            echo
            ;;

        # Encrypt outgoing message
        4)
            echo
            echo "S: Specify the filename of the identity you would like to use to encrypt the outgoing message:"
            $executable identity list
            echo "$divider"
            echo
            echo -n "U: "
            read identity_public_key
            identity_file_path="./identities/$identity_public_key"
            echo

            echo "S: Specify the message:"
            echo
            echo -n "U: "
            read plaintext_message

            echo
            echo "$divider"
            echo
            $executable keypair encrypt "$identity_file_path" "$plaintext_message"
            echo
            ;;

        # Decrypt incoming message
        5)
            echo
            echo "S: Paste the ciphertext (encrypted message) below:"
            echo
            echo "$divider"
            echo
            echo -n "U: "
            read ciphertext
            echo
            echo "$divider"
            echo

            # Outputs decrypted message to terminal
            $executable keypair decrypt ./keys/my_private_key $ciphertext
            echo
            ;;

        # Encrypt outgoing file
        6)
            echo
            echo "S: Specify the filename of the identity you would like to use to encrypt the outgoing message:"
            $executable identity list
            echo "$divider"
            echo
            echo -n "U: "
            read identity_public_key
            identity_file_path="./identities/$identity_public_key"
            echo

            echo
            echo "S: Specify the filepath to the file you would like to encrypt:"
            echo
            echo -n "U: "
            read original_file_path
            echo
            echo "$divider"
            echo

            encrypted_file_path="$original_file_path.enc"

            $executable keypair encrypt_file $identity_file_path $original_file_path $encrypted_file_path
            ;;

        # Decrypt incoming file
        7)
            echo
            echo "S: Specify the filepath to the incoming encrypted message:"
            echo
            echo -n "U:"
            read incoming_encrypted_filepath

            # Replace .enc ending of incoming_encrypted_filepath with .dec
            decrypted_file_path="${incoming_encrypted_filepath%.enc}.dec"

            $executable keypair decrypt_file ./keys/my_private_key $incoming_encrypted_filepath $decrypted_file_path
            ;;

        # Catch any invalid options
        *)
            echo "S: Invalid option"
            ;;
    esac
done
