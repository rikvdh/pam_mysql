#!/bin/bash

set -xe

sudo apt-get update -qq || true
sudo apt-get install -qq -y --no-install-recommends libpam-dev

if [[ "$CC" == "scan-build" ]]; then
    unset CC
    unset CXX

    mkdir build
    cd build
    cmake ..
    scan-build -o analysis --status-bugs make
elif [[ "$CC" == "debian" ]]; then
    unset CC
    unset CXX

    sudo apt-get install -qq -y devscripts

    debuild --no-lintian -us -uc -b
else
    mkdir build
    cd build
    cmake ..
    make
    make test
fi
