#!/bin/bash
#sudo apt-get update -qq || true
#sudo apt-get install -qq -y --no-install-recommends libpam-dev

if [[ "$CC" == "scan-build" ]]; then
    unset CC
    unset CXX

    ./configure --prefix=/usr --with-openssl --with-pam_mods_dir=/lib/security --with-pam=/usr
    scan-build -o analysis --status-bugs make
elif [[ "$CC" == "debian" ]]; then
    unset CC
    unset CXX

    debuild --no-lintian -us -uc -b
else
    ./configure --prefix=/usr --with-openssl --with-pam_mods_dir=/lib/security --with-pam=/usr
    make
fi
