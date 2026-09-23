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

# Simply generate a keypair

command="$executable keypair generate ./keys/pri_a ./identities/pub_a"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Generate keypairs using the same seed and compare files

command="$executable keypair generate ./keys/pri_b ./identities/pub_b \"UnlimitedGamesButNoGames\" 1"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

command="$executable keypair generate ./keys/pri_c ./identities/pub_c \"UnlimitedGamesButNoGames\" 1"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

if cmp -s "./keys/pri_b" "./keys/pri_c"; then
    echo -e "\033[32m[P] ./keys/pri_b ./keys/pri_c match'\033[0m"
else
    echo -e "\033[33m[F] ./keys/pri_b ./keys/pri_c match'\033[0m"
fi

if cmp -s "./identities/pub_b" "./identities/pub_c"; then
    echo -e "\033[32m[P] ./identities/pub_b ./identities/pub_c match'\033[0m"
else
    echo -e "\033[33m[F] ./identities/pub_b ./identities/pub_c match'\033[0m"
fi

# Delete ./keys/pri_a and ./identities/pub_a and verify they were removed

command="$executable keypair delete ./keys/pri_a ./identities/pub_a"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

if [ ! -f "./keys/pri_a" ]; then
    echo -e "\033[32m[P] ./keys/pri_a was removed'\033[0m"
else
    echo -e "\033[33m[F] ./keys/pri_a was not removed'\033[0m"
fi

if [ ! -f "./identities/pub_a" ]; then
    echo -e "\033[32m[P] ./identities/pub_a was removed'\033[0m"
else
    echo -e "\033[33m[F] ./identities/pub_a was not removed'\033[0m"
fi

# Encrypt using ./identities/pub_b

plaintext="Hello, world!"
command="$executable keypair encrypt ./identities/pub_b \"$plaintext\""
ciphertext=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Decrypt using ./keys/pri_b

command="$executable keypair decrypt ./keys/pri_b $ciphertext"
derived_plaintext=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Check if the derived_plaintext matches the original plaintext

if [ "$plaintext" == "$derived_plaintext" ]; then
    echo -e "\033[32m[P] Decryption produced the original plaintext\033[0m"
else
    echo -e "\033[33m[F] Decryption failed to produce the original plaintext\033[0m"
fi

# Add key pub_b to identities and verify the file contains the public key

command="cat ./identities/pub_b"
public_key=$(eval $command)
command="$executable identity add ./identities/pub_b $public_key"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

if grep -q "$public_key" "./identities/pub_b"; then
    echo -e "\033[32m[P] Public key contained in created identity file\033[0m"
else
    echo -e "\033[33m[F] Public key missing in created identity file\033[0m"
fi

# Sign a message and verify it using the identity command

command="$executable keypair sign ./keys/pri_b \"$plaintext\""
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

exec 3<<< "$result"
read -r text_hash <&3
read -r signature <&3
exec 3<&-

command="$executable identity verify ./identities/pub_b $signature $text_hash"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

if [ "$result" == "Valid signature" ]; then
    echo -e "\033[32m[P] Valid signature\033[0m"
else
    echo -e "\033[33m[F] Invalid signature\033[0m"
fi

# List identities

command="$executable identity list ./identities/"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Remove identity

command="$executable identity remove ./identities/pub_b"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Remove private key via identity command

command="$executable identity remove ./keys/pri_b"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Test the keypair help command

command="$executable keypair --help"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Store the result into a temp file

echo "$result" > ./temp_file.txt

# Validate the temp file was created

if [ -f "./temp_file.txt" ]; then
    echo -e "\033[32m[P] ./temp_file.txt was created\033[0m"
else
    echo -e "\033[33m[F] ./temp_file.txt was not created\033[0m"
fi

# Test the encrypt_file command

command="$executable keypair encrypt_file ./identities/pub_c ./temp_file.txt ./temp_file.txt.enc"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Validate the encrypted file exists

if [ -f "./temp_file.txt.enc" ]; then
    echo -e "\033[32m[P] ./temp_file.txt.enc was created\033[0m"
else
    echo -e "\033[33m[F] ./temp_file.txt.enc was not created\033[0m"
fi

# Test the decrypt_file command

command="$executable keypair decrypt_file ./keys/pri_c ./temp_file.txt.enc ./temp_file.txt.dec"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Validate the decrypted file exists

if [ -f "./temp_file.txt.dec" ]; then
    echo -e "\033[32m[P] ./temp_file.txt.dec was created\033[0m"
else
    echo -e "\033[33m[F] ./temp_file.txt.dec was not created\033[0m"
fi

# Validate it matches the original file

if cmp -s "./temp_file.txt" "./temp_file.txt.dec"; then
    echo -e "\033[32m[P] ./temp_file.txt.dec matches ./temp_file.txt\033[0m"
else
    echo -e "\033[33m[F] ./temp_file.txt.dec does not match ./temp_file.txt\033[0m"
fi

# Delete the original, encrypted, and decrypted temp files

rm ./temp_file.txt
rm ./temp_file.txt.enc
rm ./temp_file.txt.dec

# Delete ./keys/pri_c and ./identities/pub_c and verify they were removed

command="$executable keypair delete ./keys/pri_c ./identities/pub_c"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

# Validate pri_c was removed.

if [ ! -f "./keys/pri_c" ]; then
    echo -e "\033[32m[P] ./keys/pri_c was removed'\033[0m"
else
    echo -e "\033[33m[F] ./keys/pri_c was not removed'\033[0m"
fi

# Validate pub_c was removed.

if [ ! -f "./identities/pub_c" ]; then
    echo -e "\033[32m[P] ./identities/pub_c was removed'\033[0m"
else
    echo -e "\033[33m[F] ./identities/pub_c was not removed'\033[0m"
fi

# Add a pause to keep script from exiting before user can examine output

if is_windows; then
    read -n 1 -s -r -p "Press any key to continue..."
fi
