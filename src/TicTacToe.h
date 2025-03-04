#pragma once

#include <memory>
#include <string>
#include <vector>

class TicTacToe {
 public:
  using ShPtr = std::shared_ptr<TicTacToe>;
  using UnPtr = std::unique_ptr<TicTacToe>;
  using ShConstPtr = std::shared_ptr<const TicTacToe>;

  typedef int Action;

  TicTacToe();
  TicTacToe(const TicTacToe& other) = default;
  TicTacToe(TicTacToe&& other) = default;
  TicTacToe& operator=(const TicTacToe& other) = default;
  ~TicTacToe() = default;

  std::string str() const;
  bool isWin(const std::string& player) const;
  bool isDraw() const;
  bool isOver() const { return isWin("X") || isWin("O") || isDraw(); }
  std::string turn() const { return _turn; }
  std::vector<int> possibleActions() const;
  void act(const Action& action);
  void switchTurn() { _turn = (_turn == "X" ? "O" : "X"); }

 private:
  std::vector<std::string> _board;
  std::string _turn;
  bool checkRow(int row, const std::string& player) const;
  bool checkCol(int col, const std::string& player) const;
  bool checkDiagonals(const std::string& player) const;
};
