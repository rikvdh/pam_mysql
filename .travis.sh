#!/bin/bash
sudo apt-get update -qq || true
sudo apt-get install -qq -y --no-install-recommends libpam-dev

if [[ "$CC" == "scan-build" ]]; then
    unset CC
    unset CXX

    scan-build -o analysis --status-bugs ./configure --prefix=/usr --with-openssl --with-pam_mods_dir=/lib/security --with-pam=/usr
    scan-build -o analysis --status-bugs make
elif [[ "$CC" == "debian" ]]; then
    unset CC
    unset CXX

    sudo apt-get install -qq -y devscripts

    debuild --no-lintian -us -uc -b
else
    export CFLAGS="-Wall -Wextra -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -pie -fPIE -Wl,-z,relro -Wl,-z,now -fPIC -O2"
    ./configure --prefix=/usr --with-openssl --with-pam_mods_dir=/lib/security --with-pam=/usr
    make
fi
