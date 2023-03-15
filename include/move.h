#pragma once
#include "piece.h"
#include "position.h"

enum class PieceColor;
enum class PieceType;
enum class MoveType {
    Normal,
    KingRookMoveA,
    KingRookMoveH
};
struct Move {
 public:
  Position start_;
  Position end_;
  PieceColor color_;
  PieceType type_;
  MoveType move_type_;
  std::size_t AsNumber() const { 
       return start_.AsNumber() * 64 + end_.AsNumber();
  }
  bool operator==(const Move& other) const {
    return start_ == other.start_ && end_ == other.end_ && color_ == other.color_ && type_ == other.type_;
  }
};

template <>
struct std::hash<Move> {
  std::size_t operator()(const Move& move) const noexcept {
    return move.AsNumber();
  }
};