FROM debian:bookworm
WORKDIR /root/iris

# Update apt
RUN apt update
RUN apt -y upgrade
RUN apt -y dist-upgrade

# Add g++ w/ both 32 and 64 bit support
RUN apt -y install g++-multilib

# Add mingw
RUN apt -y install mingw-w64

# Install cryptopp deps
RUN apt -y install libcrypto++-dev libcrypto++-doc libcrypto++-utils

# Keep container open
ENTRYPOINT tail -f /dev/null
