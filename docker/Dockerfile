FROM alpine
ARG BTC_VERSION
ENV LD_LIBRARY_PATH="/usr/lib64"
ENV BTC_CONF="/etc/bitcoin.conf"
ENV BTC_DATA="/root/.bitcoin"
ENV BTC_PID="/run/bitcoind.pid"
ENV BTC_VERSION=${BTC_VERSION}
ENV BTC_DIR="/src/bitcoin"
ENV BERKELEYDB_VERSION="db-4.8.30.NC"

# hardcode for now
ENV BTC_VERSION=21.99.0.0

WORKDIR /
COPY . ${BTC_DIR}
COPY docker/docker-build.sh /build.sh
RUN apk --no-cache add --update \
    autoconf \
    automake \
    boost-dev \
    boost-chrono \
    boost-filesystem \
    boost-system \
    boost-thread \
    cmake \
    curl \
    curl-dev \
    czmq-dev \
    db-c++ \
    g++ \
    gcc \
    git \
    libc-dev \
    libevent \
    libevent-dev \
    libgcc \
    libtool \
    libzmq \
    linux-headers \
    make \
    musl-dev \
    openssl \
    openssl-dev \
    patch \
    pkgconf \
    pkgconf-dev \
    zlib-dev \
    && sh /build.sh

RUN apk del \
    autoconf \
    automake \
    boost-dev \
    cmake \
    curl-dev \
    czmq-dev \
    g++ \
    gcc \
    git \
    libc-dev \
    libevent-dev \
    libtool \
    linux-headers \
    make \
    musl-dev \
    openssl \
    openssl-dev \
    patch \
    pkgconf \
    pkgconf-dev \
    zlib-dev \
    && rm -f /build.sh

CMD ["/bin/sh", "-c", "bitcoind -conf=${BTC_CONF} -pid=${BTC_PID} -datadir=${BTC_DATA}"]
