rmdir /S /Q build
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -G "NMake Makefiles" ..
cd ..