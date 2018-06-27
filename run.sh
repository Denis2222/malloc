#!/usr/bin/env bash

if [ "$(uname)" == "Darwin" ]; then
    export DYLD_LIBRARY_PATH=.
    export DYLD_INSERT_LIBRARIES="libft_malloc.so"
    export DYLD_FORCE_FLAT_NAMESPACE=1
    $@
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    export LD_PRELOAD="./libft_malloc.so"
    $@
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
    @echo "Not test"
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    @echo "Not test"
fi
