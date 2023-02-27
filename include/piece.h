#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "position.h"
#include "move.h"


enum class PieceColor { White, Black };
enum class PieceType { Pawn, King, Queen, Knight, Rook, Bishop };
class Piece {
 public:
  Piece() = default;
  Piece(const std::string& piece_str);  
  friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
  std::string ToString() const;

  inline PieceColor Color() const { return color_; }
  inline PieceType Type() const { return type_; }
  std::unordered_set<Move> ValidMoves(Position start, std::unordered_map<Position, Piece> board_position) const;
 private:

  PieceColor color_;
  PieceType type_;
};