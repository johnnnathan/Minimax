#include "ttt.h"
#include <stdio.h>

void initBoard(struct tttBoard* board){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++){
      board->board[i][j] = '-';
    }
  }
}

void printBoard(struct tttBoard* board) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board->board[i][j]);
        }
        printf("\n");
    }
}

int finishedParty(struct tttBoard* board, int is_ai){
  char symbol;
  if (is_ai == 1){
    symbol = ai_symbol;
  }else{
    symbol = player_symbol;
  }

  for (int i = 0; i < 3; i++){
    int flag = 1;
    for (int j = 0; j < 3; j++){
      if (board->board[i][j] != symbol){flag = 0;}
      if (flag == 0){break;}
    }
    if (flag == 1){return 1;}
  }

  // Is this needed?
  for (int i = 0; i < 3; i++){
    int flag = 1;
    for (int j = 0; j < 3; j++){
      if (board->board[j][i] != symbol){flag = 0;}
      if (flag == 0){break;}
    }
    if (flag == 1){return 1;}
  }

  if ((board->board[2][0] == symbol && board->board[1][1] == symbol && board->board[0][2] == symbol) || (board->board[0][0] == 1 && board->board[1][1] == 1 && board->board[2][2] == 1)){
    return 1;
  }
  return 0;
}


int finished(struct tttBoard* board){
  int flagUser = finishedParty(board, 0);
  int flagAI = finishedParty(board,1);
  if (flagUser == 1 || flagAI == 1){
    return 1;
  }
  return 0;
}

int main(){
  struct tttBoard ttt;

  initBoard(&ttt);

  printBoard(&ttt);
  
  return 0;
}

