# Include directory
INC="/root/iris/include/"

# Target file
TGT="/root/iris/tests/w64-crypto-ecc.cpp"

# Exit if target file does not exist
if ! [ -f "$TGT" ]
then
    echo -e "\033[31m[C] Failed\tFile: $TGT is missing\033[0m"
    exit 1
fi

# Windows 64-bit
WIN_64_CPL="x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++"
WIN_64_BIN="/root/iris/bin/win64-cc-test.exe"

# Remove binaries if they exist
if [ -f "$WIN_64_BIN" ]; then rm "$WIN_64_BIN"; fi

# Compile windows 64-bit executable
echo -e "\033[36m[C] Compiling\tWindows 64-bit\033[0m"
$WIN_64_CPL -Wall $TGT -o $WIN_64_BIN -I /usr/local/include -L /usr/local/lib -I $INC -lcryptopp -static
if [ -f "$WIN_64_BIN" ]
then
    echo -e "\033[32m[P] Compiled\t$TGT->$WIN_64_BIN\033[0m"
else
    echo -e "\033[31m[C] Failed\t$TGT->$WIN_64_BIN\033[0m"
fi
