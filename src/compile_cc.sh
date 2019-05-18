#!/bin/bash

if [ -d "src" ]; then
    cd src
fi

DIST_DIR=../dist

mkdir -p $DIST_DIR

# compila o arquivo CC.cpp para a pasta $DIST_DIR com o nome CC
g++ ./math/CC/CC.cpp -o $DIST_DIR/CC

# deixa o CC como executável
chmod +x $DIST_DIR/CC