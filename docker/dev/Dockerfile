FROM gcc:bookworm
WORKDIR /root/iris

# Update apt
RUN apt update
RUN apt -y upgrade
RUN apt -y dist-upgrade

# Add mingw
RUN apt -y install mingw-w64

# Install cryptopp deps
RUN apt -y install libcrypto++-dev libcrypto++-doc libcrypto++-utils

# Keep container open
ENTRYPOINT tail -f /dev/null