#pragma once
#include "../include/board.h"

#include <iostream>

#include "../include/piece.h"

void PrintLine() {
  std::cout << std::endl;  
  for (auto i = 0; i < 8; i++) std::cout << "---";
  std::cout << std::endl;
}
void Board::Show() {
  for (auto i = 0; i < 8; i++) {
    std::cout << "|";
    for (auto j = 0; j < 8; j++) {
      Position pos(i, j);
      
      auto it = board_position_.find(pos);
      if (it != board_position_.end()) {
        auto value = board_position_[pos];
        std::cout << value << "|";
      } else {
        std::cout << "  |";
      }
    }
    PrintLine();
  }
}

std::vector<std::string> Split(const std::string& s) {
  auto parts = std::vector<std::string>();
  auto start = 0;
  std::size_t next = 0;
  while (next != std::string::npos) {
    next = s.find(" ", start);
    parts.push_back(s.substr(start, next - start));
    start = next + 1;
  }
  return parts;
}
void Board::Initialize(const std::string& initial_position) {
  auto moves = Split(initial_position);
  for (const auto& move : moves) {
    Position position(move.substr(2));
    Piece piece(move.substr(0, 2));
    board_position_[position] = piece;
  }
}

void Board::Initialize() {
  std::string initial_position =
      "wRa1 wNb1 wBc1 wQd1 wKe1 wBf1 wNg1 wRh1 "
      "wPa2 wPb2 wPc2 wPd2 wPe2 wPf2 wPg2 wPh2 "
      "bRa8 bNb8 bBc8 bQd8 bKe8 bBf8 bNg8 bRh8 "
      "bPa7 bPb7 bPc7 bPd7 bPe7 bPf7 bPg7 bPh7";
  Initialize(initial_position);
}

std::unordered_set<Move> Board::ValidMoves() const {
  std::unordered_set<Move> moves;
  const auto& white_moves = ValidMoves(PieceColor::White);
  const auto& black_moves = ValidMoves(PieceColor::Black);

  moves.insert(white_moves.begin(), white_moves.end());
  moves.insert(black_moves.begin(), black_moves.end());

  return moves;
 }
std::unordered_set<Move> Board::ValidMoves(PieceColor color) const {
  std::unordered_set<Move> moves;

  for (const auto& it : board_position_) {
    const Piece& piece = it.second;
    if (piece.Color() != color) {
      continue;
    }
    const Position& position = it.first;
    const auto& piece_moves = piece.ValidMoves(position, board_position_, last_move_position_);
    moves.insert(piece_moves.begin(), piece_moves.end()); 
  }

  return moves;
}
std::unordered_set<Move> Board::ValidMoves(Position start) const {
  std::unordered_set<Move> moves;

  auto it = board_position_.find(start);
  if (it == board_position_.end()) {
    return moves;
  }

  const Piece& piece = it->second;
  moves = piece.ValidMoves(start, board_position_, last_move_position_);
  return moves;
}

void Board::Excute(const Move& move) { 
  board_position_.erase(move.start_);
  if (move.move_type_ == MoveType::Normal) {
    board_position_[move.end_] = Piece(move.type_, move.color_);
  } else if (move.move_type_ == MoveType::KingRookMoveA) {
    board_position_[Position(move.start_.row, Column::C)] = Piece(move.type_, move.color_);
    board_position_[Position(move.start_.row, Column::D)] = Piece(PieceType::Rook, move.color_);
    board_position_.erase(Position(move.start_.row, Column::A));
  } else if(move.move_type_ == MoveType::KingRookMoveH){
    board_position_[Position(move.start_.row, Column::G)] =
        Piece(move.type_, move.color_);
    board_position_[Position(move.start_.row, Column::F)] =
        Piece(PieceType::Rook, move.color_);
    board_position_.erase(Position(move.start_.row, Column::H));
  }
}

std::unordered_set<Move> Board::ValidMoves(
    std::unordered_map<Position, Piece> board_position, PieceColor color) {
  std::unordered_set<Move> moves;

  for (const auto& it : board_position) {
    const Piece& piece = it.second;
    if (piece.Color() != color) {
      continue;
    }
    const Position& position = it.first;
    const auto& piece_moves =
        piece.ValidMoves(position, board_position, Position{1, 1});
    moves.insert(piece_moves.begin(), piece_moves.end());
  }

  return moves;
  }