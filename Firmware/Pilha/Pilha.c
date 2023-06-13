//
// Created by mirai on 29/05/23.
//
#include "Pilha.h"

bool inicializar_pilha(struct Pilha* stack){
    stack->tam = 0;
    stack->tam_max = 64;
    for(int i = 0; i < 64; i++){
        stack->conteiner[i] = 0;
    }

    return true;
}

bool empilhar(struct Pilha* stack, char elemento){
    if(stack->tam >= stack->tam_max){
        printf("Estouro de pilha!\n");
        return false;
    }
    stack->conteiner[stack->tam] = elemento;
    stack->tam++;
    return true;
}

char desempilhar(struct Pilha* stack){
    if(stack->tam <= 0){
        printf("Pilha vazia!\n");
        return false;
    }
    stack->tam--;
    return stack->conteiner[stack->tam];
}

bool exibir_pilha(struct Pilha* stack){
    if(stack->tam == 0){
        printf("Pilha vazia!\n");
        return false;
    }

    for(int i = 0; i < stack->tam; i++){
        printf("%c ", stack->conteiner[i]);
    }
    printf("\n");
    return true;
}