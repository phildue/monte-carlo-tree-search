#pragma once
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "Game.h"
#include "MonteCarloTreeSearch.h"

template <IsGame Game>
Game::Action MonteCarloTreeSearch<Game>::findNextMove(const Game& game) const {
  auto tree = buildTree(game);
  return selectBestAction(tree);
}

template <IsGame Game>
MonteCarloTreeSearch<Game>::Node::ShPtr MonteCarloTreeSearch<Game>::buildTree(
    const Game& game) const {
  auto tree = std::make_shared<Node>(Meta{typename Game::Action{}, game, 0, 0});

  /*
  MCTS selects the best strategy under budget constraints (maxIterations).
  Actions (nodes) are selected based one exploration and exploitation and the
  game outcome is simulated. The results are backpropagated to the root node and
  help us find the most promising move.
  */
  for (int i = 0; i < _maxIterations; ++i) {
    auto node = select(tree);

    node = expand(node);
    auto reward = simulate(node);
    backpropagate(node, reward);
  }
  return tree;
}

template <IsGame Game>
Game::Action MonteCarloTreeSearch<Game>::selectBestAction(
    MonteCarloTreeSearch<Game>::Node::ShConstPtr node) const {
  auto children = node->children();
  return (*std::max_element(
              children.begin(), children.end(),
              [](auto a, auto b) { return a->data().score < b->data().score; }))
      ->data()
      .action;
}

template <IsGame Game>
MonteCarloTreeSearch<Game>::Node::ShPtr MonteCarloTreeSearch<Game>::select(
    MonteCarloTreeSearch<Game>::Node::ShPtr tree) const {
  auto node = tree;
  while (!node->isLeaf()) {
    auto game = node->data().game;
    const auto children = node->children();
    /*We assume the opposing player selects the move that hurts us most so we
     * count the score negative.*/
    const double scoreF = game.turn() == _player ? 1.0 : -1.0;
    std::vector<double> ucbs(children.size());
    std::transform(children.begin(), children.end(), ucbs.begin(),
                   [this, scoreF, node](auto n) {
                     /*upper confidence bound formulates a trade-off between
                      * exploring new nodes and selecting the most promising
                      * ones*/
                     if (n->data().nVisits == 0) {
                       return std::numeric_limits<double>::max();
                     }
                     const double exploitation = scoreF * n->data().score;
                     const double exploration = std::sqrt(
                         std::log(node->data().nVisits) / n->data().nVisits);
                     return exploitation + _ucbConstant * exploration;
                   });
    const size_t argMax =
        std::max_element(ucbs.begin(), ucbs.end()) - ucbs.begin();
    node = children[argMax];
  }
  return node;
}

template <IsGame Game>
MonteCarloTreeSearch<Game>::Node::ShPtr MonteCarloTreeSearch<Game>::expand(
    MonteCarloTreeSearch<Game>::Node::ShPtr tree) const {
  /*For expansion we take a random action, the simulation in the next step will
   * tell us if this can lead to good outcomes.*/
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

template <IsGame Game>
float MonteCarloTreeSearch<Game>::simulate(
    MonteCarloTreeSearch<Game>::Node::ShConstPtr node) const {
  /*Simulate game outcome based on random moves, over repeated iterations we
   * will see the most promising strategy*/
  auto game = node->data().game;
  while (!game.isOver()) {
    auto actions = game.possibleActions();
    game.act(actions[rand() % actions.size()]);
  }
  if (game.isWin(_player)) {
    return 1.f;
  } else if (game.isWin(_opponent)) {
    return -1.f;
  }
  return 0;
}

template <IsGame Game>
void MonteCarloTreeSearch<Game>::backpropagate(
    MonteCarloTreeSearch<Game>::Node::ShPtr node, float result) const {
  auto n = node;
  do {
    n->data().nVisits++;
    n->data().totalReward += result;
    n->data().score = n->data().totalReward / n->data().nVisits;
    n = n->parent();
  } while (n);
}

template <IsGame Game>
std::string MonteCarloTreeSearch<Game>::nodeToStr(
    typename MonteCarloTreeSearch<Game>::Node::ShConstPtr node) const {
  std::stringstream ss;
  for (int i = 0; i < 9; ++i) {
    const auto& children = node->children();
    auto action = std::find_if(children.begin(), children.end(),
                               [i](auto n) { return n->data().action == i; });
    if (action == children.end()) {
      ss << "...... ";
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
template <IsGame Game>
void MonteCarloTreeSearch<Game>::drawTree(
    const std::string& filename, typename Node::ShConstPtr root) const {
  std::ofstream file(filename);
  file << "digraph G {\n";
  std::function<void(typename Node::ShConstPtr, int)> drawNode =
      [&](typename Node::ShConstPtr node, int thickness) {
        std::string color;
        auto otherPlayer = _player == "X" ? "O" : "X";
        if (node->data().game.isWin(_player)) {
          color = "green";
        } else if (node->data().game.isWin(otherPlayer)) {
          color = "red";
        } else if (node->data().game.isDraw()) {
          color = "yellow";
        } else {
          color = "white";
        }
        file << "  \"" << node.get() << "\" [label=\""
             << node->data().game.str() << "Visits: " << node->data().nVisits
             << "\\nReward: " << node->data().score
             << "\", style=filled, fillcolor=" << color
             << ", penwidth=" << thickness << "];\n";

        if (node->children().empty()) {
          return;
        }
        auto children = node->children();
        auto maxChild = std::max_element(
            children.begin(), children.end(),
            [](auto a, auto b) { return a->data().score < b->data().score; });

        for (const auto& child : children) {
          file << "  \"" << node.get() << "\" -> \"" << child.get() << "\";\n";
          drawNode(child, child == *maxChild ? 3 : 1);
        }
      };
  drawNode(root, 1);
  file << "}\n";
  file.close();
}
