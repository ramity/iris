#!/bin/bash

DIR="/root/iris/libs/src/cryptopp"
VER="CRYPTOPP_8_7_0"
CXX="g++"
CXXFLAGS="-m64"
PREFIX="/root/iris/libs/linux/cryptopp"

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
if git branch | grep -q $VER
then
    # branch exists, checkout quietly if already on branch
    git checkout $VER > /dev/null 2>&1
else
    # branch does not exist, checkout and create
    git checkout tags/$VER -b $VER
fi

# compile cryptopp to prefix dir
make -f GNUmakefile PREFIX=$PREFIX distclean
make -f GNUmakefile PREFIX=$PREFIX CXX=$CXX CXXFLAGS=$CXXFLAGS -j`nproc`
make -f GNUmakefile PREFIX=$PREFIX CXX=$CXX CXXFLAGS=$CXXFLAGS -j`nproc` install
