#pragma once
#include <iostream>
#include <memory>
#include "TicTacToe.h"
#include "MonteCarloTreeSearch.h"

class Player {
    public:
        using ShPtr = std::shared_ptr<Player>;
        using UnPtr = std::unique_ptr<Player>;
        using ShConstPtr = std::shared_ptr<const Player>;
        Player(char player) : _player{player} {}
        virtual ~Player() = default;
        virtual int getMove(TicTacToe::ShConstPtr game) = 0;
        char player() const { return _player;}
    private:
        char _player;
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(char player) : Player(player) {}
        int getMove(TicTacToe::ShConstPtr game) override {
            int index;
            std::cout << "[" << player() << "] Enter index: ";
            std::cin >> index;
            return index;
        }
};

class RandomPlayer : public Player {
    public:
        RandomPlayer(char player) : Player(player) {}
        int getMove(TicTacToe::ShConstPtr game) override {
            auto actions = game->possibleActions();
            return actions[rand() % actions.size()];
        }
};

class AIPlayer : public Player {
    public:
    AIPlayer(char player, MonteCarloTreeSearch::ShConstPtr mcts) : Player(player),_mcts{mcts} {}
    int getMove(TicTacToe::ShConstPtr game) override{
        auto move = _mcts->findNextMove(game);
        std::cout << "[" << player() << "] AI move: " << move << std::endl;
        return move;
    }
    private:
    MonteCarloTreeSearch::ShConstPtr _mcts;
    
};
