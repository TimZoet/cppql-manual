> mkdir build
> cd build
> cmake
  -DBUILD_TESTS=ON
  -DBUILD_EXAMPLES=ON 
  -DCMAKE_TOOLCHAIN_FILE=path/to/vcpkg.cmake
  ../source
> cmake --build .