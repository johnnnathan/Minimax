import random
import time

player_symbol = "X"
ai_symbol = "O"
player_tally = 0
ai_tally = 0
draw_tally = 0

random.seed(time.time())
main_board = [[0, 1, 2],
               [3, 4, 5],
               [6, 7, 8]]

def reset_board():
    global main_board 
    main_board = [[0, 1, 2],
                  [3, 4, 5],
                  [6, 7, 8]]

def print_board():
    print("\nCurrent Board:")
    for row in main_board:
        row_display = [" " if isinstance(cell, int) else cell for cell in row]
        print(" | ".join(row_display))
        print("-" * 13)
    print()

def check_win(board, symbol):
    # Check rows, columns, and diagonals
    for i in range(3):
        if all(board[i][j] == symbol for j in range(3)) or \
           all(board[j][i] == symbol for j in range(3)):
            return True
    if all(board[i][i] == symbol for i in range(3)) or \
       all(board[i][2-i] == symbol for i in range(3)):
        return True
    return False

def finished(board):
    global player_tally, ai_tally, draw_tally
    if check_win(board, player_symbol):
        print("Player wins!")
        player_tally += 1
        return True
    elif check_win(board, ai_symbol):
        print("AI wins!")
        ai_tally += 1
        return True
    elif board_filled(board):
        print("It's a draw!")
        draw_tally += 1
        return True
    return False

def board_filled(board):
    return all(not isinstance(cell, int) for row in board for cell in row)

def make_move_random(board):
    empty_cells = [(r, c) for r in range(3) for c in range(3) if isinstance(board[r][c], int)]
    if empty_cells:
        row, col = random.choice(empty_cells)
        board[row][col] = player_symbol

def act_player():
    make_move_random(main_board)

def minimax(board, depth, is_maximizing):
    if check_win(board, ai_symbol):
        return 10 - depth
    elif check_win(board, player_symbol):
        return depth - 10
    elif board_filled(board):
        return 0

    if is_maximizing:
        best_score = float('-inf')
        for row in range(3):
            for col in range(3):
                if isinstance(board[row][col], int):
                    board[row][col] = ai_symbol
                    score = minimax(board, depth + 1, False)
                    board[row][col] = row * 3 + col
                    best_score = max(score, best_score)
        return best_score
    else:
        best_score = float('inf')
        for row in range(3):
            for col in range(3):
                if isinstance(board[row][col], int):
                    board[row][col] = player_symbol
                    score = minimax(board, depth + 1, True)
                    board[row][col] = row * 3 + col
                    best_score = min(score, best_score)
        return best_score

def act_ai():
    best_score = float('-inf')
    best_move = None

    for row in range(3):
        for col in range(3):
            if isinstance(main_board[row][col], int):
                main_board[row][col] = ai_symbol
                score = minimax(main_board, 0, False)
                main_board[row][col] = row * 3 + col

                if score > best_score:
                    best_score = score
                    best_move = (row, col)

    if best_move:
        main_board[best_move[0]][best_move[1]] = ai_symbol

def act(who):
    if who == player_symbol:
        act_player()
    else:
        act_ai()

def play(starter):
    reset_board()
    players = [starter, ai_symbol if starter == player_symbol else player_symbol]
    current_player = 0

    while not finished(main_board):
        act(players[current_player])
        current_player = 1 - current_player

start_time = time.time()    

for i in range(25):
    play(ai_symbol)  # AI starts first
    play(player_symbol)  # Player starts first
    print(f"Game set {i+1} completed")

end_time = time.time()

execution_time = end_time - start_time

print(f"Time: {execution_time:.2f} seconds")
print(f"Random: {player_tally}")
print(f"Minimax: {ai_tally}")
print(f"Draw: {draw_tally}")
