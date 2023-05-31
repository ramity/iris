# Define platform agnostic vars and conditionally exit if target does not exist

IRIS_INC="/root/iris/include"
TGT="/root/iris/src/main.cpp"
if ! [ -f "$TGT" ]
then
    echo -e "\033[31m[C] Failed\tFile: $TGT is missing\033[0m"
    exit 1
fi

# Build require dirs

BUILD_DIR="/root/iris/build"
KEYS_DIR="$BUILD_DIR/keys"
IDENTITIES_DIR="$BUILD_DIR/identities"
mkdir $KEYS_DIR
mkdir $IDENTITIES_DIR

# Define platform specific bins

L64_BIN="$BUILD_DIR/iris"
W64_BIN="$BUILD_DIR/iris.exe"

# Linux compile config

L64_CRYPTOPP_INC="/root/iris/libs/linux/cryptopp/include"
L64_CRYPTOPP_LIB="/root/iris/libs/linux/cryptopp/lib"
L64_CPL="g++"

# Windows compile config

W64_CRYPTOPP_INC="/root/iris/libs/windows/cryptopp/include"
W64_CRYPTOPP_LIB="/root/iris/libs/windows/cryptopp/lib"
W64_CPL="x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++"

# Linux compile

echo -e "\033[36m[C] Compiling Linux 64-bit\033[0m"
$L64_CPL -Wall $TGT -o $L64_BIN -I $L64_CRYPTOPP_INC -L $L64_CRYPTOPP_LIB -I $IRIS_INC -lcryptopp -static
if [ -f "$L64_BIN" ]
then
    echo -e "\033[32m[P] Compiled\t$TGT->$L64_BIN\033[0m"
else
    echo -e "\033[31m[C] Failed\t$TGT->$L64_BIN\033[0m"
fi

# Windows compile

echo -e "\033[36m[C] Compiling\tWindows 64-bit\033[0m"
$W64_CPL -Wall $TGT -o $W64_BIN -I $W64_CRYPTOPP_INC -L $W64_CRYPTOPP_LIB -I $IRIS_INC -lcryptopp -static
if [ -f "$W64_BIN" ]
then
    echo -e "\033[32m[P] Compiled\t$TGT->$W64_BIN\033[0m"
else
    echo -e "\033[31m[C] Failed\t$TGT->$W64_BIN\033[0m"
fi
