[![Build CMake IEC61499 Runtime](https://github.com/rossonet/Iec61499-runtime/actions/workflows/cmake_posix.yml/badge.svg)](https://github.com/rossonet/Iec61499-runtime/actions/workflows/cmake_posix.yml)

# Building 4DIAC Forte

## Standard POSIX build

    ./setup_posix.sh
    cd bin/posix
    make

## Resetting CMake files

In case you ran CMake with invalid options it might help
to reset the CMake state by deleting CMake intermediate
files:

    rm -Rf CMakeCache.txt CMakeFiles/

## Building a local RPM

For building local RPMs you can use (tito)[https://github.com/dgoodwin/tito]

    tito build --test --rpm


