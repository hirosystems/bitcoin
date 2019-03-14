#!/bin/sh
patch -p1 < no_rpc.diff
PWD=`pwd`
docker run -d -v ${PWD}:/srv debian sh /srv/build.debian.sh
