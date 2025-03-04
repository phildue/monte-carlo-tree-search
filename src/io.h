
#pragma once
#include "MonteCarloTreeSearch.h"

template <IsGame Game>
void toDotFile(const std::string& filename,
               typename MonteCarloTreeSearch<Game>::Node::ShConstPtr root,
               const std::string& player);

#include "io.hpp"
