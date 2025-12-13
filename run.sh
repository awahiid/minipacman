#!/bin/bash

echo "MiniPacman - Compilando proyecto..."

mkdir -p bin

g++ -Wall -Wextra -std=c++17 -Iinclude src/*.cpp -o bin/main

if [ $? -eq 0 ]; then
    echo "✓ Compilación exitosa"
    echo ""
    echo "Ejecutando MiniPacman..."
    echo "========================================="
    cd bin
    ./main
else
    echo "✗ Error durante la compilación"
    exit 1
fi

