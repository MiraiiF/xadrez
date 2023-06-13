#include "Parser.h"

void parse_board(char board[8][8], char* string){
    short unsigned int counter = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            string[i*8 + j + counter] = board[i][j]; 
        }
        string[(i+1)*8 + counter] = '/';
        counter += 1;
    }
    string_fim(string);
}

void string_fim(char* string){
    string[71] = '\0';
}