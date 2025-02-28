#include "TicTacToe.h"

#include <algorithm>
#include <sstream>
#include <vector>

TicTacToe::TicTacToe() : _board(9, " "), _turn{"X"} {}

std::string TicTacToe::str() const {
  std::stringstream ss;
  for (int i = 0; i < 9; ++i) {
    ss << (_board[i] == " " ? "." : _board[i]) << " ";
    if (i % 3 == 2) {
      ss << "\n";
    }
  }
  return ss.str();
}

void TicTacToe::act(const TicTacToe::Action& index) {
  if (_board[index] != " ") {
    throw std::runtime_error("Invalid move.");
  }
  _board[index] = turn();
  switchTurn();
}

bool TicTacToe::isWin(const std::string& player) const {
  for (int i = 0; i < 3; ++i) {
    if (checkRow(i, player) || checkCol(i, player)) {
      return true;
    }
  }
  return checkDiagonals(player);
}

bool TicTacToe::isDraw() const {
  return std::none_of(_board.begin(), _board.end(),
                      [](const std::string& c) { return c == " "; });
}

bool TicTacToe::checkRow(int row, const std::string& player) const {
  int index = row * 3;
  return _board[index] == player && _board[index + 1] == player &&
         _board[index + 2] == player;
}

bool TicTacToe::checkCol(int col, const std::string& player) const {
  return _board[col] == player && _board[col + 3] == player &&
         _board[col + 6] == player;
}

bool TicTacToe::checkDiagonals(const std::string& player) const {
  return (_board[0] == player && _board[4] == player && _board[8] == player) ||
         (_board[2] == player && _board[4] == player && _board[6] == player);
}

std::vector<int> TicTacToe::possibleActions() const {
  std::vector<int> result;
  result.reserve(9);
  for (int i = 0; i < 9; ++i) {
    if (_board[i] == " ") {
      result.push_back(i);
    }
  }
  return result;
}
