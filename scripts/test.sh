INC="/root/iris/include/"
BIN="/root/iris/bin/test"
TGT="/root/iris/tests/*"

# Remove bin file if it exists
if [ -f "$BIN" ]
then
    rm $BIN
fi

# Check if a specific test was passed
if [ $1 ]
then
    TGT="${TGT%?}$1"
fi

# Compile and execute each file in tests dir
for FILE in $TGT
do
    if [ -f "$FILE" ] && ! [ "$FILE" == w64* ]
    then
        echo -e "\033[36m[C] Compiling\t$FILE\033[0m"
        g++ -Wall -I $INC $FILE -o $BIN -lpthread -lcryptopp

        if [ -f "$BIN" ]
        then
            echo -e "\033[37m[E] Executing\t$FILE\033[0m"
            $BIN

            if [ $? -eq 0 ]; then
                echo -e "\033[32m[P] Passed\t$FILE\033[0m"
            else
                echo -e "\033[33m[F] Failed\t$FILE\033[0m"
            fi

            if [ -f "$BIN" ]
            then
                rm $BIN
            fi
        else
            echo -e "\033[31m[C] Failed\t$FILE\033[0m"
        fi
    fi
done
