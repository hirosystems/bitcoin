#!/bin/sh
PWD=`pwd`
if [ "$1" == "--with-diff" ];then
  patch -p1 < no_rpc.diff
  docker run -d -v ${PWD}:/srv alpine sh /srv/build.alpine.sh --with-diff
else
  docker run -d -v ${PWD}:/srv alpine sh /srv/build.alpine.sh
fi
