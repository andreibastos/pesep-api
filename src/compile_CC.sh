#!/bin/bash

mkdir -p ../dist/

# compila o arquivo CC.cpp para a pasta ../dist/ com o nome CC
g++ ./math/CC/CC.cpp -o ../dist/CC

# deixa o CC como executável
chmod +x ../dist/CC