origin=$(pwd)
cd open62541
mkdir build && cd $_
cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Debug -DUA_ENABLE_AMALGAMATION=ON ..
make -j
cd $origin
