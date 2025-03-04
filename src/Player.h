#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "MonteCarloTreeSearch.h"
#include "TicTacToe.h"
#include "concepts.h"
template <IsGame Game>
class Player {
 public:
  typedef std::shared_ptr<Player> ShPtr;
  typedef std::shared_ptr<const Player> ShConstPtr;
  virtual ~Player() = default;
  virtual Game::Action getAction(const Game& game) = 0;
  virtual std::string player() const = 0;
};

template <IsGame Game>
class HumanPlayer : public Player<Game> {
 public:
  HumanPlayer(const std::string& player) : _player(player) {}
  Game::Action getAction(const Game& game) override {
    typename Game::Action index;
    std::cout << "[" << _player << "] Enter index: ";
    std::cin >> index;
    return index;
  }
  std::string player() const override { return _player; }

 private:
  std::string _player;
};

template <IsGame Game, IsPlayerAlgorithm<Game> Algorithm>
class AIPlayer : public Player<Game> {
 public:
  AIPlayer(const std::string& player, const Algorithm& mcts)
      : _player(player), _algo(mcts) {}
  Game::Action getAction(const Game& game) override {
    auto move = _algo.findNextMove(game);
    std::cout << "[" << _player << "] AI move: " << move << std::endl;
    return move;
  }
  std::string player() const override { return _player; }

 private:
  std::string _player;
  Algorithm _algo;
};

template <IsGame Game>
class RandomPlayer : public Player<Game> {
 public:
  RandomPlayer(const std::string& player) : _player(player) {}
  Game::Action getAction(const Game& game) override {
    auto actions = game.possibleActions();
    return actions[rand() % actions.size()];
  }
  std::string player() const override { return _player; }

 private:
  std::string _player;
};
