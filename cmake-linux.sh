#!/bin/bash

# Change this value so that the file name it stores points to your vcpkg.cmake
vcpkg_cmake="/home/wheat_box/DevPacks/vcpkg/scripts/buildsystems/vcpkg.cmake"

if [ -e "$vcpkg_cmake" ]; then
	cmake -S . -B Build -DCMAKE_TOOLCHAIN_FILE="$vcpkg_cmake"
else
	echo +-------------------------------------------------------------
	echo "|" "$vcpkg_cmake" not exists.
	echo "|" Edit cmake-windows.bat and modify the value of vcpkg_cmake.
	echo +-------------------------------------------------------------
fi

read -p "Press [Enter] key to continue..."
