
START LOCALL
https://pytorch.org/get-started/locally/

INSTALLING C++ DISTRIBUTIONS OF PYTORCH
https://pytorch.org/cppdocs/installing.html

mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=/home/seba/Repositories/libtorch ..
cmake --build . --config Release
