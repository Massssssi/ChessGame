#include "../include/piece.h"

#include "../include/board.h"

std::unordered_set<Move> QueenRookBishopMoves(
    Position start, std::unordered_map<Position, Piece> board_position,
    PieceColor color, PieceType type,
    const std::vector<std::pair<int, int>> directions, bool one_step = false) {
  std::unordered_set<Move> moves;
  Move move = {start, start, color, type, MoveType::Normal};

  for (const auto& direction : directions) {
    Position position = start;
    while (true) {
      if (direction.first == -1 && position.row == Row::_1) {
        break;
      }
      if (direction.first == 1 && position.row == Row::_8) {
        break;
      }
      if (direction.second == -1 && position.column == Column::A) {
        break;
      }
      if (direction.second == 1 && position.column == Column::H) {
        break;
      }
      position.row =
          static_cast<Row>(static_cast<int>(position.row) + direction.first);
      position.column = static_cast<Column>(static_cast<int>(position.column) +
                                            direction.second);
      Move copy(move);
      copy.end_ = position;
      auto it = board_position.find(position);
      if (it != board_position.end()) {
        if (board_position[position].Color() != color) {
          moves.insert(copy);
        }
        break;
      }
      moves.insert(copy);
      if (one_step) {
        break;
      }
    }
  }
  return moves;
}

std::unordered_set<Position> QueenRookBishopAttackedPositions(
    Position start, std::unordered_map<Position, Piece> board_position,
    PieceColor color, PieceType type,
    const std::vector<std::pair<int, int>> directions, bool one_step = false) {
  std::unordered_set<Position> positions;

  for (const auto& direction : directions) {
    Position position = start;
    while (true) {
      if (direction.first == -1 && position.row == Row::_1) {
        break;
      }
      if (direction.first == 1 && position.row == Row::_8) {
        break;
      }
      if (direction.second == -1 && position.column == Column::A) {
        break;
      }
      if (direction.second == 1 && position.column == Column::H) {
        break;
      }
      position.row =
          static_cast<Row>(static_cast<int>(position.row) + direction.first);
      position.column = static_cast<Column>(static_cast<int>(position.column) +
                                            direction.second);

      auto it = board_position.find(position);
      if (it != board_position.end()) {
        
          positions.insert(position);
        
        break;
      }
      positions.insert(position);
      if (one_step) {
        break;
      }
    }
  }
  return positions;
}

void FilterOnKingPosition(std::unordered_set<Move>& moves,
     std::unordered_map<Position, Piece> board_position) {
  if (moves.empty()) {
    return;
  }
  const auto color = board_position[moves.begin()->start_].Color();
  Position king_position(1, 1);
  for (auto it = board_position.begin(); it != board_position.end(); ++it) {
    if (it->second.Color() == color && it->second.Type() == PieceType::King) {
      king_position = it->first;
    }
  }
  for (auto move_it = moves.begin(); move_it != moves.end();) {
    auto move = *move_it;
    auto board_copy = board_position;
    board_copy[move.end_] = Piece(move.type_, move.color_);
    board_copy.erase(move.start_);

    auto opponent_attacked_positions = Board::AttackedPositions(
        board_copy, move.color_ == PieceColor::Black ? PieceColor::White
                                                     : PieceColor::Black);
    auto it = std::find_if(opponent_attacked_positions.begin(),
                     opponent_attacked_positions.end(), [&](Position position) {
          if (king_position == position) {
            return true;
          }
          return false;
        });

    if (it != opponent_attacked_positions.end()) {
      move_it = moves.erase(move_it);
    } else {
      ++move_it;
    }
  }
}

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

std::unordered_set<Move> Piece::ValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position,
    Position last_move) const {
  std::unordered_set<Move> moves;

  switch (type_) {
    case PieceType::Bishop:
      return BishopValidMoves(start, board_position, last_move);
    case PieceType::King:
      return KingValidMoves(start, board_position, last_move);
    case PieceType::Knight:
      return KnightValidMoves(start, board_position, last_move);
    case PieceType::Pawn:
      return PawnValidMoves(start, board_position, last_move);
    case PieceType::Queen:
      return QueenValidMoves(start, board_position, last_move);
    case PieceType::Rook:
      return RookValidMoves(start, board_position, last_move);
    default:
      throw std::exception();
  }
  return moves;
}

std::unordered_set<Position> Piece::AttackedPositions(
    Position start, std::unordered_map<Position, Piece> board_position) const {
  std::unordered_set<Position> positions;

  switch (type_) {
    case PieceType::Bishop:
      return BishopAttackedPositions(start, board_position);
    case PieceType::King:
      return KingAttackedPositions(start, board_position);
    case PieceType::Knight:
      return KnightAttackedPositions(start, board_position);
    case PieceType::Pawn:
      return PawnAttackedPositions(start, board_position);
    case PieceType::Queen:
      return QueenAttackedPositions(start, board_position);
    case PieceType::Rook:
      return RookAttackedPositions(start, board_position);
    default:
      throw std::exception();
  }
  return positions;
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
    next_1position.column = left_position.column;
    if (last_move == left_position &&
        ((left_position.row == Row::_5 && color_ == PieceColor::White) ||
         (left_position.row == Row::_4 && color_ == PieceColor::Black)) &&
        board_position.find(left_position) != board_position.end() &&
        board_position[left_position].Color() != color_ &&
        board_position[left_position].Type() == PieceType::Pawn) {
      auto copy = move;      
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
    next_1position.column = right_position.column;
    if (last_move == right_position &&
        ((right_position.row == Row::_5 && color_ == PieceColor::White) ||
         (right_position.row == Row::_4 && color_ == PieceColor::Black)) &&
        board_position.find(right_position) != board_position.end() &&
        board_position[right_position].Color() != color_ &&
        board_position[right_position].Type() == PieceType::Pawn) {
      auto copy = move;      
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
  FilterOnKingPosition(moves, board_position);
  
  return moves;
}

std::unordered_set<Move> Piece::BishopValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position,
    Position last_move) const {
  // 4 Directions
  // Either Position(-1, 0)  (0,0)......(0,7)
  //                           .          .
  //                         (7,0) .....(7,7)
  // OR Position not empty. If self, no add.
  //                        if opponent, add and stop.

  const std::vector<std::pair<int, int>> directions = {
      {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

  std::unordered_set<Move> moves =
      QueenRookBishopMoves(start, board_position, color_, type_, directions);
  FilterOnKingPosition(moves, board_position);
  return moves;
}

std::unordered_set<Move> Piece::KingValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position,
    Position last_move) const {
  const std::vector<std::pair<int, int>> directions = {
      {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
  std::unordered_set<Move> moves = QueenRookBishopMoves(
      start, board_position, color_, type_, directions, true);
  // K-R
  //
  for (auto move_it = moves.begin(); move_it != moves.end();) {
    auto move = *move_it;
    auto board_copy = board_position;
    board_copy[move.end_] = Piece(move.type_, move.color_);
    board_copy.erase(start);

    auto opponent_attacked_positions = Board::AttackedPositions(
        board_copy, move.color_ == PieceColor::Black ? PieceColor::White
                                                     : PieceColor::Black);
    auto it = std::find_if(opponent_attacked_positions.begin(),
                           opponent_attacked_positions.end(), [&](Position position) {
          if (move.end_ == position) {
            return true;
          }
          return false;
        });

    if (it != opponent_attacked_positions.end()) {
      move_it = moves.erase(move_it);
    } else {
      ++move_it;
    }
  }
  auto opponent_attacked_positions = Board::AttackedPositions(
      board_position, board_position[start].Color() == PieceColor::Black
                          ? PieceColor::White
                          : PieceColor::Black);
  // Adding R-K-R moves
  if (board_position[start].Color() == PieceColor::White) {
    if (start.row != Row::_1 || start.column != Column::E) {
      return moves;
    }
    const auto b1 = Position("b1");
    const auto c1 = Position("c1");
    const auto d1 = Position("d1");
    if (board_position.find(Position("a1")) != board_position.end() && 
        board_position.find(b1) == board_position.end() &&
        board_position.find(c1) == board_position.end() &&
        board_position.find(d1) == board_position.end()) {
      auto it = std::find_if(opponent_attacked_positions.begin(),
                             opponent_attacked_positions.end(),
                             [&](Position position) {                               
                               if (b1 == position || c1 == position || d1 == position || start == position) {
                                 return true;
                               }
                               return false;
                             });

      if (it == opponent_attacked_positions.end()) {
        Move move = {start, start, board_position[start].Color(),
                     board_position[start].Type(), MoveType::KingRookMoveA};
        moves.insert(move);
      }
    }

    const auto f1 = Position("f1");
    const auto g1 = Position("g1");
    if (board_position.find(Position("h1")) != board_position.end() &&
        board_position.find(f1) == board_position.end() &&
        board_position.find(g1) == board_position.end()
        ) {
      auto it = std::find_if(opponent_attacked_positions.begin(),
                             opponent_attacked_positions.end(),
                             [&](Position position) {
                               if (f1 == position || g1 == position || start == position) {
                                 return true;
                               }
                               return false;
                             });

      if (it == opponent_attacked_positions.end()) {
        Move move = {start, start, board_position[start].Color(),
                     board_position[start].Type(), MoveType::KingRookMoveH};
        moves.insert(move);
      }
    }
  }
  if (board_position[start].Color() == PieceColor::Black) {
    if (start.row != Row::_8 || start.column != Column::E) {
      return moves;
    }

    const auto b8 = Position("b8");
    const auto c8 = Position("c8");
    const auto d8 = Position("d8");
    if (board_position.find(Position("a8")) != board_position.end() &&
        board_position.find(b8) == board_position.end() &&
        board_position.find(c8) == board_position.end() &&
        board_position.find(d8) == board_position.end()) {
      auto it = std::find_if(opponent_attacked_positions.begin(),
                             opponent_attacked_positions.end(),
                             [&](Position position) {
                               if (b8 == position || c8 == position ||
                                   d8 == position || start == position) {
                                 return true;
                               }
                               return false;
                             });

      if (it == opponent_attacked_positions.end()) {
        Move move = {start, start, board_position[start].Color(),
                     board_position[start].Type(), MoveType::KingRookMoveA};
        moves.insert(move);
      }
    }

    const auto f8 = Position("f8");
    const auto g8 = Position("g8");
    if (board_position.find(Position("h8")) != board_position.end() &&
        board_position.find(f8) == board_position.end() &&
        board_position.find(g8) == board_position.end()) {
      auto it = std::find_if(opponent_attacked_positions.begin(),
                       opponent_attacked_positions.end(), [&](Position position) {
            if (f8 == position || g8 == position || start == position) {
              return true;
            }
            return false;
          });

      if (it == opponent_attacked_positions.end()) {
        Move move = {start, start, board_position[start].Color(),
                     board_position[start].Type(), MoveType::KingRookMoveH};
        moves.insert(move);
      }
    }
  }
  return moves;
}
std::unordered_set<Move> Piece::QueenValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position,
    Position last_move) const {
  const std::vector<std::pair<int, int>> directions = {
      {1, 1}, {1, -1}, {-1, -1}, {-1, 1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  std::unordered_set<Move> moves =
      QueenRookBishopMoves(start, board_position, color_, type_, directions);
  FilterOnKingPosition(moves, board_position);
  return moves;
}
std::unordered_set<Move> Piece::KnightValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position,
    Position last_move) const {
  const std::vector<std::pair<int, int>> directions = {
      {1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-2, -1}, {-1, -2}};
  std::unordered_set<Move> moves =
      QueenRookBishopMoves(start, board_position, color_, type_, directions, true);
  FilterOnKingPosition(moves, board_position);
  return moves;
}
std::unordered_set<Move> Piece::RookValidMoves(
    Position start, std::unordered_map<Position, Piece> board_position,
    Position last_move) const {
  const std::vector<std::pair<int, int>> directions = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  std::unordered_set<Move> moves =
      QueenRookBishopMoves(start, board_position, color_, type_, directions);
  FilterOnKingPosition(moves, board_position);
  return moves;
}

std::unordered_set<Position> Piece::PawnAttackedPositions(
    Position start, std::unordered_map<Position, Piece> board_position) const {
  std::unordered_set<Position> positions;
  int step = 1;
  if (color_ == PieceColor::White) {
    step = 1;
  } else {
    step = -1;
  }
  
  auto left_position = start;
  if (start.column != Column::A) {
    left_position.column = static_cast<Column>(static_cast<int>(left_position.column) - 1);
    if ((color_ == PieceColor::White && start.row != Row::_8) || (color_ == PieceColor::Black && start.row != Row::_1)) {
      left_position.row =
          static_cast<Row>(static_cast<int>(left_position.row) + step);
      positions.insert(left_position);
    }
  }

  auto right_position = start;
  if (start.column != Column::H) {
    right_position.column =
        static_cast<Column>(static_cast<int>(right_position.column) - 1);
    if ((color_ == PieceColor::White && start.row != Row::_8) ||
        (color_ == PieceColor::Black && start.row != Row::_1)) {
      right_position.row =
          static_cast<Row>(static_cast<int>(right_position.row) + step);
      positions.insert(right_position);
    }
  }

  return positions;
}

std::unordered_set<Position> Piece::BishopAttackedPositions(
    Position start, std::unordered_map<Position, Piece> board_position) const {
  // 4 Directions
  // Either Position(-1, 0)  (0,0)......(0,7)
  //                           .          .
  //                         (7,0) .....(7,7)
  // OR Position not empty. If self, no add.
  //                        if opponent, add and stop.

  const std::vector<std::pair<int, int>> directions = {
      {1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

  std::unordered_set<Position> positions =
      QueenRookBishopAttackedPositions(start, board_position, color_, type_, directions);
  
  return positions;
}

std::unordered_set<Position> Piece::KingAttackedPositions(
    Position start, std::unordered_map<Position, Piece> board_position) const {
  const std::vector<std::pair<int, int>> directions = {
      {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};
  std::unordered_set<Position> positions = QueenRookBishopAttackedPositions(
      start, board_position, color_, type_, directions, true);

  return positions;
}

std::unordered_set<Position> Piece::QueenAttackedPositions(
    Position start, std::unordered_map<Position, Piece> board_position) const {
  const std::vector<std::pair<int, int>> directions = {
      {1, 1}, {1, -1}, {-1, -1}, {-1, 1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  std::unordered_set<Position> positions =
      QueenRookBishopAttackedPositions(start, board_position, color_, type_, directions);
  return positions;
}

std::unordered_set<Position> Piece::KnightAttackedPositions(
    Position start, std::unordered_map<Position, Piece> board_position) const {
  const std::vector<std::pair<int, int>> directions = {
      {1, 2}, {2, 1}, {-1, 2}, {2, -1}, {1, -2}, {-2, 1}, {-2, -1}, {-1, -2}};
  std::unordered_set<Position> positions = QueenRookBishopAttackedPositions(
      start, board_position, color_, type_, directions);
  return positions;
}

std::unordered_set<Position> Piece::RookAttackedPositions(
    Position start, std::unordered_map<Position, Piece> board_position) const {
  const std::vector<std::pair<int, int>> directions = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  std::unordered_set<Position> positions = QueenRookBishopAttackedPositions(
      start, board_position, color_, type_, directions);
  return positions;
}

