import math
import copy

PLAYER_X = "X"   # AI
PLAYER_O = "O"   # Human
EMPTY = "-"

def create_board():
    return [[[EMPTY for _ in range(3)] for _ in range(3)] for _ in range(9)]

def print_board(boards):
    for row_block in range(3):
        for row in range(3):
            line = ""
            for col_block in range(3):
                b = row_block * 3 + col_block
                line += " ".join(boards[b][row]) + "   "
            print(line)
        print()

def check_winner(board):
    lines = []
    lines.extend(board)
    lines.extend([[board[i][j] for i in range(3)] for j in range(3)])
    lines.append([board[i][i] for i in range(3)])
    lines.append([board[i][2-i] for i in range(3)])

    for line in lines:
        if line[0] != EMPTY and all(cell == line[0] for cell in line):
            return line[0]
    return None

def check_global_winner(boards):
    meta = [check_winner(b) for b in boards]
    meta_grid = [meta[i*3:(i+1)*3] for i in range(3)]
    return check_winner(meta_grid)

def get_moves(boards, forced_board):
    moves = []

    if forced_board is not None and check_winner(boards[forced_board]) is None:
        b = forced_board
        for i in range(3):
            for j in range(3):
                if boards[b][i][j] == EMPTY:
                    moves.append((b, i, j))
    else:
        for b in range(9):
            if check_winner(boards[b]) is None:
                for i in range(3):
                    for j in range(3):
                        if boards[b][i][j] == EMPTY:
                            moves.append((b, i, j))

    return moves

def evaluate(boards):
    winner = check_global_winner(boards)
    if winner == PLAYER_X:
        return 100
    elif winner == PLAYER_O:
        return -100
    return 0

def minimax(boards, depth, alpha, beta, maximizing, forced_board):
    score = evaluate(boards)

    if abs(score) == 100 or depth == 0:
        return score

    moves = get_moves(boards, forced_board)

    if maximizing:
        max_eval = -math.inf
        for b, i, j in moves:
            new_boards = copy.deepcopy(boards)
            new_boards[b][i][j] = PLAYER_X

            val = minimax(new_boards, depth-1, alpha, beta, False, i*3+j)
            max_eval = max(max_eval, val)
            alpha = max(alpha, val)

            if beta <= alpha:
                break
        return max_eval

    else:
        min_eval = math.inf
        for b, i, j in moves:
            new_boards = copy.deepcopy(boards)
            new_boards[b][i][j] = PLAYER_O

            val = minimax(new_boards, depth-1, alpha, beta, True, i*3+j)
            min_eval = min(min_eval, val)
            beta = min(beta, val)

            if beta <= alpha:
                break
        return min_eval

def best_move(boards, forced_board):
    best_val = -math.inf
    move_choice = None

    for b, i, j in get_moves(boards, forced_board):
        new_boards = copy.deepcopy(boards)
        new_boards[b][i][j] = PLAYER_X

        val = minimax(new_boards, 3, -math.inf, math.inf, False, i*3+j)

        if val > best_val:
            best_val = val
            move_choice = (b, i, j)

    return move_choice

boards = create_board()
forced_board = None

while True:
    print_board(boards)

    # HUMAN MOVE
    print("Your turn (O)")
    b = int(input("Board (0-8): "))
    i = int(input("Row (0-2): "))
    j = int(input("Col (0-2): "))

    if boards[b][i][j] != EMPTY:
        print("Invalid move!")
        continue

    boards[b][i][j] = PLAYER_O
    forced_board = i * 3 + j

    if check_global_winner(boards):
        print_board(boards)
        print("You win!")
        break

    # AI MOVE
    print("AI is thinking... 🤖")
    move = best_move(boards, forced_board)

    if move:
        b, i, j = move
        boards[b][i][j] = PLAYER_X
        forced_board = i * 3 + j

    if check_global_winner(boards):
        print_board(boards)
        print("AI wins!")
        break
