FROM gcc:bookworm
WORKDIR /root/iris
# Update apt
RUN apt update
RUN apt -y upgrade
RUN apt -y dist-upgrade
# Install cryptopp deps
RUN apt -y install libcrypto++-dev libcrypto++-doc libcrypto++-utils
ENTRYPOINT tail -f /dev/null