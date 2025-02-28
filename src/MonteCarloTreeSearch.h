#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <string>  // Include the string header
#include <vector>

#include "Game.h"
#include "TreeNode.h"

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
    float ucb1 = std::numeric_limits<float>::max();
  };
  typedef TreeNode<Meta> Node;

  MonteCarloTreeSearch(std::string player, int maxIterations,
                       float ucbConstant = std::sqrt(2))
      : _player{player},
        _maxIterations{maxIterations},
        _ucbConstant{ucbConstant} {};
  ~MonteCarloTreeSearch() = default;

  Game::Action findNextMove(const Game& game) const;
  Node::ShPtr buildTree(const Game& game) const;
  Game::Action selectBestAction(Node::ShConstPtr node) const;
  Node::ShPtr select(Node::ShPtr node) const;
  Node::ShPtr expand(Node::ShPtr node) const;
  float simulate(Node::ShConstPtr node) const;
  void backpropagate(Node::ShPtr node, int result) const;
  float ucb1(Node::ShConstPtr node) const;

  std::string nodeToStr(Node::ShConstPtr node) const;

 private:
  std::string _player;
  int _maxIterations;
  float _ucbConstant;
};

#include "MonteCarloTreeSearch.hpp"
