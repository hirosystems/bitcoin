#!/bin/sh -x

check_exit() {
    RET=$1
    if [ $RET -ne 0 ];then
        exit $RET
    fi
}

WITH_MUSL=1
OPTS=""
SUFFIX=""
PROM_CPP="prometheus-cpp"


for arg in "$@"; do
  case $arg in
      "-glibc" )
        WITH_MUSL=0;;
      "-bdb-version="* )
         BERKELEYDB_VERSION="${arg#*=}";;
      "-h" )
         echo "$0 <options>"
         echo " -glibc      Build binaries with GLIBC"
         echo " -bdb-version=[db-4.8.30.NC]   Version of Berkeley DB to use [ default: db-4.8.30.NC ]"
         exit 0;;
  esac
done

echo ""
echo ""
echo "Script Vars:"
echo "WITH_MUSL: $WITH_MUSL"
echo "BERKELEYDB_VERSION: $BERKELEYDB_VERSION"
echo ""
echo ""

echo ""
echo "Building Berkeley DB Version:$BERKELEYDB_VERSION"
echo ""
wget https://download.oracle.com/berkeley-db/${BERKELEYDB_VERSION}.tar.gz -O /tmp/${BERKELEYDB_VERSION}.tar.gz
tar -xzf /tmp/${BERKELEYDB_VERSION}.tar.gz -C /tmp/
sed s/__atomic_compare_exchange/__atomic_compare_exchange_db/g -i /tmp/${BERKELEYDB_VERSION}/dbinc/atomic.h
cd /tmp/${BERKELEYDB_VERSION}/build_unix
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr
make -j4
check_exit $?
make install
check_exit $?



echo ""
echo "Building prometheus-cpp libraries"
echo ""
git clone https://github.com/jupp0r/prometheus-cpp ${PROM_CPP}
check_exit $?
cd ${PROM_CPP}
git submodule init
check_exit $?
git submodule update
check_exit $?
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_PREFIX=/usr .. -DBUILD_SHARED_LIBS=ON
check_exit $?
make -j 4
check_exit $?
make install

export PROM_CPPFLAGS="-I/usr/include/prometheus"

cd ${BTC_DIR}
echo ""
echo "Building BTC Version:$BTC_VERSION${SUFFIX}"
echo ""
echo ""
echo "Running autogen"
echo ""
sh autogen.sh
check_exit $?

echo ""
echo "Configuring bitcoin"
echo ""
./configure \
    --with-boost \
    --with-boost-thread \
    --enable-util-cli $OPTS \
    --disable-gui-tests \
    --enable-static \
    --disable-tests \
    --disable-bench \
    --without-miniupnpc \
    --disable-shared \
    --with-pic \
    --enable-cxx \
    CPPFLAGS="${PROM_CPPFLAGS}" \
    LDFLAGS="-lprometheus-cpp-pull -lprometheus-cpp-push -lprometheus-cpp-core -lcurl -lz -static-libstdc++"
check_exit $?

echo ""
echo "Compiling bitcoin"
echo ""
make STATIC=1
check_exit $?
make install
check_exit $?

cd /tmp
if [ -d /tmp/${BERKELEYDB_VERSION} ]; then
    echo "Removing Dir: /tmp/${BERKELEYDB_VERSION}"
    rm -rf /tmp/${BERKELEYDB_VERSION}
fi
if [ -f /tmp/${BERKELEYDB_VERSION}.tar.gz ]; then
    echo "Removing File: /tmp/${BERKELEYDB_VERSION}.tar.gz"
    rm -f /tmp/${BERKELEYDB_VERSION}.tar.gz
fi
if [ -d ${PROM_CPP} ]; then
    echo "Removing Dir: ${PROM_CPP}"
    rm -rf ${PROM_CPP}
fi
if [ -d ${BTC_DIR} ]; then
    echo "Removing Dir: ${BTC_DIR}"
    rm -rf ${BTC_DIR}
fi
exit 0
