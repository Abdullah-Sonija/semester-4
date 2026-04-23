import math
import copy

PLAYER_X = "X"   # AI
PLAYER_O = "O"   # Human
EMPTY = "-"

def create_board():
    return [[[EMPTY for _ in range(3)] for _ in range(3)] for _ in range(9)]

def print_board(boards):
    print("\n--- SUPER TIC-TAC-TOE ---")
    for row_block in range(3):
        for row in range(3):
            line = ""
            for col_block in range(3):
                b = row_block * 3 + col_block
                line += " ".join(boards[b][row]) + " | "
            print(line[:-3])
        if row_block < 2:
            print("-" * 21)
    print()

def check_winner(board):
    lines = []
    lines.extend(board) # rows
    lines.extend([[board[i][j] for i in range(3)] for j in range(3)]) # columns
    lines.append([board[i][i] for i in range(3)]) # main diagonal
    lines.append([board[i][2-i] for i in range(3)]) # anti diagonal

    for line in lines:
        if line[0] != EMPTY and all(cell == line[0] for cell in line):
            return line[0]
    return None

def check_global_winner(boards):
    meta = [check_winner(b) for b in boards]
    meta_grid = [meta[i*3:(i+1)*3] for i in range(3)]
    return check_winner(meta_grid)

def is_board_full(board):
    return all(cell != EMPTY for row in board for cell in row)

def get_moves(boards, forced_board):
    moves = []
    
    if forced_board is not None and check_winner(boards[forced_board]) is None and not is_board_full(boards[forced_board]):
        b = forced_board
        for i in range(3):
            for j in range(3):
                if boards[b][i][j] == EMPTY:
                    moves.append((b, i, j))
        return moves
        
    for b in range(9):
        if check_winner(boards[b]) is None and not is_board_full(boards[b]):
            for i in range(3):
                for j in range(3):
                    if boards[b][i][j] == EMPTY:
                        moves.append((b, i, j))
    return moves

def evaluate(boards):
    winner = check_global_winner(boards)
    if winner == PLAYER_X:
        return 1000
    elif winner == PLAYER_O:
        return -1000
    
    score = 0
    for b in range(9):
        w = check_winner(boards[b])
        if w == PLAYER_X:
            score += 10
        elif w == PLAYER_O:
            score -= 10
    return score

def minimax(boards, depth, alpha, beta, maximizing, forced_board):
    score = evaluate(boards)

    if abs(score) >= 1000 or depth == 0:
        return score

    moves = get_moves(boards, forced_board)
    if not moves: 
        return 0

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
    moves = get_moves(boards, forced_board)

    for b, i, j in moves:
        new_boards = copy.deepcopy(boards)
        new_boards[b][i][j] = PLAYER_X

        val = minimax(new_boards, 3, -math.inf, math.inf, False, i*3+j)
        if val > best_val:
            best_val = val
            move_choice = (b, i, j)
    return move_choice if move_choice else (moves[0] if moves else None)

def play():
    boards = create_board()
    forced_board = None

    while True:
        print_board(boards)
        valid_moves = get_moves(boards, forced_board)
        
        if not valid_moves:
            print("Game Over! It's a tie!")
            break

        # HUMAN MOVE
        print("Your turn (O).", end=" ")
        if forced_board is not None and check_winner(boards[forced_board]) is None and not is_board_full(boards[forced_board]):
            print(f"You MUST play in Board {forced_board}.")
        else:
            print("You can play in ANY available board.")
            
        try:
            b = int(input("Board (0-8): "))
            i = int(input("Row (0-2): "))
            j = int(input("Col (0-2): "))
        except ValueError:
            print("\n>> Invalid input! Please enter numbers only. <<\n")
            continue

        if (b, i, j) not in valid_moves:
            print("\n>> Invalid move! Either the cell is taken, or you didn't play in the forced board. <<\n")
            continue

        boards[b][i][j] = PLAYER_O
        forced_board = i * 3 + j

        if check_global_winner(boards):
            print_board(boards)
            print("You win! Congratulations!")
            break

        # AI MOVE
        move = best_move(boards, forced_board)

        if move:
            b, i, j = move
            print(f"AI played at -> Board {b}, Row {i}, Col {j}")
            boards[b][i][j] = PLAYER_X
            forced_board = i * 3 + j

        if check_global_winner(boards):
            print_board(boards)
            print("AI wins! Better luck next time.")
            break

if __name__ == '__main__':
    play()
