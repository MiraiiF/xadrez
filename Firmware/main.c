#include "Tabuleiro/Tabuleiro.h"
#define NUMERO_DE_CHECAGENS 3


//TABULEIRO
char tabuleiro[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '0'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};

//MATRIZ LIDA POR HARDWARE
bool presenca_de_pecas[8][8] = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
};


//DECLARAÇÃO DOS ESTADOS
void STATE_1(); //ESTADO QUE ESPERA A SAÍDA DE UMA PEÇA
void STATE_2(); //ESTADO QUE ESPERA A ENTRADA OU SAÍDA DE UMA PEÇA
void STATE_3(); //ESTADO QUE ESPERA A ENTRADA DE UMA PEÇA, APENAS E DECIDE SE FOI ROQUE OU CAPTURA
void STATE_4(); //MESMA COISA DO ESTADO 3, MAS NO CASO DE ROQUE

void (*state_pointer)(void) = STATE_1; //PONTEIRO DA MÁQUINA DE ESTADOS

//PILHA DE PEÇAS REMOVIDAS
struct Pilha pecas_fora;

char pacote[72];

int main() {
    inicializar_pilha(&pecas_fora); //INICIALIZA A PILHA
    while(1){
        atualiza_presencas(presenca_de_pecas); //FUNÇÃO A SER TROCADA PELA VARREDURA DO HARDWARE
        state_pointer(); //EXECUTA O ESTADO ATUAL
        detecta_promocao(tabuleiro); //DETECTA SE EXISTE ALGUM PEAO A SER PROMOVIDO
    }
}


void STATE_1(){ //ESTADO QUE DETECTA A SAIDA DE UMA PEÇA E DEMARCA O TÉRMINO DE UM MOVIMENTO
    parse_board(tabuleiro, pacote);
    //TODO: ENVIA STRING PACOTES
    printf("Estou no ESTADO 1!\n");
    int k = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            while((checa_saida(tabuleiro[i][j], presenca_de_pecas[i][j]))){ //se uma peça saiu...
                k++;
                atualiza_presencas(presenca_de_pecas); //VARREDURA
                if(k >= NUMERO_DE_CHECAGENS){ //checa NUMERO_DE_CHECAGENS vezes se a peça realmente saiu (por causa de erros de hardware)
                    int linha = i, coluna = j;
                    empilhar(&pecas_fora, atualiza_tabuleiro_saida(tabuleiro, linha, coluna)); //empilha peça que saiu
                    state_pointer = STATE_2; //vai ao estado 2
                    return;
                }
            }
            k = 0;
        }
    }
}

void STATE_2(){ //DETECTA SE A PEÇA QUE SAIU FEZ UM MOVIMENTO PADRÃO OU UMA CAPTURA
    printf("Estou no ESTADO 2!\n");
    int k = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            while((checa_saida(tabuleiro[i][j], presenca_de_pecas[i][j]))){ //CHECA SAÍDA (CAPTURA OU ROQUE)
                k++;
                atualiza_presencas(presenca_de_pecas);
                if(k >= NUMERO_DE_CHECAGENS){
                    int linha = i, coluna = j;
                    empilhar(&pecas_fora, atualiza_tabuleiro_saida(tabuleiro, linha, coluna));
                    state_pointer = STATE_3;
                    return;
                }
            }
            k = 0;
            while((checa_entrada(tabuleiro[i][j], presenca_de_pecas[i][j]))){ //CHECA ENTRADA(MOVIMENTO PADRÃO)
                k++;
                atualiza_presencas(presenca_de_pecas);
                if(k >= NUMERO_DE_CHECAGENS){
                    int linha = i, coluna = j;
                    atualiza_tabuleiro_entrada(tabuleiro, linha, coluna, desempilhar(&pecas_fora));
                    state_pointer = STATE_1; //TÉRMINO DE MOVIMENTO
                    return;
                }
            }
            k = 0;
        }
    }
}

void STATE_3(){ //ESTADO QUE DECIDE SE É ROQUE OU CAPTURA, ALÉM DE DETECTAR UMA ENTRADA
    printf("Estou no ESTADO 3!\n");
    int k = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            while((checa_entrada(tabuleiro[i][j], presenca_de_pecas[i][j]))){ //CHECA A ENTRADA DE UMA PEÇA
                k++;
                atualiza_presencas(presenca_de_pecas);
                if(k >= NUMERO_DE_CHECAGENS){
                    int linha = i, coluna = j;
                    char primeira_empilhada = pecas_fora.conteiner[pecas_fora.tam-2];
                    char ultima_empilhada = pecas_fora.conteiner[pecas_fora.tam-1];
                    if(checa_mesma_cor(primeira_empilhada, ultima_empilhada)){ //VERIFICA SE AS PEÇAS QUE SAÍRAM SÃO DE MESMA COR
                        state_pointer = STATE_4; //CASO SIM, É ROQUE
                    }
                    else{
                        state_pointer = STATE_1; //SE NÃO, É CAPTURA E TERMINA O MOVIMENTO
                    }
                    atualiza_tabuleiro_entrada(tabuleiro, linha, coluna, desempilhar(&pecas_fora));
                    return;
                }
            }
            k = 0;
        }
    }
}

void STATE_4(){ //ESTADO DE ROQUE
    printf("Estou no ESTADO 4!\n");
    int k = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            while((checa_entrada(tabuleiro[i][j], presenca_de_pecas[i][j]))){ //DETECTA UMA ENTRADA
                k++;
                atualiza_presencas(presenca_de_pecas);
                if(k >= NUMERO_DE_CHECAGENS){
                    int linha = i, coluna = j;
                    atualiza_tabuleiro_entrada(tabuleiro, linha, coluna, desempilhar(&pecas_fora));
                    state_pointer = STATE_1; //TÉRMINO DO MOVIMENTO
                    return;
                }
            }
            k = 0;
        }
    }
}

