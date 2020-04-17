#!/bin/sh
VERSION=`./src/bitcoind --version | head -1 | awk '{print $4}' |tr -d 'v' | cut -f1 -d "-"`
DIR="bitcoin-${VERSION}"
if [ "$1" == "--with-diff" ];then
  DIR="bitcoin-${VERSION}-no-rpc"
else
  DIR="bitcoin-${VERSION}"
fi
if [ -d "${DIR}" ]; then
  rm -rf ${DIR}
fi
if [ -f ${DIR}.tar ]; then
  rm -f ${DIR}.tar
fi
if [ -f ${DIR}.tar.gz ]; then
  rm -f ${DIR}.tar.gz
fi
mkdir -p ${DIR}/bin
mkdir -p ${DIR}/include
mkdir -p ${DIR}/share/man/man1
strip src/bitcoind 
strip src/bitcoin-cli
strip src/bitcoin-tx
cp -a src/bitcoind ${DIR}/bin/
cp -a src/bitcoin-cli ${DIR}/bin/
cp -a src/bitcoin-tx ${DIR}/bin/
cp -a src/script/bitcoinconsensus.h ${DIR}/include/
cp -a doc/man/bitcoin-cli.1 ${DIR}/share/man/man1/
cp -a doc/man/bitcoin-tx.1 ${DIR}/share/man/man1/
cp -a doc/man/bitcoind.1 ${DIR}/share/man/man1/
tar -cf ${DIR}.tar ${DIR} && gzip ${DIR}.tar
rm -rf ${DIR}
