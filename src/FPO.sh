#!/bin/bash
if [ -d "src" ]; then
    cd src
fi

# recebe a pasta que deve ser criada como pârametro
dir=$1;

# cria a pasta com o parâmetro recebido
mkdir -p $dir

# copia os arquivos necessários para cálculo do FPO para a nova pasta
cp math/FPO/* $dir/ 

# navega até a pasta
cd $dir

# executa FPO chamando o AMPL e imprime o log no arquivo de log_FPO.txt
../../../../ampl/ampl FPO.mod >> log_FPO.txt

# remove os arquivos de entrada
rm *.mod *.dat