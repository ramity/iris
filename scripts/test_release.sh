# Simply generate a keypair

command="./iris keypair generate ./keys/pri_a ./keys/pub_a"
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

command="./iris keypair generate ./keys/pri_b ./keys/pub_b \"UnlimitedGamesButNoGames\" 1"
result=$(eval $command)
exit_code=$?
if [ $exit_code -eq 0 ]; then
    echo -e "\033[32m[P] '$command'\033[0m"
elif [ $exit_code -eq 1 ]; then
    echo -e "\033[33m[F] '$command'\033[0m"
else
    echo -e "\033[33m[$exit_code] '$command'\033[0m"
fi

command="./iris keypair generate ./keys/pri_c ./keys/pub_c \"UnlimitedGamesButNoGames\" 1"
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

if cmp -s "./keys/pub_b" "./keys/pub_c"; then
    echo -e "\033[32m[P] ./keys/pub_b ./keys/pub_c match'\033[0m"
else
    echo -e "\033[33m[F] ./keys/pub_b ./keys/pub_c match'\033[0m"
fi

# Delete ./keys/pri_a and verify it was removed

command="./iris keypair delete ./keys/pri_a ./keys/pub_a"
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

if [ ! -f "./keys/pub_a" ]; then
    echo -e "\033[32m[P] ./keys/pub_a was removed'\033[0m"
else
    echo -e "\033[33m[F] ./keys/pub_a was not removed'\033[0m"
fi

# Encrypt using ./keys/pub_b

plaintext="Hello, world!"
command="./iris keypair encrypt ./keys/pub_b \"$plaintext\""
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

command="./iris keypair decrypt ./keys/pri_b $ciphertext"
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

# ./iris keypair sign
# ./iris identity --help
# ./iris identity add
# ./iris identity remove
# ./iris identity list
# ./iris identity verify
