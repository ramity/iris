#!/bin/bash

# Clear build dir

BUILD_DIR="/root/iris/build"
rm -r -d $BUILD_DIR/*

# Define platform agnostic vars and conditionally exit if target does not exist

IRIS_INC="/root/iris/include"
TGT="/root/iris/src/main.cpp"
if ! [ -f "$TGT" ]
then
    echo -e "\033[31m[C] Failed\tFile: $TGT is missing\033[0m"
    exit 1
fi

# Build require dirs

KEYS_DIR="$BUILD_DIR/keys"
IDENTITIES_DIR="$BUILD_DIR/identities"
mkdir $KEYS_DIR
mkdir $IDENTITIES_DIR

# Add release related scripts

cp /root/iris/scripts/release/test.sh $BUILD_DIR/test.sh
cp /root/iris/scripts/release/update.sh $BUILD_DIR/update.sh
chmod +x $BUILD_DIR/test.sh
chmod +x $BUILD_DIR/update.sh

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

# Add version file for update script

touch $BUILD_DIR/version
echo "v0.3.2" > $BUILD_DIR/version

# Add ramity identity

echo "MIGbMBAGByqGSM49AgEGBSuBBAAjA4GGAAQBNtwf+HWIV/ifAz826Anbd6Ce5L3WPvXGBZ99EEd1QNYqzToWCCLMd5ajzFOidBESl5jjX0jwgpxvV626KBHaJMgB6zKDw3zd2v1IC7IkNCXUDe7DRgqyjFpkLTJ+aGrBRfBgJq20Sqf/RHINHvlzulzQYKV0/vrdGqdqbsQURHoWZGQ=" > $BUILD_DIR/identities/ramity

# Create release zips

cd $BUILD_DIR
zip -9 linux-64.zip -r ./* -x ./iris.exe -x "*.zip" -x ".gitkeep"
zip -9 windows-64.zip -r ./* -x ./iris -x "*.zip" -x ".gitkeep"

# Prevent permission issues when testing from within the build dir

chown -R 1000:1000 ./*
