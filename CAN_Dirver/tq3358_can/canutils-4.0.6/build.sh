#!/bin/sh

export PKG_CONFIG_PATH=/opt/EmbedSky/4.4.6/arm-embedsky-linux-gnueabi/embedsky/usr/lib/pkgconfig/
./configure --host=arm-linux --prefix=`pwd`/../__install --enable-debug &&
make &&
make install
