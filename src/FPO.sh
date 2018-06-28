#!/bin/bash
dir=$1;

mkdir -p $dir

cp math/FPO/* $dir/ 

cd $dir
ls $PWD
../../../../ampl/ampl FPO.mod