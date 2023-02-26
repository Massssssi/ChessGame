#pragma once

#include <unordered_map>
#include <ostream>

enum class Color { White, Black };
enum class Type { Pawn, King, Queen, Knight, Rook, Bishop };
class Piece {
 public:
  friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
  Color color;
  Type type;
  std::string ToString() const;
};

enum class Row { _1, _2, _3, _4, _5, _6, _7, _8 };
enum class Column { A, B, C, D, E, F, H, G };
class Position {
 public:
  Row row;
  Column column;
  int AsNumber() {
    return static_cast<int>(row) * 8 + static_cast<int>(column);
  }
};

class PiecePosition {
  Piece piece;
  Position position;
};

class Board {
 public:
  void Show();

 private:
  // 8x8 cells
  // cell -> empty: Piece.
  // Piece type, color.

  // move bknc4
  // board position: b_king-xx;king-xx; [piece_position]*
  // piece_position: e4
  std::unordered_map<Position, Piece> board_position_;
};

