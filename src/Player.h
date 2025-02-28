#pragma once
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "MonteCarloTreeSearch.h"
#include "TicTacToe.h"

template <typename G, typename Action>
  requires Game<G, Action>
class Player {
 public:
  typedef std::shared_ptr<Player> ShPtr;
  typedef std::shared_ptr<const Player> ShConstPtr;
  virtual ~Player() = default;
  virtual Action getMove(const G& game) const = 0;
  virtual std::string player() const = 0;
};

template <typename G, typename Action>
  requires Game<G, Action>
class HumanPlayer : public Player<G, Action> {
 public:
  HumanPlayer(const std::string& player) : _player(player) {}
  Action getMove(const G& game) const override {
    Action index;
    std::cout << "[" << _player << "] Enter index: ";
    std::cin >> index;
    return index;
  }
  std::string player() const override { return _player; }

 private:
  std::string _player;
};

template <typename G, typename Action>
  requires Game<G, Action>
class AIPlayer : public Player<G, Action> {
 public:
  AIPlayer(const std::string& player,
           std::shared_ptr<const MonteCarloTreeSearch<G, Action>> mcts)
      : _player(player), _mcts(mcts) {}
  Action getMove(const G& game) const override {
    auto move = _mcts->findNextMove(game);
    std::cout << "[" << _player << "] AI move: " << move << std::endl;
    return move;
  }
  std::string player() const override { return _player; }

 private:
  std::string _player;
  std::shared_ptr<const MonteCarloTreeSearch<G, Action>> _mcts;
};

template <typename G, typename Action>
  requires Game<G, Action>
class RandomPlayer : public Player<G, Action> {
 public:
  RandomPlayer(const std::string& player) : _player(player) {}
  Action getMove(const G& game) const override {
    auto actions = game.possibleActions();
    return actions[rand() % actions.size()];
  }
  std::string player() const override { return _player; }

 private:
  std::string _player;
};
