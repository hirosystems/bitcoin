#!/bin/sh -x

cd /srv/
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
  libc-dev
/sbin/ldconfig /usr/lib /lib
echo ""
echo "Running autogen"
echo ""
sh autogen.sh
echo ""
echo "Configuring bitcoin"
echo ""
./configure \
  --enable-util-cli \
  --disable-gui-tests \
  --disable-wallet \
  --enable-static \
  --disable-tests \
  --without-miniupnpc \
  --disable-shared \
  --with-pic \
  --enable-cxx \
  LDFLAGS="-static-libstdc++" \
  CXXFLAGS="-static-libstdc++"
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
