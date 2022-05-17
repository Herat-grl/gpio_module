#!/bin/sh
./run.sh
rmmod phy_intr
insmod phy_intr.ko
gcc user.c -o user
