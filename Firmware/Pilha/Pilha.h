//
// Created by mirai on 29/05/23.
//

#ifndef XADREZ_PILHA_H
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

struct Pilha{
    char conteiner[64];
    int tam;
    int tam_max;
};

bool inicializar_pilha(struct Pilha* stack); //STACK INIT

bool empilhar(struct Pilha* stack, char elemento); //PUSH

char desempilhar(struct Pilha* stack); //POP

bool exibir_pilha(struct Pilha* stack); //SHOW CONTENT

#define XADREZ_PILHA_H

#endif //XADREZ_PILHA_H
