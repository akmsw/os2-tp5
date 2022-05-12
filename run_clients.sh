#!/bin/bash

clear

echo "ingrese el puerto a conectarse"
read port

echo -e "\ningrese la cantidad de clientes a instanciar"
read clients_amount

echo -e "\nincrementando contador..."

for ((i = 0; i < clients_amount; i++))
do
    curl -X POST http://localhost:$port/increment &
done

wait

echo -e "\nresultado de contador incrementado:"

curl http://localhost:$port/print