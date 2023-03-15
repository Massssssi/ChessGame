#pragma once
#include <unordered_set>
#include <unordered_map>
#include "../include/piece.h"
#include "../src/piece.cpp"
#include "../include/board.h"
#include "../src/board.cpp"
#include "../include/position.h"
#include "../src/position.cpp"
#include "../include/move.h"
#include "../src/move.cpp"
#include "gtest/gtest.h" // Using Google Test framework


TEST(PawnValidMovesTest, ReturnsCorrectValidMoves) {
    std::unordered_map<Position, Piece> board;
    Position start{ Row::_2, Column::D };
    Piece pawn(PieceType::Pawn, PieceColor::White );
    board[start] = pawn;
    Position last_move{ Row::_4, Column::E };

    std::unordered_set<Move> expected_moves{
        {start, {Row::_3, Column::D}, PieceColor::White, PieceType::Pawn, MoveType::Normal},
        {start, {Row::_4, Column::D}, PieceColor::White, PieceType::Pawn, MoveType::Normal}
    };
    auto actual_moves = pawn.PawnValidMoves(start, board, last_move);
    EXPECT_EQ(actual_moves, expected_moves);
}

