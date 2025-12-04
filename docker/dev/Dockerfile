FROM debian:bookworm
WORKDIR /root/iris

# Update apt
RUN apt update
RUN apt -y upgrade
RUN apt -y dist-upgrade

# Add g++
RUN apt -y install g++

# Add mingw
RUN apt -y install mingw-w64

# Add compile deps
RUN apt -y install make
RUN apt -y install git
RUN apt -y install unzip zip

# Keep container open
ENTRYPOINT sleep infinity
