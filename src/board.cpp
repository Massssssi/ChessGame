#include "board.h"

#include <iostream>

void PrintLine() {
  std::cout << std::endl;  
  for (auto i = 0; i < 8; i++) std::cout << "----";
  std::cout << std::endl;
}
void Board::Show() {
  for (auto i = 0; i < 8; i++) {
    for (auto j = 0; j < 8; j++) {
      Position pos;
      pos.row = static_cast<Row>(i);
      pos.column = static_cast<Column>(j);

      auto it = board_position_.find(pos);
      if (it != board_position_.end()) {
        auto value = board_position_[pos];
        std::cout << "|" << value << "|";
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