import random
import copy
import math

class Player:
    def __init__(self, symbol):
        self.symbol = symbol

    def get_move(self, board):
        move = input(f"Player {self.symbol}, enter your move (row and column) as 'row,col': ")
        return map(int, move.split(','))


class TicTacToe:
    def __init__(self):
        self.board = [[' ' for _ in range(3)] for _ in range(3)]
        self.players = [Player('X'), Player('O')]
        self.current_player_index = 0

    def print_board(self):
        for row in self.board:
            print(" | ".join(row))
            print("-" * 5)

    def check_winner(self, player):
        # Check rows, columns and diagonals
        for i in range(3):
            if all([cell == player.symbol for cell in self.board[i]]):
                return True
            if all([self.board[j][i] == player.symbol for j in range(3)]):
                return True
        if all([self.board[i][i] == player.symbol for i in range(3)]) or all([self.board[i][2 - i] == player.symbol for i in range(3)]):
            return True
        return False

    def is_full(self):
        return all([cell != ' ' for row in self.board for cell in row])

    def play(self):
        while True:
            self.print_board()
            current_player = self.players[self.current_player_index]
            row, col = current_player.get_move(self.board)

            if self.board[row][col] != ' ':
                print("Cell already taken, try again.")
                continue

            self.board[row][col] = current_player.symbol

            if self.check_winner(current_player):
                self.print_board()
                print(f"Player {current_player.symbol} wins!")
                break

            if self.is_full():
                self.print_board()
                print("It's a tie!")
                break

            self.current_player_index = 1 - self.current_player_index


class AIPlayer(Player):
    def __init__(self, symbol, simulations=1000):
        super().__init__(symbol)
        self.simulations = simulations

    def get_move(self, board):
        best_move = None
        best_win_ratio = -1

        for move in self.get_possible_moves(board):
            wins = 0
            for _ in range(self.simulations):
                if self.simulate_game(board, move):
                    wins += 1
            win_ratio = wins / self.simulations
            if win_ratio > best_win_ratio:
                best_win_ratio = win_ratio
                best_move = move

        return best_move

    def get_possible_moves(self, board):
        moves = []
        for i in range(3):
            for j in range(3):
                if board[i][j] == ' ':
                    moves.append((i, j))
        return moves

    def simulate_game(self, board, move):
        simulation_board = copy.deepcopy(board)
        simulation_board[move[0]][move[1]] = self.symbol
        current_symbol = 'O' if self.symbol == 'X' else 'X'

        while True:
            if self.check_winner(simulation_board, self.symbol):
                return True
            if self.check_winner(simulation_board, current_symbol):
                return False
            if self.is_full(simulation_board):
                return False

            possible_moves = self.get_possible_moves(simulation_board)
            random_move = random.choice(possible_moves)
            simulation_board[random_move[0]][random_move[1]] = current_symbol
            current_symbol = 'O' if current_symbol == 'X' else 'X'

    def check_winner(self, board, symbol):
        for i in range(3):
            if all([cell == symbol for cell in board[i]]):
                return True
            if all([board[j][i] == symbol for j in range(3)]):
                return True
        if all([board[i][i] == symbol for i in range(3)]) or all([board[i][2 - i] == symbol for i in range(3)]):
            return True
        return False

    def is_full(self, board):
        return all([cell != ' ' for row in board for cell in row])

    game = TicTacToe()
    game.players[1] = AIPlayer('O')
    game.play()
