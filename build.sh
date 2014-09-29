#!/bin/bash

BASE_VER="KANGAROO.M7.MKIV.v067"
VER=""
KERNEL_VER=$BASE_VER$VER

export LOCALVERSION="."`echo $KERNEL_VER`
export CROSS_COMPILE=${HOME}/Toolchains/arm-cortex_a15-linux-gnueabihf-linaro_4.9.2-2014.09/bin/arm-cortex_a15-linux-gnueabihf-

export ARCH=arm
export SUBARCH=arm
export KBUILD_BUILD_USER=poondoge
# export KBUILD_BUILD_HOST="semaphore.gr"

DATE_START=$(date +"%s")

make "m7_defconfig"

echo "LOCALVERSION="$LOCALVERSION
echo "CROSS_COMPILE="$CROSS_COMPILE
echo "ARCH="$ARCH

make -j1

DATE_END=$(date +"%s")
echo
DIFF=$(($DATE_END - $DATE_START))
echo "  Build completed in $(($DIFF / 60)) minutes and $(($DIFF % 60)) seconds."
echo
