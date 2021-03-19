#!/bin/sh
LOCAL_VERSION="VERSION"
FILE="../configure.ac"

if [ -f $FILE ]; then
  MAJOR=$(grep "define(_CLIENT_VERSION_MAJOR" $FILE  | awk '{print $2}' | tr -d \))
  MINOR=$(grep "define(_CLIENT_VERSION_MINOR" $FILE  | awk '{print $2}' | tr -d \))
  BUILD=$(grep "define(_CLIENT_VERSION_BUILD" $FILE  | awk '{print $2}' | tr -d \))
  RC=$(grep "define(_CLIENT_VERSION_RC" $FILE  | awk '{print $2}' | tr -d \))
else
  exit 3
fi
BTC_VERSION="${MAJOR}.${MINOR}.${BUILD}.${RC}"
echo $BTC_VERSION > $LOCAL_VERSION