DIR="/root/iris/libs/cryptopp"
VER="CRYPTOPP_8_7_0"

# clone dir if it does not exist
if ! [ -d "$DIR"]
then
    git clone https://github.com/weidai11/cryptopp.git ./libs/cryptopp
fi

cd $DIR
git checkout tags/$VER -b $VER
make -f GNUmakefile-cross distclean
make -f GNUmakefile-cross CXX=x86_64-w64-mingw32-g++ CXXFLAGS="-m64" -j`nproc`
make -f GNUmakefile-cross CXX=x86_64-w64-mingw32-g++ CXXFLAGS="-m64" -j`nproc` install
# This may or may not be required. Rebuilding container + testing required
# sudo ldconfig
