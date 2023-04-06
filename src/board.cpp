#include "../include/board.h"

#include <iostream>

#include "../include/piece.h"



// helper function to print a line of hyphens
void PrintLine() {
    std::cout << std::endl;
    for (auto i = 0; i < 8; i++) std::cout << "---";
    std::cout << std::endl;
}

// function to display the chess board
void Board::Show() {
    for (auto i = 0; i < 8; i++) {
        std::cout << "|";
        for (auto j = 0; j < 8; j++) {
            Position pos(i, j);

            auto it = board_position_.find(pos);
            if (it != board_position_.end()) {
                auto value = board_position_[pos];
                std::cout << value << "|";
            }
            else {
                std::cout << "  |";
            }
        }
        PrintLine();
    }
}

// function to split a string into parts separated by spaces
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

// function to initialize the chess board with pieces
void Board::Initialize(const std::string& initial_position) {
    auto moves = Split(initial_position);
    for (const auto& move : moves) {
        Position position(move.substr(2));
        Piece piece(move.substr(0, 2));
        board_position_[position] = piece;
    }
}

// function to initialize the chess board with default pieces
void Board::Initialize() {
    std::string initial_position =
        "wRa1 wNb1 wBc1 wQd1 wKe1 wBf1 wNg1 wRh1 "
        "wPa2 wPb2 wPc2 wPd2 wPe2 wPf2 wPg2 wPh2 "
        "bRa8 bNb8 bBc8 bQd8 bKe8 bBf8 bNg8 bRh8 "
        "bPa7 bPb7 bPc7 bPd7 bPe7 bPf7 bPg7 bPh7";
    Initialize(initial_position);
}

// function to obtain all valid moves for the pieces on the board
std::unordered_set<Move> Board::ValidMoves() const {
    std::unordered_set<Move> moves;
    const auto& white_moves = ValidMoves(PieceColor::White);
    const auto& black_moves = ValidMoves(PieceColor::Black);

    moves.insert(white_moves.begin(), white_moves.end());
    moves.insert(black_moves.begin(), black_moves.end());

    return moves;
}

// function to obtain valid moves for pieces of a particular color
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

    // Find the piece at the starting position
    auto it = board_position_.find(start);
    if (it == board_position_.end()) {
        // If there is no piece at the starting position, return an empty set of moves
        return moves;
    }

    // Get the piece at the starting position
    const Piece& piece = it->second;

    // Get the valid moves for the piece
    moves = piece.ValidMoves(start, board_position_, last_move_position_);


    return moves;
}

// this function executes moves
void Board::Excute(const Move& move) {
    // Remove the piece from the starting position
    board_position_.erase(move.start_);

    if (move.move_type_ == MoveType::Normal) {
        // If it's a normal move, place the piece at the end position
        board_position_[move.end_] = Piece(move.type_, move.color_);
    }
    else if (move.move_type_ == MoveType::KingRookMoveA) {
        // If it's a king-side castling move, move the king and rook accordingly
        board_position_[Position(move.start_.row, Column::C)] = Piece(move.type_, move.color_);
        board_position_[Position(move.start_.row, Column::D)] = Piece(PieceType::Rook, move.color_);
        board_position_.erase(Position(move.start_.row, Column::A));
    }
    else if (move.move_type_ == MoveType::KingRookMoveH) {
        // If it's a queen-side castling move, move the king and rook accordingly
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

    // Loop through all pieces on the board
    for (const auto& it : board_position) {
        const Piece& piece = it.second;

        // If the piece is not of the specified color, skip it
        if (piece.Color() != color) {
            continue;
        }

        const Position& position = it.first;


        const auto& piece_moves =
            piece.ValidMoves(position, board_position, Position{ 1, 1 });

        // Add the piece's valid moves to the set of moves
        moves.insert(piece_moves.begin(), piece_moves.end());
    }

    // Return the set of valid moves
    return moves;
}

// This function takes a map of board positions and a piece color and returns a set of positions
// that are attacked by pieces of the given color
std::unordered_set<Position> Board::AttackedPositions(
    std::unordered_map<Position, Piece> board_position, PieceColor color) {
    std::unordered_set<Position> positions;

    // Iterate through all the pieces on the board
    for (const auto& it : board_position) {
        const Piece& piece = it.second;
        // If the color of the piece is not the same as the given color, skip this piece
        if (piece.Color() != color) {
            continue;
        }
        // Get the position of the piece and the set of positions it attacks
        const Position& position = it.first;
        const auto& attacked_positions =
            piece.AttackedPositions(position, board_position);
   
        positions.insert(attacked_positions.begin(), attacked_positions.end());
    }

    return positions;
}

// This function takes a piece color and returns a set of positions that are attacked by pieces
// of the given color on the current board position
std::unordered_set<Position> Board::AttackedPositions(
    PieceColor color) const {
    // Call the other AttackedPositions function with the current board position and the given color
    std::unordered_set<Position> positions =
        Board::AttackedPositions(board_position_, color);

 
    return positions;
}