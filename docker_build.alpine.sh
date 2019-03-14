#!/bin/sh
patch -p1 < no_rpc.diff
PWD=`pwd`
docker run -d -v ${PWD}:/srv alpine:3.8 sh /srv/build.alpine.sh
