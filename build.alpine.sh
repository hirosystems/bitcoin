#!/bin/sh -x

echo ""
echo "Installing Required libraries"
echo ""
apk --no-cache add --update \
  libgcc \
  boost-dev \
  boost-thread \
  boost-filesystem \
  boost-system \
  openssl \
  autoconf \
  libtool \
  pkgconf \
  pkgconf-dev \
  libevent \
  git \
  czmq-dev \
  libzmq \
  gcc \
  g++ \
  openssl-dev \
  libevent-dev \
  make \
  automake \
  musl-dev \
  linux-headers \
  libc-dev \
  db-c++
/sbin/ldconfig /usr/lib /lib

OPTS=""
if [ "$1" == "--with-diff" ];then
  OPTS="--disable-wallet"
else
  # OPTS="--with-incompatible-bdb"
  BERKELEYDB_VERSION="db-4.8.30.NC"
  BERKELEYDB_PREFIX="/opt/${BERKELEYDB_VERSION}"
  wget https://download.oracle.com/berkeley-db/${BERKELEYDB_VERSION}.tar.gz -O /tmp/${BERKELEYDB_VERSION}.tar.gz
  tar -xzf /tmp/${BERKELEYDB_VERSION}.tar.gz -C /tmp/
  sed s/__atomic_compare_exchange/__atomic_compare_exchange_db/g -i /tmp/${BERKELEYDB_VERSION}/dbinc/atomic.h
  mkdir -p ${BERKELEYDB_PREFIX}
  cd /tmp/${BERKELEYDB_VERSION}/build_unix
  ../dist/configure --enable-cxx --disable-shared --with-pic --prefix=${BERKELEYDB_PREFIX}
  make -j4
  make install
  /sbin/ldconfig /usr/lib /lib ${BERKELEYDB_PREFIX}/lib
fi

cd /srv/
echo ""
echo "Running autogen"
echo ""
sh autogen.sh
echo ""
echo "Configuring bitcoin"
echo ""
./configure \
  --enable-util-cli $OPTS \
  --disable-gui-tests \
  --enable-static \
  --disable-tests \
  --without-miniupnpc \
  --disable-shared \
  --with-pic \
  --enable-cxx \
  LDFLAGS="-L${BERKELEYDB_PREFIX}/lib/ -static-libstdc++" \
  CPPFLAGS="-I${BERKELEYDB_PREFIX}/include/ -static-libstdc++"
echo ""
echo "Compiling bitcoin"
echo ""
make STATIC=1
echo ""
echo "Creating Binary dist"
echo ""
if [ "$1" == "--with-diff" ];then
  sh -x make_binary_dist.sh --with-diff
fi
sh -x make_binary_dist.sh
echo ""
echo "Cleaning up"
echo ""
make distclean
