> mkdir build
> cd build
> cmake
  -DCMAKE_BUILD_TYPE=Release
  -DBUILD_TESTS=ON
  -DBUILD_EXAMPLES=ON 
  -DUSE_CONAN=ON
  ../source
> make