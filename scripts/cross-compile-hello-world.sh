# Include directory
INC="/root/iris/include/"

# Target file
TGT="/root/iris/tests/hello-world.cpp"

# Exit if target file does not exist
if ! [ -f "$TGT" ]
then
    echo -e "\033[31m[C] Failed\tFile: $TGT is missing\033[0m"
    exit 1
fi

# Windows 32-bit defs
WIN_32_CPL="i686-w64-mingw32-g++ -static-libgcc -static-libstdc++"
WIN_32_BIN="/root/iris/bin/win32-cc-test.exe"

# Windows 64-bit
WIN_64_CPL="x86_64-w64-mingw32-g++ -static-libgcc -static-libstdc++"
WIN_64_BIN="/root/iris/bin/win64-cc-test.exe"

# Linux 32-bit
LNX_32_CPL="g++ -m32"
LNX_32_BIN="/root/iris/bin/lnx32-cc-test"

# Linux 64-bit
LNX_64_CPL="g++"
LNX_64_BIN="/root/iris/bin/lnx64-cc-test"

# Remove binaries if they exist
if [ -f "$WIN_32_BIN" ]; then rm "$WIN_32_BIN"; fi
if [ -f "$WIN_64_BIN" ]; then rm "$WIN_64_BIN"; fi
if [ -f "$LNX_32_BIN" ]; then rm "$LNX_32_BIN"; fi
if [ -f "$LNX_64_BIN" ]; then rm "$LNX_64_BIN"; fi

# Compile windows 32-bit executable
echo -e "\033[36m[C] Compiling\tWindows 32-bit\033[0m"
$WIN_32_CPL -Wall -I $INC $TGT -o $WIN_32_BIN
if [ -f "$WIN_32_BIN" ]
then
    echo -e "\033[32m[P] Compiled\t$TGT->$WIN_32_BIN\033[0m"
else
    echo -e "\033[31m[C] Failed\t$TGT->$WIN_32_BIN\033[0m"
fi

# Compile windows 64-bit executable
echo -e "\033[36m[C] Compiling\tWindows 64-bit\033[0m"
$WIN_64_CPL -Wall -I $INC $TGT -o $WIN_64_BIN
if [ -f "$WIN_64_BIN" ]
then
    echo -e "\033[32m[P] Compiled\t$TGT->$WIN_64_BIN\033[0m"
else
    echo -e "\033[31m[C] Failed\t$TGT->$WIN_64_BIN\033[0m"
fi

# Compile linux 32-bit executable
echo -e "\033[36m[C] Compiling\tlinux 32-bit\033[0m"
$LNX_32_CPL -Wall $TGT -o $LNX_32_BIN
if [ -f "$LNX_32_BIN" ]
then
    echo -e "\033[32m[P] Compiled\t$TGT->$LNX_32_BIN\033[0m"
else
    echo -e "\033[31m[C] Failed\t$TGT->$LNX_32_BIN\033[0m"
fi

# Compile linux 64-bit executable
echo -e "\033[36m[C] Compiling\tlinux 64-bit\033[0m"
$LNX_64_CPL -Wall -I $INC $TGT -o $LNX_64_BIN
if [ -f "$LNX_64_BIN" ]
then
    echo -e "\033[32m[P] Compiled\t$TGT->$LNX_64_BIN\033[0m"
else
    echo -e "\033[31m[C] Failed\t$TGT->$LNX_64_BIN\033[0m"
fi
