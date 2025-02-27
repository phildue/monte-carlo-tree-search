#pragma once

#include <math.h>

#include <memory>
#include <vector>

#include "TicTacToe.h"
#include "TreeNode.h"
class MonteCarloTreeSearch {
 public:
  typedef std::shared_ptr<MonteCarloTreeSearch> ShPtr;
  typedef std::shared_ptr<const MonteCarloTreeSearch> ShConstPtr;

  struct Meta {
    int action;
    TicTacToe::ShPtr game;
    int nVisits = 0;
    double totalReward = 0;
    float ucb1 = std::numeric_limits<float>::max();
  };
  typedef TreeNode<Meta> Node;

  MonteCarloTreeSearch(char player, int maxIterations,
                       float ucbConstant = std::sqrt(2))
      : _player{player},
        _maxIterations{maxIterations},
        _ucbConstant{ucbConstant} {};
  ~MonteCarloTreeSearch() = default;

  int findNextMove(TicTacToe::ShConstPtr game) const;
  Node::ShPtr select(Node::ShPtr node) const;
  Node::ShPtr expand(Node::ShPtr node) const;
  float simulate(Node::ShConstPtr node) const;
  void backpropagate(Node::ShPtr node, int result) const;
  float ucb1(Node::ShConstPtr node) const;

 private:
  char _player;
  int _maxIterations;
  float _ucbConstant;
};
