#!/bin/bash

if [[ "$OSTYPE" == "linux-gnu" ]]; then
    # Linux-specific executable
    echo "linux"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS-specific executable
    echo "mac"
elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    # Windows-specific executable
    echo "windows"
else
    echo "Unsupported operating system: $OSTYPE"
fi