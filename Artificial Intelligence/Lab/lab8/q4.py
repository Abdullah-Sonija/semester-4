import math

class TicTacToe:
    def __init__(self):
        # Initialize an empty board with 9 spaces
        self.board = [' '] * 9

    def print_board(self):
        # Print the board matching the requested lowercase 'x' and 'o' format
        for i in range(0, 9, 3):
            row = []
            for j in range(3):
                cell = self.board[i+j]
                if cell == 'X':
                    row.append('x')
                elif cell == 'O':
                    row.append('o')
                else:
                    row.append(' ')
            print(f"| {row[0]} | {row[1]} | {row[2]} |")
        print()

    def available_moves(self):
        return [i for i, spot in enumerate(self.board) if spot == ' ']

    def empty_squares(self):
        return ' ' in self.board

    def num_empty_squares(self):
        return self.board.count(' ')

    def make_move(self