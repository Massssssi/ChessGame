#include "board.h"

#include <iostream>

#include "piece.h"

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
    const auto& piece_moves = piece.ValidMoves(position, board_position_);
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
  moves = piece.ValidMoves(start, board_position_);
  return moves;
}