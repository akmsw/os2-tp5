#! /bin/bash

make clean && make && clear

echo "ingrese el número de puerto a utilizar"
read port

./lab5 $port