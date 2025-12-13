# MiniPacman

Un proyecto educativo que implementa algoritmos de búsqueda e inteligencia artificial para resolver el juego Pacman.

## Descripción

Este proyecto es una herramienta para aprender cómo funcionan diferentes algoritmos de búsqueda y técnicas de inteligencia artificial. Implementa varias estrategias de resolución para el juego clásico de Pacman:

- **Escalada Simple**: Algoritmo greedy básico
- **Máxima Pendiente (Recursivo)**: Búsqueda con backtracking
- **Máxima Pendiente (Iterativo)**: Versión iterativa del anterior
- **Movimientos Aleatorios**: Búsqueda aleatoria
- **Búsqueda en Anchura Modificada**: Algoritmo greedy priorizado por distancia

## Compilación y Ejecución

### Opción 1: Usando Makefile

```bash
make
```

Para ejecutar:

```bash
make run
```

Para limpiar archivos compilados:

```bash
make clean
```

### Opción 2: Usando el script

```bash
./run.sh
```

## Requisitos

- Compilador C++ (g++, clang, etc.)
- Make (para usar el Makefile)

## Estructura del Proyecto

```
├── src/              # Código fuente C++
├── include/          # Archivos header
├── layouts/          # Mapas del juego (MINIPAC1-10)
├── bin/              # Ejecutables compilados
├── Makefile          # Instrucciones de compilación
└── run.sh            # Script para compilar y ejecutar
```

## Autor

Abdel Wahed Mahfoud Mouhandizi

## Institución

Escuela Politécnica - Universidad de Extremadura

