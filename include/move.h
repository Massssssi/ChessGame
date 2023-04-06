#pragma once

#include "piece.h"
#include "position.h"

enum class PieceColor;
enum class PieceType;


enum class MoveType {
    Normal,           // Normal move
    KingRookMoveA,    // Move of the king's rook to the A file
    KingRookMoveH     // Move of the king's rook to the H file
};


struct Move {
public:
    Position start_;     // Starting position of the move
    Position end_;       // Ending position of the move
    PieceColor color_;   // Color of the piece being moved
    PieceType type_;     // Type of the piece being moved
    MoveType move_type_; // Type of the move (Normal, KingRookMoveA, KingRookMoveH)

    // A helper function that returns a unique number representing the move.
    std::size_t AsNumber() const {
        return start_.AsNumber() * 64 + end_.AsNumber();
    }

    // Overloading the equality operator to compare two Move objects.
    bool operator==(const Move& other) const {
        return start_ == other.start_ && end_ == other.end_ && color_ == other.color_ && type_ == other.type_;
    }
};

// Defining the hash function for the Move object, which is used in unordered_set.
template <>
struct std::hash<Move> {
    std::size_t operator()(const Move& move) const noexcept {
        return move.AsNumber();
    }
};