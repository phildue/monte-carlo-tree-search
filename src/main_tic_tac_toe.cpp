#include <unistd.h>

#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <variant>

#include "Player.h"
#include "TicTacToe.h"
#include "io.h"
std::shared_ptr<Player<TicTacToe>> createPlayer(const std::string& type,
                                                const std::string& symbol,
                                                int iterations) {
  const std::string opponent = symbol == "X" ? "O" : "X";
  if (type == "ai") {
    return std::make_shared<AIPlayer<TicTacToe>>(
        symbol, std::make_shared<MonteCarloTreeSearch<TicTacToe>>(
                    symbol, opponent, iterations));
  } else if (type == "human") {
    return std::make_shared<HumanPlayer<TicTacToe>>(symbol);
  } else if (type == "random") {
    return std::make_shared<RandomPlayer<TicTacToe>>(symbol);
  } else {
    throw std::invalid_argument("Unknown player type: " + type);
  }
}

int main(int argc, char* argv[]) {
  std::string playerXType = "ai";
  std::string playerOType = "ai";
  int iterations = 250;

  int opt;
  while ((opt = getopt(argc, argv, "X:O:i:")) != -1) {
    switch (opt) {
      case 'X':
        playerXType = optarg;
        break;
      case 'O':
        playerOType = optarg;
        break;
      case 'i':
        iterations = std::stoi(optarg);
        break;
      default:
        std::cerr << "Usage: " << argv[0]
                  << " [-X playerXType] [-O playerOType] [-i iterations]"
                  << std::endl;
        return 1;
    }
  }

  TicTacToe game{};
  std::cout << "Tic Tac Toe Game" << std::endl;

  std::map<std::string, Player<TicTacToe>::ShConstPtr> players = {
      {"O", createPlayer(playerOType, "O", iterations)},
      {"X", createPlayer(playerXType, "X", iterations)}};

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
    std::cout << "Game is over. It's a draw." << std::endl;
  } else {
    std::cout << "Game is over. Player: " << (game.isWin("X") ? 'X' : 'O')
              << " wins." << std::endl;
  }

  return 0;
}
