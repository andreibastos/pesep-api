#!/bin/bash
dir=$1;

./FPO.sh $dir

mkdir -p $dir

cp ../dist/* $dir/

cd $dir 

./CC >> log_CC.txt

rm CC
