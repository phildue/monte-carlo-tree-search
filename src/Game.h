#pragma once

#include <string>
#include <vector>
template <typename T>
concept IsGame =
    requires(T game, typename T::Action action, std::string player) {
      { game.str() } -> std::convertible_to<std::string>;
      { game.isWin(player) } -> std::convertible_to<bool>;
      { game.isDraw() } -> std::convertible_to<bool>;
      {
        game.possibleActions()
      } -> std::convertible_to<std::vector<typename T::Action>>;
      { game.act(action) } -> std::same_as<void>;
    };
