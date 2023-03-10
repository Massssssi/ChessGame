#include "piece.h"

#include "board.h"



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
Piece::Piece(PieceType type, PieceColor color) : color_{color}, type_{type} {}

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



std::unordered_set<Move> Piece::PawnValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position,
    Position last_move) const {
  std::unordered_set<Move> moves;
  int step = 1;
  if (color_ == PieceColor::White) {
    step = 1;
  } else {
    step = -1;
  }

  Move move = {start, start, color_, type_, MoveType::Normal};
  // move.piece_ = *this;
  // move.start_ = start;

  auto next_1position = start;
  next_1position.row =
      static_cast<Row>(static_cast<int>(next_1position.row) + step);
  if (board_position.find(next_1position) == board_position.end()) {
    auto copy = move;
    copy.end_ = next_1position;
    moves.insert(copy);
  }
  auto next_2position = next_1position;
  next_2position.row =
      static_cast<Row>(static_cast<int>(next_2position.row) + step);
  if ((start.row == Row::_2 && color_ == PieceColor::White ||
       start.row == Row::_7 && color_ == PieceColor::Black) &&
      board_position.find(next_1position) == board_position.end() &&
      board_position.find(next_2position) == board_position.end()) {
    auto copy = move;
    copy.end_ = next_2position;
    moves.insert(copy);
  }

  if (start.column != Column::A) {
    auto left_position = start;

    left_position.column =
        static_cast<Column>(static_cast<int>(left_position.column) - 1);

    if (last_move == left_position &&
        ((left_position.row == Row::_5 && color_ == PieceColor::White) ||
         (left_position.row == Row::_4 && color_ == PieceColor::Black)) &&
        board_position.find(left_position) != board_position.end() &&
        board_position[left_position].Color() != color_ &&
        board_position[left_position].Type() == PieceType::Pawn) {
      auto copy = move;
      next_1position.column = left_position.column;
      copy.end_ = next_1position;
      moves.insert(copy);
    }

    if (board_position.find(next_1position) != board_position.end() &&
        board_position[next_1position].Color() != color_) {
      auto copy = move;
      copy.end_ = next_1position;
      moves.insert(copy);
    }
  }

  if (start.column != Column::H) {
    auto right_position = start;

    right_position.column =
        static_cast<Column>(static_cast<int>(right_position.column) + 1);

    if (last_move == right_position &&
        ((right_position.row == Row::_5 && color_ == PieceColor::White) ||
         (right_position.row == Row::_4 && color_ == PieceColor::Black)) &&
        board_position.find(right_position) != board_position.end() &&
        board_position[right_position].Color() != color_ &&
        board_position[right_position].Type() == PieceType::Pawn) {
      auto copy = move;
      next_1position.column = right_position.column;
      copy.end_ = next_1position;
      moves.insert(copy);
    }

    if (board_position.find(next_1position) != board_position.end() &&
        board_position[next_1position].Color() != color_) {
      auto copy = move;
      copy.end_ = next_1position;
      moves.insert(copy);
    }
  }

  // start.row += step;
  // start.row += step; start.column +/-= 1;
  // start.row += 2 * step;
  //FilterOnKingPosition(moves, board_position);
  
  return moves;
}


