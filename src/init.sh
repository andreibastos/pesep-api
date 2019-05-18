#!/bin/bash

# verifica se tem o direitorio src e entra
if [ -d "src" ]; then
    cd src
fi

# baixa o ampl
sh get_ampl.sh

# compila o CC
sh compile_cc.sh