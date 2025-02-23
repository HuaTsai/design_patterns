#pragma once

#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>

enum class Direction : std::uint8_t { kUp, kDown, kLeft, kRight };

inline std::string GetDirectionSymbol(Direction direction) {
  switch (direction) {
    case Direction::kUp:
      return "↑";
    case Direction::kDown:
      return "↓";
    case Direction::kLeft:
      return "←";
    case Direction::kRight:
      return "→";
    default:
      throw std::invalid_argument("Invalid direction");
  }
}

inline Direction GetRandomDirection() {
  static std::uniform_int_distribution<int> dis(0, 3);
  static std::default_random_engine dre(std::random_device{}());
  return static_cast<Direction>(dis(dre));
}
