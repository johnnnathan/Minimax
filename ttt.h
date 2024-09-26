#ifndef TTT_H
#define TTT_H

const char aiSymbol = 'O';
const char playerSymbol = 'X';

struct tttBoard{
  char board[3][3];
};

void printBoard(struct tttBoard* board);
void initBoard(struct tttBoard* board);

#endif // !TTT_H
