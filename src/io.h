
#pragma once
#include <iomanip>
#include <sstream>

#include "MonteCarloTreeSearch.h"
template <IsGame Game>
void toDotFile(const std::string& filename,
               typename MonteCarloTreeSearch<Game>::Node::ShConstPtr root,
               const std::string& player);

template <IsGame Game>
class DrawingMonteCarloTreeSearch {
 public:
  DrawingMonteCarloTreeSearch(const std::string& player,
                              const std::string& opponent, int maxIterations,
                              float ucbConstant = std::sqrt(2))
      : _mcts{player, opponent, maxIterations, ucbConstant},
        _player{player},
        _iteration{0} {};

  Game::Action findNextMove(const Game& game) {
    auto tree = _mcts.buildTree(game);
    std::ostringstream oss;
    oss << "tree_" << _player << "_" << std::setw(3) << std::setfill('0')
        << _iteration << ".dot";
    toDotFile<Game>(oss.str(), tree, _player);
    _iteration++;
    return _mcts.selectBestAction(tree);
  }

 private:
  MonteCarloTreeSearch<Game> _mcts;
  const std::string _player;
  size_t _iteration;
};

#include "io.hpp"
