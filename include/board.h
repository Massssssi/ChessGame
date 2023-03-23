#pragma once

#include <unordered_map>
#include <unordered_set>
#include <ostream>

#include "piece.h"
#include "position.h"
#include "move.h"




class Board {  
 public:
  Board() : last_move_position_{1, 1} {}
  void Show();
  void Initialize(const std::string& initial_position);
  void Initialize();

  void Excute(const Move& move);

  std::unordered_set<Move> ValidMoves() const;
  std::unordered_set<Move> ValidMoves(PieceColor color) const;
  std::unordered_set<Move> ValidMoves(Position start) const;
  std::unordered_set<Position> AttackedPositions(PieceColor color) const;

  static std::unordered_set<Move> ValidMoves(
      std::unordered_map<Position, Piece> board_position, PieceColor color);
  static std::unordered_set<Position> AttackedPositions(
      std::unordered_map<Position, Piece> board_position, PieceColor color);

  const Piece& operator[](const Position& position) const {
    return (*board_position_.find(position)).second;
  }
  bool Exist(const Position& position) const {
    if (board_position_.find(position) != board_position_.end()) {
      return true;
    }
    return false;
  }
 private:
  std::unordered_map<Position, Piece> board_position_;
  Position last_move_position_;
};

