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
    mkdir -p build/Debug
    mkdir -p build/Release
    cd build/Debug
    if [[ "$CC" == "gcc" ]]; then
        pip install --user cpp-coveralls urllib3[secure] || exit $?

        cmake -DCMAKE_BUILD_TYPE=Debug -DENABLE_CODECOVERAGE=ON ../..
        make
        make test
        coveralls --gcov-options "--object-directory CMakeFiles/pam_mysql.dir" -r ../../ -b . -i ../..
    else
        cmake -DCMAKE_BUILD_TYPE=Debug ../..
        make
        make test
    fi

    cd ../Release
    cmake -DCMAKE_BUILD_TYPE=Release ../..
    make
    make test
fi
