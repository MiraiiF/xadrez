cmake_minimum_required(VERSION 3.2)
project(xadrez C)

set(CMAKE_C_STANDARD 11)

add_executable(xadrez main.c Tabuleiro/Tabuleiro.h Tabuleiro/Tabuleiro.c Pilha/Pilha.c Pilha/Pilha.h examples.h Parser/Parser.c Parser/Parser.h)
