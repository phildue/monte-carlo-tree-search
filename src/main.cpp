#include <iostream>
#include <map>
#include "TicTacToe.h"
#include "Player.h"
int main() {

    auto game = std::make_shared<TicTacToe>();
    std::cout << "Tic Tac Toe Game" << std::endl;
    std::map<char, Player::ShPtr> players;
    players['O'] = std::make_shared<HumanPlayer>('O');
    players['X'] = std::make_shared<AIPlayer>('X', std::make_shared<MonteCarloTreeSearch>('X', 1000));
    while (!game->isWin('X') && !game->isWin('O') && !game->isDraw()) {
        std::cout << game->str() << std::endl;
        auto player = players[game->turn()];
        try{
            game->act(player->getMove(game), game->turn());
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