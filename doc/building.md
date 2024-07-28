# :floppy_disk: Building
To build `slc` the user must make sure that the following are installed on their
machine:
  - CMake
  - libpng
  - gtest (if the user wishes to compile the tests, see compiling without tests
    below)
  - gcc (linux only)
  - gnumake (linux only)

## :question: Installing CMake/Required Libraries
For those who use `apt` as their package manager, the following ought to work:
```
sudo apt update && sudo apt upgrade # not strictly necessary, but good idea
sudo apt install gcc make cmake libpng-dev
sudo apt install libgtest-dev # if the user wishes to build the tests
```

It should be quite similar for other package managers, usually C/C++ will follow
the naming pattern of `lib{LIBRARY_NAME}-dev`.

# :sparkles: Compilation

## With Compiling Tests
```
mkdir build # or whatever you want the build garbage to go into
cd build
cmake ..
make
```
The binaries `tests` and `slc` will be made in the `build/` directory.

## Without Compiling Tests
```
mkdir build # or whatever you want the build garbage to go into
cd build
cmake -DBUILD_TESTS=OFF ..
make
```
The binary `slc` will be made in the `build/` directory.
