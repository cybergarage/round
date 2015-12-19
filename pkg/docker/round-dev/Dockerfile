FROM ubuntu:14.04.2
MAINTAINER Satoshi Konno <skonno@cybergarage.org>

# Update base packages
RUN apt-get update && apt-get upgrade -y

# Install base packages
RUN apt-get install -y git g++ make automake autoconf
RUN apt-get install -y libboost-all-dev

# Set Packaging ENV
ENV DEBFULLNAME "Satoshi Konno"
ENV DEBEMAIL skonno@cybergarage.org

# Git configuration
RUN git config --global user.email "skonno@cybergarage.org"
RUN git config --global user.name "Satoshi Konno"

# mUPnP for C
RUN apt-get install -y libxml2-dev
WORKDIR /root
RUN git clone https://github.com/cybergarage/mupnpc.git mupnp
WORKDIR mupnp
RUN ./bootstrap && ./configure && make && make install

# Round
RUN apt-get install -y libboost-all-dev libssl-dev libjansson-dev
RUN apt-get install -y libmozjs185-dev
WORKDIR /root
#RUN git clone https://github.com/cybergarage/round.git round
#RUN git pull
COPY round /root/round
WORKDIR round
RUN ./bootstrap && ./configure && make && make install

WORKDIR /root
