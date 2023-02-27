#include "board.h"

#include <iostream>

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

std::ostream& operator<<(std::ostream& os, const Piece& piece) { 
    os << piece.ToString();
    return os; }

std::string Piece::ToString() const {
  std::string color_str = color == Color::Black ? "b" : "w";
  std::string type_str;
  switch (type) {
    case Type::Bishop:
      type_str = "B";
      break;
    case Type::King:
      type_str = "K";
      break;
    case Type::Knight:
      type_str = "N";
      break;
    case Type::Pawn:
      type_str = "P";
      break;
    case Type::Queen:
      type_str = "Q";
      break;
    case Type::Rook:
      type_str = "R";
      break;
    default:
      throw std::exception();
  }
  return color_str + type_str;
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