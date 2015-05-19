#!/bin/sh
QUICKY_REPOSITORY=`pwd`/sources
export QUICKY_REPOSITORY
cd ${QUICKY_REPOSITORY}/quicky_tools/setup
. setup.sh
cd ../../..
#EOF
