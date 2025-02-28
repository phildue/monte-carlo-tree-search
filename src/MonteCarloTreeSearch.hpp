#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "Game.h"
#include "MonteCarloTreeSearch.h"

template <typename G, typename Action>
  requires Game<G, Action>
std::string reward2str(
    typename MonteCarloTreeSearch<G, Action>::Node::ShConstPtr node) {
  std::stringstream ss;
  for (int i = 0; i < 9; ++i) {
    const auto& children = node->children();
    auto action = std::find_if(children.begin(), children.end(),
                               [i](auto n) { return n->data().action == i; });
    if (action == children.end()) {
      ss << ". ";
    } else {
      auto data = (*action)->data();
      ss << data.totalReward << "|" << data.nVisits << " ";
    }
    if (i % 3 == 2) {
      ss << "\n";
    }
  }
  return ss.str();
}

template <typename G, typename Action>
  requires Game<G, Action>
Action MonteCarloTreeSearch<G, Action>::findNextMove(const G& game) const {
  auto root = std::make_shared<Node>(Meta{-1, game, 0, 0});
  for (int i = 0; i < _maxIterations; ++i) {
    auto node = select(root);
    node = expand(node);
    auto reward = simulate(node);
    backpropagate(node, reward);
  }
  std::cout << reward2str<G, Action>(root) << std::endl;

  return (*std::max_element(root->children().begin(), root->children().end(),
                            [](auto a, auto b) {
                              return a->data().totalReward / a->data().nVisits <
                                     b->data().totalReward / b->data().nVisits;
                            }))
      ->data()
      .action;
}

template <typename G, typename Action>
  requires Game<G, Action>
typename MonteCarloTreeSearch<G, Action>::Node::ShPtr
MonteCarloTreeSearch<G, Action>::select(
    typename MonteCarloTreeSearch<G, Action>::Node::ShPtr tree) const {
  auto node = tree;
  auto game = node->data().game;
  while (!game.isWin("X") && !game.isWin("O") && !game.isDraw()) {
    if (node->isLeaf()) {
      return node;
    }
    for (const auto& n : node->children()) {
      n->data().ucb1 = ucb1(n);
    }

    node = *std::max_element(
        node->children().begin(), node->children().end(),
        [this](auto a, auto b) { return a->data().ucb1 < b->data().ucb1; });
    game = node->data().game;
  }
  return node;
}

template <typename G, typename Action>
  requires Game<G, Action>
typename MonteCarloTreeSearch<G, Action>::Node::ShPtr
MonteCarloTreeSearch<G, Action>::expand(
    typename MonteCarloTreeSearch<G, Action>::Node::ShPtr tree) const {
  const auto& actions = tree->data().game.possibleActions();
  if (actions.empty()) {
    return tree;
  }
  for (const auto& action : actions) {
    auto game = tree->data().game;
    game.act(action);
    auto child = std::make_shared<Node>(Meta{action, game}, tree);
    tree->addChild(child);
  }
  return tree->children()[rand() % actions.size()];
}

template <typename G, typename Action>
  requires Game<G, Action>
float MonteCarloTreeSearch<G, Action>::simulate(
    typename MonteCarloTreeSearch<G, Action>::Node::ShConstPtr node) const {
  auto game = node->data().game;
  while (!game.isWin("X") && !game.isWin("O") && !game.isDraw()) {
    auto actions = game.possibleActions();
    game.act(actions[rand() % actions.size()]);
  }
  auto otherPlayer = _player == "X" ? "O" : "X";
  if (game.isWin(_player)) {
    return 1;
  } else if (game.isWin(otherPlayer)) {
    return -1;
  }
  return 0;
}

template <typename G, typename Action>
  requires Game<G, Action>
void MonteCarloTreeSearch<G, Action>::backpropagate(
    typename MonteCarloTreeSearch<G, Action>::Node::ShPtr node,
    int result) const {
  auto n = node;
  do {
    n->data().nVisits++;
    n->data().totalReward += result;
    n = n->parent();
  } while (n);
}

template <typename G, typename Action>
  requires Game<G, Action>
float MonteCarloTreeSearch<G, Action>::ucb1(
    typename MonteCarloTreeSearch<G, Action>::Node::ShConstPtr node) const {
  const auto& data = node->data();
  if (data.nVisits == 0) {
    return std::numeric_limits<float>::max();
  }
  return data.totalReward / data.nVisits +
         _ucbConstant *
             std::sqrt(std::log(node->parent()->data().nVisits) / data.nVisits);
}
