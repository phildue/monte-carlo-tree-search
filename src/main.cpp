#include <iostream>
#include <map>
#include "node.h"
#include "tic_tac_toe.h"
#include "Player.h"
int main() {

    auto game = std::make_shared<TicTacToe>();
    auto tree = std::make_shared<Node>();
    std::cout << "Tic Tac Toe Game" << std::endl;
    std::map<char, Player::ShPtr> players;
    players['X'] = std::make_shared<HumanPlayer>('X');
    players['O'] = std::make_shared<RandomPlayer>('O');
    while (!game->isWin('X') && !game->isWin('O') && !game->isDraw()) {
        std::cout << game->str() << std::endl;
        auto player = players[game->turn()];
        try{
            game->act(player->getMove(game), game->turn());
            game->switchTurn();
        }catch(std::runtime_error& e){
            std::cout << e.what() << std::endl;
        }
    }
    if (game->isDraw()) {
        std::cout << "Game is over." << "It's a draw." << std::endl;
        return 0;
    }else{
        std::cout << "Game is over." << "Player: " << (game->isWin('X') ? 'X' : 'O') << " wins." << std::endl;
    }
    return 0;
}