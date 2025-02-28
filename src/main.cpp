#include <iostream>
#include <map>
#include <variant>

#include "Player.h"
#include "TicTacToe.h"
int main() {
  TicTacToe game{};
  std::cout << "Tic Tac Toe Game" << std::endl;
  std::map<std::string, Player<TicTacToe>::ShConstPtr> players = {
      {"O",
       std::make_shared<AIPlayer<TicTacToe>>(
           "O", std::make_shared<MonteCarloTreeSearch<TicTacToe>>("O", 1000))},
      {"X",
       std::make_shared<AIPlayer<TicTacToe>>(
           "X", std::make_shared<MonteCarloTreeSearch<TicTacToe>>("X", 1000))}

  };
  while (!game.isWin("X") && !game.isWin("O") && !game.isDraw()) {
    std::cout << game.str() << std::endl;
    auto player = players[game.turn()];
    try {
      game.act(player->getAction(game));
    } catch (std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }
  }
  if (game.isDraw()) {
    std::cout << "Game is over." << "It's a draw." << std::endl;
    return 0;
  } else {
    std::cout << "Game is over." << "Player: " << (game.isWin("X") ? 'X' : 'O')
              << " wins." << std::endl;
  }
  return 0;
}
