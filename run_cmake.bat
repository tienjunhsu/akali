@echo off
"C:\Program Files\CMake\bin\cmake.exe" -G "Visual Studio 14" -DCMAKE_TOOLCHAIN_FILE=D:\sourcecode\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x86-windows -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=D:\ppx -DPPX_NO_HTTP=OFF -DPPX_NO_ENCRYPT=OFF -DPPX_NO_IPC=OFF -S %~dp0 -B %~dp0build