#!/bin/bash
# cria a pasta para o ampl
ampl="../ampl"

mkdir -p $ampl

# baixa o amplx64 para linux
wget -N https://ampl.com/demo/ampl.linux64.tgz -O $ampl/ampl.linux64.tgz

# # baixa o minos
# wget http://netlib.bell-labs.com/netlib/ampl/student/linux/minos.gz -O $ampl/minos.gz


# #baixa o ipsolve
# wget http://netlib.bell-labs.com/netlib/ampl/student/linux/lpsolve.gz -O $ampl/lpsolve.gz

# extrai
tar -xvzf $ampl/ampl.linux64.tgz -C $ampl/
mv $ampl/ampl.linux64/* $ampl/
# gzip -c $ampl/minos.gz > $ampl/minos
# gzip -c $ampl/lpsolve.gz > $ampl/lpsolve

# remove os arquivos baixados tmps
rm $ampl/ampl.linux64/ -r 
rm $ampl/ampl.linux64.tgz
# rm $ampl/*.*gz