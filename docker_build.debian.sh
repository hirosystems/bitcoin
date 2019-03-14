#!/bin/sh
PWD=`pwd`
docker run -d -v ${PWD}:/srv debian sh /srv/build.debian.sh
