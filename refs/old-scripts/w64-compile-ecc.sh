#!/bin/bash

INC="/root/iris/include"
BIN="/root/iris/bin/win64-cc-test.exe"
TGT="/root/iris/tests/crypto-ecc.cpp"

CRYPTOPP_INC="/root/iris/libs/windows/cryptopp/include"
CRYPTOPP_LIB="/root/iris/libs/windows/cryptopp/lib"

WIN_64_CPL="x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++"

# Remove bin file if it exists
if [ -f "$BIN" ]
then
    rm $BIN
fi

# Exit if target file does not exist
if ! [ -f "$TGT" ]
then
    echo -e "\033[31m[C] Failed\tFile: $TGT is missing\033[0m"
    exit 1
fi

# Compile windows 64-bit executable
echo -e "\033[36m[C] Compiling\tWindows 64-bit\033[0m"
$WIN_64_CPL -Wall $TGT -o $BIN -I $CRYPTOPP_INC -L $CRYPTOPP_LIB -I $INC -lcryptopp -static
if [ -f "$BIN" ]
then
    echo -e "\033[32m[P] Compiled\t$TGT->$BIN\033[0m"
else
    echo -e "\033[31m[C] Failed\t$TGT->$BIN\033[0m"
fi
