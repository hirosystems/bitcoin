#!/bin/sh
PWD=`pwd`
git checkout src/rpc/blockchain.cpp
git checkout src/rpc/client.cpp
git checkout src/rpc/net.cpp
CHECK_NAME=`docker ps | grep bitcoin_builder > /dev/null`
if [ $? -eq "0" ]; then
  docker stop bitcoin_builder && docker rm bitcoin_builder
fi
if [ "$1" == "--with-diff" ];then
  patch -p1 < no_rpc.diff
  docker run -d -v ${PWD}:/srv --name bitcoin_builder alpine sh /srv/build.alpine.sh --with-diff
else
  docker run -d -v ${PWD}:/srv --name bitcoin_builder alpine sh /srv/build.alpine.sh
fi
docker logs -f bitcoin_builder
