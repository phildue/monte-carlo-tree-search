#pragma once
#include <algorithm>
#include <fstream>
#include <functional>
#include <string>

#include "MonteCarloTreeSearch.h"

template <IsGame Game>
void toDotFile(const std::string& filename,
               typename MonteCarloTreeSearch<Game>::Node::ShConstPtr root,
               const std::string& player) {
  std::ofstream file(filename);
  using Node = typename MonteCarloTreeSearch<Game>::Node;
  file << "digraph G {\n";
  std::function<void(typename Node::ShConstPtr, int)> drawNode =
      [&](typename Node::ShConstPtr node, int thickness) {
        std::string color;
        auto otherPlayer = player == "X" ? "O" : "X";
        if (node->data().game.isWin(player)) {
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
        const double scoreF = node->data().game.turn() == player ? 1.0 : -1.0;
        auto maxChild = std::max_element(
            children.begin(), children.end(), [scoreF](auto a, auto b) {
              return scoreF * a->data().score < scoreF * b->data().score;
            });

        for (const auto& child : children) {
          file << "  \"" << node.get() << "\" -> \"" << child.get() << "\";\n";
          drawNode(child, child == *maxChild ? 3 : 1);
        }
      };
  drawNode(root, 1);
  file << "}\n";
  file.close();
}
