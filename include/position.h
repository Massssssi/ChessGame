#pragma once

#include <string>
#include <unordered_map>

enum class Row { _1, _2, _3, _4, _5, _6, _7, _8 };
enum class Column { A, B, C, D, E, F, G, H };
class Position {
 public:
  // Position() = default;
  Position(const std::string& position_str) {
    row = static_cast<Row>(position_str[1] - '1');
    column = static_cast<Column>(position_str[0] - 'a');
  }
  Position(int i, int j) {
    row = static_cast<Row>(i);
    column = static_cast<Column>(j);
  }
  Row row;
  Column column;
  int AsNumber() const {
    return static_cast<int>(row) * 8 + static_cast<int>(column);
  }
  bool operator==(const Position& other) const {
    return AsNumber() == other.AsNumber();
  }
};

template <>
struct std::hash<Position> {
  std::size_t operator()(const Position& position) const noexcept {
    return position.AsNumber();
  }
};