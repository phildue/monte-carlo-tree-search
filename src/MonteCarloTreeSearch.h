#pragma once

#include <memory>
#include <vector>
#include <math.h>
#include "TicTacToe.h"
#include "Node.h"
class MonteCarloTreeSearch {
public:
    using ShPtr = std::shared_ptr<MonteCarloTreeSearch>;
    using ShConstPtr = std::shared_ptr<const MonteCarloTreeSearch>;

    struct Meta{
        int action;
        TicTacToe::ShPtr game;
        int nVisits = 0;
        double totalReward = 0;
        float ucb1 = std::numeric_limits<float>::max();
    };
    

    MonteCarloTreeSearch(char player, int maxIterations, float ucbConstant = std::sqrt(2)):_player{player},_maxIterations{maxIterations},_ucbConstant{ucbConstant}{};
    ~MonteCarloTreeSearch() = default;

    int findNextMove(TicTacToe::ShConstPtr game) const;
    Node<Meta>::ShPtr select(Node<Meta>::ShPtr node) const;
    Node<Meta>::ShPtr expand(Node<Meta>::ShPtr node) const;
    float simulate(Node<Meta>::ShConstPtr node) const;
    void backpropagate(Node<Meta>::ShPtr node, int result) const;
    float ucb1(Node<MonteCarloTreeSearch::Meta>::ShConstPtr node) const;
private:
    char _player;
    int _maxIterations;
    float _ucbConstant;
};


