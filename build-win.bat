@echo off
echo #Cleaning building cache...
rmdir /S /Q build
mkdir build

echo #Adding cmake to path...
set path=%~dp0cmake\bin;%path%
set path
cd build
echo #Generating Makefile
cmake .. -G"MinGW Makefiles"
echo #Building...
mingw32-make -j2
copy htcli.exe ..

pause
