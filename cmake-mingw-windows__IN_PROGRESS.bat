echo "IN PROGRESS..."
cmake -S . -B Build -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=C:/DevPacks/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static
pause
