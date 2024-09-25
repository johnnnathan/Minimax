player_symbol = "X"
ai_symbol = "O"

main_board = [["X","X",2],
              [3,4,5],
              [6,7,8]] 



def print_board():
    for row in main_board:
        print(row)


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
    return finished_party(board, False)  or finished_party(board, True)


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
        


