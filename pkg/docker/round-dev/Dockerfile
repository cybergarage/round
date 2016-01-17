FROM ubuntu:14.04.3
MAINTAINER Satoshi Konno <skonno@cybergarage.org>

# Update base packages
RUN apt-get update && apt-get upgrade -y

# Install base packages
RUN apt-get install -y git g++ make automake autoconf
RUN apt-get install -y pkg-config
RUN apt-get install -y libboost-all-dev

# Set Packaging ENV
ENV DEBFULLNAME "Satoshi Konno"
ENV DEBEMAIL skonno@cybergarage.org

# Git configuration
RUN git config --global user.email "skonno@cybergarage.org"
RUN git config --global user.name "Satoshi Konno"
RUN git config --global credential.helper cache

# mUPnP for C
RUN apt-get install -y libxml2-dev
WORKDIR /root
RUN git clone https://github.com/cybergarage/mupnpc.git mupnp

# Round
RUN apt-get install -y libboost-all-dev libssl-dev libjansson-dev libxml2-dev
RUN apt-get install -y libmozjs185-dev python-dev
RUN apt-get install -y libedit-dev
WORKDIR /root
#RUN git clone https://github.com/cybergarage/round.git round
COPY round /root/round

WORKDIR /root

