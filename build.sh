cmake -S . -B build -DSDLTTF_VENDORED=ON -DSDLMIXER_VENDORED=ON
cd build
make 
cd ..
mv build/src/tetris tetris
