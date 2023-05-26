DIR="/root/iris/libs/src/cryptopp"
VER="CRYPTOPP_8_7_0"
CXX="x86_64-w64-mingw32-g++"
CXXFLAGS="-m64"
PREFIX="/root/iris/libs/windows/crytopp"

# create prefix dir if it does not exist
if ! [ -d "$PREFIX" ]
then
    mkdir -p $PREFIX
fi

# clone dir if it does not exist
if ! [ -d "$DIR" ]
then
    git clone https://github.com/weidai11/cryptopp.git $DIR
fi

cd $DIR

# conditionally create branch if it does not exist and checkout specific tag
if git rev-parse --quiet --verify "refs/tags/$tag" > /dev/null
then
    # branch exists, checkout
    git checkout $VER
else
    # branch does not exist, checkout and create
    git checkout tags/$VER -b $VER
fi

# compile cryptopp to prefix dir
make -f GNUmakefile-cross PREFIX=$PREFIX distclean
make -f GNUmakefile-cross PREFIX=$PREFIX CXX=$CXX CXXFLAGS=$CXXFLAGS -j`nproc`
make -f GNUmakefile-cross PREFIX=$PREFIX CXX=$CXX CXXFLAGS=$CXXFLAGS -j`nproc` install

# This may or may not be required. Rebuilding container + testing required
# sudo ldconfig
