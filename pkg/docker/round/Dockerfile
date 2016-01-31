FROM cybergarage/round-dev:latest
MAINTAINER Satoshi Konno <skonno@cybergarage.org>

# mUPnP for C
WORKDIR /root
WORKDIR mupnp
RUN git pull
RUN ./configure_linux && make && make install
WORKDIR /root
RUN rm -rf mupnp

# Round
WORKDIR /root
WORKDIR round
RUN git pull
RUN ./configure_linux && make && make install
WORKDIR /root
RUN rm -rf round

WORKDIR /root
