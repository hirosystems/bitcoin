#!/bin/sh
PWD=`pwd`
docker run -d -v ${PWD}:/srv alpine sh /srv/build.alpine.sh
