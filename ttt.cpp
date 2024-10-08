// Methods to add
// Print Board x
// finishedParty x
// finished x
// boardFilled x
// getInput x
// actPlayer x
// actAI
// minimax
// act 
// play



#include "ttt.h"
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <random>
#include <chrono>

#define MAX 1000
#define MIN -1000

// Function prototypes for minimax and actAI
int minimax(struct tttBoard* board, int depth, int isMax);
int bestMove(struct tttBoard* board);



int randomMove(struct tttBoard* board){
  std::random_device rd; // Seed
  std::mt19937 gen(rd()); // Mersenne Twister generator

  // Define the range
  int min = 0;
  int max = 8;

  // Create a uniform distribution
  std::uniform_int_distribution<> dis(min, max);

  // Generate a random number in the range [min, max]
  while (true){
    int randomNumber = dis(gen);
    int row = randomNumber / 3;
    int col = randomNumber % 3;
    if (board->board[row][col] == '-'){
      board->board[row][col] = playerSymbol;
      return 0;
    }
  }

  


}



int getInput(struct tttBoard* board){
  char input[1];
  while (1 == 1){
    printf("Make your move:\n");
    scanf(" %c", input);
    int cell = input[0] - '0';
    if (cell < 0 && cell > 8){
      printf("Value out of range\n");
      continue;
    }
    int row = cell / 3;
    int col = cell % 3;
    if (board->board[row][col] == playerSymbol || board->board[row][col] == aiSymbol){
      printf("Cell is occupied\n");
      continue;
    }
    board->board[row][col] = playerSymbol;
    return 0;

  }
}

int boardFilled(struct tttBoard* board){
  for (int i = 0; i < 3; i ++){
    for (int j = 0 ; j < 3; j++){
      if (board->board[i][j] == '-'){
        return 0;
      }
    }
  }
  return 1;
}

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
    symbol = aiSymbol;
  }else{
    symbol = playerSymbol;
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

  if ((board->board[2][0] == symbol && board->board[1][1] == symbol && board->board[0][2] == symbol) || (board->board[0][0] == symbol && board->board[1][1] == symbol && board->board[2][2] == symbol)){
    return 1;
  }
  return 0;
}


int finished(struct tttBoard* board){
  int flagUser = finishedParty(board, 0);
  int flagAI = finishedParty(board,1);
  int flagFull = boardFilled(board);
  if (flagUser == 1){
    printf("Player won\n");
    return 1;
  } 
  if(flagAI == 1){
    printf("Minimax won\n");
    return 2;
  } 
  if (flagFull == 1){
    printf("Draw\n");
    return 3;
  }
  return 0;
}


void actAI(struct tttBoard* board) {
    int bestMoveIndex = bestMove(board);
    int row = bestMoveIndex / 3;
    int col = bestMoveIndex % 3;
    board->board[row][col] = aiSymbol;
}

int act(struct tttBoard* board, char who){
  if (who == playerSymbol){
    randomMove(board);
    return 0;
  }
  actAI(board);
  return 0;

}

int minimax(struct tttBoard* board, int depth, int isMax) {
    if (finishedParty(board, 1)) return 10 - depth;  // AI wins
    if (finishedParty(board, 0)) return depth - 10;  // Player wins
    if (boardFilled(board)) return 0;                // Draw

    if (isMax) {
        int best = MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board->board[i][j] == '-') {
                    board->board[i][j] = aiSymbol;
                    int score = minimax(board, depth + 1, 0);
                    board->board[i][j] = '-';
                    best = (score > best) ? score : best;
                }
            }
        }
        return best;
    } else {
        int best = MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board->board[i][j] == '-') {
                    board->board[i][j] = playerSymbol;
                    int score = minimax(board, depth + 1, 1);
                    board->board[i][j] = '-';
                    best = (score < best) ? score : best;
                }
            }
        }
        return best;
    }
}

int bestMove(struct tttBoard* board) {
    int bestVal = MIN;
    int bestMoveIndex = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board->board[i][j] == '-') {
                board->board[i][j] = aiSymbol;
                int moveVal = minimax(board, 0, 0);
                board->board[i][j] = '-';
                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestMoveIndex = i * 3 + j;
                }
            }
        }
    }

    return bestMoveIndex;
}

int play(struct tttBoard* board, char starter){
  char player1;
  char player2;

  if (starter == playerSymbol){
    player1 = playerSymbol;
    player2 = aiSymbol;
  }
  else{
    player1 = aiSymbol;
    player2 = playerSymbol;
  }

  int finishedCode = 0;

  finishedCode = finished(board);



  printBoard(board);
  while (!finishedCode) {
    printf("Player 1:\n");
    act(board, player1);
    finishedCode = finished(board);
    if (finishedCode != 0){
      printBoard(board);  // Print final state before exiting
      return finishedCode;            // End the game if Player 1 (or AI in swapped role) finishes the game
    }

    printBoard(board);       // Show the board after Player 1's move

    printf("Player 2: \n");
    act(board, player2);     // AI or Player 2's turn
    finishedCode = finished(board);
    if (finishedCode != 0) {
      printBoard(board);  // Print final state before exiting
      return finishedCode;            // End the game if AI (or Player 2) finishes the game
    }

    printBoard(board);       // Show the board after AI's move
  }

  return 0;
}


int main(){
  struct tttBoard ttt;

  initBoard(&ttt);

  auto start_time = std::chrono::high_resolution_clock::now();

  int player_tally = 0;
  int ai_tally = 0;
  int draw_tally = 0;

  for (int i = 0; i < 50; i ++){
    int result = play(&ttt, aiSymbol);
    if (result == 1){
      player_tally += 1;
    }else if (result == 2) {
      ai_tally += 1;
    }
    else if (result == 3){
      draw_tally += 1;
    }
    initBoard(&ttt);
  }


    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    // Logging results
    std::cout << "Results after 50 games:\n";
    std::cout << "Player Wins: " << player_tally << "\n";
    std::cout << "AI Wins: " << ai_tally << "\n";
    std::cout << "Draws: " << draw_tally << "\n";
    std::cout << "Time taken: " << std::fixed << std::setprecision(3) << duration.count() << " seconds\n";
  return 0;
}

