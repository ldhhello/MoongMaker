#!/bin/sh

#cd ./src

echo $(pwd)

#sudo docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) emscripten/emsdk em++ /src/main.cpp -I/src -o wasm.js -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s EXPORT_ALL=1 -DWASM_BUILD -pthread -s PROXY_TO_PTHREAD -Wno-int-conversion -Wno-implicit-function-declaration -Wno-invalid-source-encoding -O2 -s EXTRA_EXPORTED_RUNTIME_METHODS=FS
sudo docker run --rm -v $(pwd):/src -u $(id -u):$(id -g) emscripten/emsdk em++ src/*.cpp -Isrc -o wasm.js -s "EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s EXPORT_ALL=1 -DWASM_BUILD -Wno-int-conversion -Wno-implicit-function-declaration -Wno-invalid-source-encoding -O2 -s EXTRA_EXPORTED_RUNTIME_METHODS=FS -sASSERTIONS -sALLOW_MEMORY_GROWTH
