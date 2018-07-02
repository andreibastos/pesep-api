#!/bin/bash

# recebe a pasta que deve ser criada como pârametro
dir=$1; 

# cria a pasta com o parâmetro recebido
mkdir -p $dir

# calcula o fluxo de potência para obter a matriz de susceptancia 
./FPO.sh $dir

# copia o compilado do CC para a nova pasta
cp ../dist/* $dir/

# navega até a pasta
cd $dir 

# executa o curto e imprime o log no arquivo de log_CC.txt
./CC >> log_CC.txt

# remove o arquivo compilado
rm CC
