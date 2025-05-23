@echo off
setlocal

:: Change this value so that the file name it stores points to your vcpkg.cmake
set "vcpkg_cmake=C:/DevPacks/vcpkg/scripts/buildsystems/vcpkg.cmake"

if exist "%vcpkg_cmake%" (
	cmake -S . -B Build_mingw -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="%vcpkg_cmake%" -DVCPKG_TARGET_TRIPLET=x64-mingw -DCMAKE_EXPORT_COMPILE_COMMANDS=1
	move Build_mingw\compile_commands.json .\
) else (
	echo +-------------------------------------------------------------
	echo ^| "%vcpkg_cmake%" not exists.
	echo ^| Edit cmake-windows.bat and modify the value of vcpkg_cmake.
	echo +-------------------------------------------------------------
)

endlocal
pause
