#ifndef TTT_H
#define TTT_H

const char ai_symbol = 'O';
const char player_symbol = 'X';

struct tttBoard{
  char board[3][3];
};

void printBoard(struct tttBoard* board);
void initBoard(struct tttBoard* board);

#endif // !TTT_H
