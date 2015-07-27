rm -rf build
rm htcli
mkdir build
cd build
cmake ..
make -j4
ln -s -t .. ./htcli
