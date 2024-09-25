player_symbol = "X"
ai_symbol = "O"

main_board = [[0,1,2],
              [3,4,5],
              [6,7,8]] 




def print_board():
    print("\nCurrent Board:")
    for row in main_board:
        row_display = [" " if isinstance(cell, int) else cell for cell in row]
        print(" | ".join(row_display))
        print("-" * 13)  
    print()  

def finished_party(board, is_ai):
    symbol = ai_symbol if is_ai else player_symbol

    # Check rows
    for row in board:
        if all(cell == symbol for cell in row):
            return True

    # Check columns
    for col in range(3):
        if all(board[row][col] == symbol for row in range(3)):
            return True

    # Check diagonals
    if (board[0][0] == symbol and board[1][1] == symbol and board[2][2] == symbol) or \
       (board[0][2] == symbol and board[1][1] == symbol and board[2][0] == symbol):
        return True
    return False

def finished(board):
    if finished_party(board, False):
        print("Player wins!")
        return True
    elif finished_party(board, True):
        print("AI wins!")
        return True
    elif board_filled(board):
        print("It's a draw!")
        return True
    return False

def board_filled(board):
    for row in range(3):
        for col in range(3):
            if board[row][col] != "X" and board[row][col] != "O":
                return False
    return True

def get_input():
    while True:
        move = input("What is your next move?")
        try:
            result = int(move)
            if result < 9 and result > -1:
                row = int(result / 3)
                col = result % 3 
                if main_board[row][col] != "X" and main_board[row][col] != "O":
                    return result, row, col
                else:
                    print("Position already occupied")
            else:
                print("Value out of range")
        except ValueError:
            print("Invalid value, please try again")

def act_player():
    move , row, col = get_input()
    main_board[row][col] = player_symbol

def minimax(board, depth, is_maximizing):
    # Check for terminal states
    if finished_party(board, True):  # AI win
        return 1  # AI wins
    elif finished_party(board, False):  # Player win
        return -1  # Player wins
    elif all(isinstance(cell, str) for row in board for cell in row):  # Draw
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
    player1, player2 = "ERROR", "ERROR"
    if starter == player_symbol:
        player1 = player_symbol
        player2 = ai_symbol
    else:
        player1 = ai_symbol
        player2 = player_symbol

    while not finished(main_board):
        print_board()
        act(player1)
        act(player2)
        

play(player_symbol)

