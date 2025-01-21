# Build process
```sh
mkdir build # Create build folder
cmake -B build # Only necessary on first compilation, or after changing the build process in CMakeLists.txt
cmake --build build # add `-t [build-server | build-client]` to build a specific target
./build/bin/client # Run
```
