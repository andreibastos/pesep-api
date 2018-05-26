#!/bin/bash
dir=$1;

mkdir -p $dir

cp math/FPO.mod math/dados.dat $dir/ 

cd $dir
ls
../../ampl/ampl FPO.mod