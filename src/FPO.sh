#!/bin/bash
dir=$1;

mkdir -p $dir

cp math/FPO/* $dir/ 

cd $dir
../../../../ampl/ampl FPO.mod >> log_FPO.txt

rm *.mod *.dat