#!/bin/bash

# Function to check if the script is running in a Windows environment

is_windows() {
    case "$OSTYPE" in
        msys*|cygwin*|mingw*|win*) return 0 ;;
        *) return 1 ;;
    esac
}

# Conditionally use ./iris or ./iris depending on if windows

if is_windows; then
    executable="./iris.exe"
else
    executable="./iris"
fi

# Display the iris help text

$executable --help

# Explain to the user the termination condition

echo "Type 'exit' or 'quit' to terminate the script."

# Enter a loop
# - Asks the user for iris arguments
# - Passes the arguments into iris
# - Repeats until user exits

while true; do

    echo -n ">>> "
    read args

    # Termination condition
    if [ "$args" == "exit" ] || [ "$args" == "quit" ]; then
        break
    fi

    $executable $args
done

# Add a pause to keep script from exiting before user can examine output

if is_windows; then
    read -n 1 -s -r -p "Press any key to continue..."
fi
