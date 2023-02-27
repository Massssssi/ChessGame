#pragma once

#include <unordered_map>
#include <ostream>

enum class Color { White, Black };
enum class Type { Pawn, King, Queen, Knight, Rook, Bishop };
class Piece {
 public:
  Piece() = default;
  Piece(const std::string& piece_str) {
    color = piece_str[0] == 'w' ? Color::White : Color::Black;
    switch (piece_str[1]) {
      case 'B':
        type = Type::Bishop;
        break;
      case 'K':
        type = Type::King;
        break;
      case 'N':
        type = Type::Knight;
        break;
      case 'P':
        type = Type::Pawn;
        break;
      case 'Q':
        type = Type::Queen;
        break;
      case 'R':
        type = Type::Rook;
        break;
    }
  }
  friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
  Color color;
  Type type;
  std::string ToString() const;
};

enum class Row { _1, _2, _3, _4, _5, _6, _7, _8 };
enum class Column { A, B, C, D, E, F, G, H };
class Position {
 public:
  //Position() = default;
  Position(const std::string& position_str) {
    row = static_cast<Row>(position_str[1]-'1');
    column = static_cast<Column>(position_str[0] -'a');
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

template<>
struct std::hash<Position> {
  std::size_t operator()(const Position& position) const noexcept { return position.AsNumber(); }
};
class PiecePosition {
  Piece piece;
  Position position;
};

class Board {
 public:
  void Show();
  void Initialize(const std::string& initial_position);
 private:
  // 8x8 cells
  // cell -> empty: Piece.
  // Piece type, color.

  // move bknc4
  // board position: b_king-xx;king-xx; [piece_position]*
  // piece_position: e4
  std::unordered_map<Position, Piece> board_position_;
};

