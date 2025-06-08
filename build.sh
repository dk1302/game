rm -rf build
rm Game
mkdir build
cmake -DCMAKE_BUILD_TYPE=Debug -B build
cd build
make all
cp Game ..
cd ..
