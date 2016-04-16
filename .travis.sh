sudo apt-get update -qq || true
sudo apt-get install -qq -y --no-install-recommends libpam-dev
./configure --prefix=/usr --with-openssl --with-pam_mods_dir=/lib/security --with-pam=/usr
make
