# Monte Carlo Tree Search for Tic Tac Toe

This repository contains C++ code that implements a Monte Carlo Tree Search (MCTS) algorithm for playing Tic Tac Toe.

## Features

- Implementation of MCTS algorithm
- Tic Tac Toe game logic
- Command-line interface for playing against the AI

## Monte Carlo Tree Search (MCTS) Algorithm

Monte Carlo Tree Search (MCTS) is a heuristic search algorithm used for decision-making processes, particularly in game playing. It combines the precision of tree search with the generality of random sampling. The algorithm consists of four main steps:

1. **Selection**: Starting from the root node, select successive child nodes until a leaf node is reached. The selection is based on a policy, often the Upper Confidence Bound (UCB1).

2. **Expansion**: If the leaf node is not a terminal state, one or more child nodes are generated and added to the tree.

3. **Simulation**: A simulation (or playout) is run from the newly added node to a terminal state using a default policy, typically random moves.

4. **Backpropagation**: The result of the simulation is propagated back through the tree, updating the nodes' statistics.

MCTS is particularly effective for games with large state spaces and has been successfully applied to various games, including Go, Chess, and Tic Tac Toe.

## C++ Implementation

In this implementation we try to apply modern C++ language features e.g. concepts.

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
- CMake (optional, for building)

### Building

To build the project, you can use the following commands:

```sh
mkdir build
cd build
cmake ..
make
```

### Running

After building the project, you can run the executable:

```sh
./tic_tac_toe
```

## Usage

Follow the on-screen instructions to play Tic Tac Toe against the AI powered by the MCTS algorithm.

## Acknowledgements

- [Monte Carlo Tree Search](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search)
- [Tic Tac Toe](https://en.wikipedia.org/wiki/Tic-tac-toe)
