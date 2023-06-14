#!/bin/bash

# Function to check if a command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to check if the script is running in a Windows environment
is_windows() {
    case "$OSTYPE" in
        msys*|cygwin*|mingw*|win*) return 0 ;;
        *) return 1 ;;
    esac
}

# Read tag value from file
version_file="./version"
if [[ ! -f "$version_file" ]]; then
    echo "Version file not found: $version_file"
    exit 1
fi

tag=$(cat "$version_file")
echo "Local tag: $tag"

# Fetch the latest tag from the GitHub API
repo_owner="ramity"
repo_name="iris"
api_url="https://api.github.com/repos/$repo_owner/$repo_name/releases/latest"
if command_exists curl; then
    latest_tag=$(curl -s "$api_url" | grep '"tag_name":' | sed -E 's/.*"([^"]+)".*/\1/')
elif command_exists wget; then
    latest_tag=$(wget -qO- "$api_url" | grep '"tag_name":' | sed -E 's/.*"([^"]+)".*/\1/')
else
    echo "Neither curl nor wget found. Please install either of them and try again."
    exit 1
fi

echo "Latest remote tag: $latest_tag"

# Compare tags
if [[ "$tag" == "$latest_tag" ]]; then
    echo "Your version is up to date."
else
    echo "Your version is not up to date."
    read -p "Do you want to download the latest version? (y/n) " choice

    if [[ $choice =~ ^[Yy]$ ]]; then
        # Download and unzip the latest version
        if is_windows; then
            os="windows"
        else
            os="linux"
        fi

        download_url="https://github.com/$repo_owner/$repo_name/releases/download/$latest_tag/$os-64.zip"
        mkdir ./tmp
        zip_file="./tmp/$os-64.zip"

        echo "Downloading $latest_tag"
        if command_exists curl; then
            curl -s -L -o "$zip_file" "$download_url"
        elif command_exists wget; then
            wget -q -O "$zip_file" "$download_url"
        else
            echo "Neither curl nor wget found. Please install either of them and try again."
            exit 1
        fi

        echo "Unzipping $latest_tag..."
        unzip -q -u "$zip_file" -d .

        echo "Cleaning up..."
        rm -rf "./tmp"

        echo "Download complete."
    else
        echo "You chose not to download the latest version."
    fi
fi
