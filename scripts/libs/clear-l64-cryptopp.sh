DIR="/root/iris/libs/linux/cryptopp"

# remove dir and files within if it exists
if [ -d "$DIR" ]
then
    rm -r -d $DIR
fi
