#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <string>  // Include the string header
#include <vector>

#include "Game.h"
#include "TreeNode.h"

template <typename G, typename Action>
  requires Game<G, Action>
class MonteCarloTreeSearch {
 public:
  typedef std::shared_ptr<MonteCarloTreeSearch> ShPtr;
  typedef std::shared_ptr<const MonteCarloTreeSearch> ShConstPtr;

  struct Meta {
    Action action;
    G game;
    int nVisits = 0;
    double totalReward = 0;
    float ucb1 = std::numeric_limits<float>::max();
  };
  typedef TreeNode<Meta> Node;

  MonteCarloTreeSearch(std::string player, int maxIterations,
                       float ucbConstant = std::sqrt(2))
      : _player{std::move(player)},
        _maxIterations{maxIterations},
        _ucbConstant{ucbConstant} {};
  ~MonteCarloTreeSearch() = default;

  Action findNextMove(const G& game) const;
  typename Node::ShPtr select(typename Node::ShPtr node) const;
  typename Node::ShPtr expand(typename Node::ShPtr node) const;
  float simulate(typename Node::ShConstPtr node) const;
  void backpropagate(typename Node::ShPtr node, int result) const;
  float ucb1(typename Node::ShConstPtr node) const;

 private:
  std::string _player;  // Change the type of _player to std::string
  int _maxIterations;
  float _ucbConstant;
};

#include "MonteCarloTreeSearch.hpp"
