#pragma once

#include <vector>
#include <string>
#include <memory>

class TicTacToe {
public:
    using ShPtr = std::shared_ptr<TicTacToe>;
    using UnPtr = std::unique_ptr<TicTacToe>;
    using ShConstPtr = std::shared_ptr<const TicTacToe>;

    TicTacToe();
    TicTacToe(const TicTacToe& other) = default;
    TicTacToe(TicTacToe&& other) = default;
    TicTacToe& operator=(const TicTacToe& other) = default;
    ~TicTacToe() = default;

    std::string str() const;
    bool isWin(char player) const;
    bool isDraw() const;
    char turn() const { return _turn;}
    std::vector<int> possibleActions() const;
    void act(int index, char player);
    void switchTurn() { _turn = (_turn == 'X' ? 'O' : 'X');}
private:
    std::vector<char> _board;
    char _turn;
    bool checkRow(int row, char player) const;
    bool checkCol(int col, char player) const;
    bool checkDiagonals(char player) const;
};