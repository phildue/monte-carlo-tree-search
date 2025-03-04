#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <string>  // Include the string header
#include <vector>

#include "TreeNode.h"
#include "concepts.h"

template <IsGame Game>
class MonteCarloTreeSearch {
 public:
  typedef std::shared_ptr<MonteCarloTreeSearch> ShPtr;
  typedef std::shared_ptr<const MonteCarloTreeSearch> ShConstPtr;

  struct Meta {
    Game::Action action;
    Game game;
    int nVisits = 0;
    double totalReward = 0;
    double score = 0;
  };
  typedef TreeNode<Meta> Node;

  MonteCarloTreeSearch(const std::string& player, const std::string& opponent,
                       int maxIterations, float ucbConstant = std::sqrt(2))
      : _player{player},
        _opponent{opponent},
        _maxIterations{maxIterations},
        _ucbConstant{ucbConstant} {};
  ~MonteCarloTreeSearch() = default;

  Game::Action findNextMove(const Game& game) const;
  Node::ShPtr buildTree(const Game& game) const;
  Game::Action selectBestAction(Node::ShConstPtr node) const;
  Node::ShPtr select(Node::ShPtr node) const;
  Node::ShPtr expand(Node::ShPtr node) const;
  float simulate(Node::ShConstPtr node) const;
  void backpropagate(Node::ShPtr node, float result) const;

 private:
  std::string _player, _opponent;
  int _maxIterations;
  double _ucbConstant;
};

#include "MonteCarloTreeSearch.hpp"
