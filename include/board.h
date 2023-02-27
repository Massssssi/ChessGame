#pragma once

#include <unordered_map>
#include <unordered_set>
#include <ostream>

#include "piece.h"
#include "position.h"
#include "move.h"




//class PiecePosition {
//  Piece piece;
//  Position position;
//};

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

  std::unordered_set<Move> ValidMoves() const;
  std::unordered_set<Move> ValidMoves(PieceColor color) const;
  std::unordered_set<Move> ValidMoves(Position start) const;
  //  case1: pieceIsValidMove(position -> position)
  // case2: piece, position -> all valid positions.
};

