#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "../include/position.h"
#include "../include/move.h"

struct Move;
enum class PieceColor { White, Black };
enum class PieceType { Pawn, King, Queen, Knight, Rook, Bishop };
class Piece {
 public:
  Piece() = default;
  Piece(const std::string& piece_str);
  Piece(PieceType type, PieceColor color);
  friend std::ostream& operator<<(std::ostream& os, const Piece& piece);
  std::string ToString() const;

  inline PieceColor Color() const { return color_; }
  inline PieceType Type() const { return type_; }
  std::unordered_set<Move> ValidMoves(
      Position start, std::unordered_map<Position, Piece> board_position,
      Position last_move) const;
  std::unordered_set<Position> AttackedPositions(
      Position start, std::unordered_map<Position, Piece> board_position) const;

  std::unordered_set<Move> PawnValidMoves(
      Position start, std::unordered_map<Position, Piece> board_position,
      Position last_move) const;
  std::unordered_set<Move> BishopValidMoves(
      Position start, std::unordered_map<Position, Piece> board_position,
      Position last_move) const;
  std::unordered_set<Move> KingValidMoves(
      Position start, std::unordered_map<Position, Piece> board_position,
      Position last_move) const;
  std::unordered_set<Move> QueenValidMoves(
      Position start, std::unordered_map<Position, Piece> board_position,
      Position last_move) const;
  std::unordered_set<Move> KnightValidMoves(
      Position start, std::unordered_map<Position, Piece> board_position,
      Position last_move) const;
  std::unordered_set<Move> RookValidMoves(
      Position start, std::unordered_map<Position, Piece> board_position,
      Position last_move) const;

  std::unordered_set<Position> PawnAttackedPositions(
      Position start, std::unordered_map<Position, Piece> board_position) const;
  std::unordered_set<Position> BishopAttackedPositions(
      Position start, std::unordered_map<Position, Piece> board_position) const;
  std::unordered_set<Position> KingAttackedPositions(
      Position start, std::unordered_map<Position, Piece> board_position) const;
  std::unordered_set<Position> QueenAttackedPositions(
      Position start, std::unordered_map<Position, Piece> board_position) const;
  std::unordered_set<Position> KnightAttackedPositions(
      Position start, std::unordered_map<Position, Piece> board_position) const;
  std::unordered_set<Position> RookAttackedPositions(
      Position start, std::unordered_map<Position, Piece> board_position) const;

  PieceColor color_;
  PieceType type_;
};