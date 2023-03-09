#!/bin/bash

sudo apt update

sudo apt instal autoconf
sudo apt-get install libtool

git clone https://gitlab.com/lely_industries/lely-core.git
cd lely-core
autoreconf -i
./configure --disable-cython

make
make check
make html
sudo make install

