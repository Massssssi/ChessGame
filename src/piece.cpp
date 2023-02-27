#include "piece.h"


Piece::Piece(const std::string& piece_str) {
  color_ = piece_str[0] == 'w' ? PieceColor::White : PieceColor::Black;
  switch (piece_str[1]) {
    case 'B':
      type_ = PieceType::Bishop;
      break;
    case 'K':
      type_ = PieceType::King;
      break;
    case 'N':
      type_ = PieceType::Knight;
      break;
    case 'P':
      type_ = PieceType::Pawn;
      break;
    case 'Q':
      type_ = PieceType::Queen;
      break;
    case 'R':
      type_ = PieceType::Rook;
      break;
  }
}

std::ostream& operator<<(std::ostream& os, const Piece& piece) {
  os << piece.ToString();
  return os;
}

std::string Piece::ToString() const {
  std::string color_str = color_ == PieceColor::Black ? "b" : "w";
  std::string type_str;
  switch (type_) {
    case PieceType::Bishop:
      type_str = "B";
      break;
    case PieceType::King:
      type_str = "K";
      break;
    case PieceType::Knight:
      type_str = "N";
      break;
    case PieceType::Pawn:
      type_str = "P";
      break;
    case PieceType::Queen:
      type_str = "Q";
      break;
    case PieceType::Rook:
      type_str = "R";
      break;
    default:
      throw std::exception();
  }
  return color_str + type_str;
}

std::unordered_set<Move> Piece::ValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position) const {
  std::unordered_set<Move> moves;

  switch (type_) {
    case PieceType::Bishop:
      
      break;
    case PieceType::King:
      type_str = "K";
      break;
    case PieceType::Knight:
      type_str = "N";
      break;
    case PieceType::Pawn:
      type_str = "P";
      break;
    case PieceType::Queen:
      type_str = "Q";
      break;
    case PieceType::Rook:
      type_str = "R";
      break;
    default:
      throw std::exception();
  }
}

std::unordered_set<Move> PawnValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position, PieceColor color) {
  std::unordered_set<Move> moves;
  if (color == PieceColor::White) {
    
  } else {
  
  }

}