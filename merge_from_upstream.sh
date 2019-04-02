#!/bin/sh
UPSTREAM="https://github.com/bitcoin/bitcoin.git"
if [ $1 ]; then
  BRANCH="$1"
else
  BRANCH="master"
fi

git pull $UPSTREAM $BRANCH
