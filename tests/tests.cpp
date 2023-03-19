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
#include "./include/gtest/gtest.h" // Using Google Test framework


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

TEST(PawnValidMovesTest, WhitePawnCanMoveOneOrTwoStepsForward) {
    std::unordered_map<Position, Piece> board;
    Position start{ Row::_2, Column::D };
    Piece pawn{ PieceType::Pawn ,PieceColor::White,};
    board[start] = pawn;
    Position last_move{ Row::_4, Column::E };

    std::unordered_set<Move> expected_moves{
        {start, {Row::_3, Column::D}, PieceColor::White, PieceType::Pawn, MoveType::Normal},
        {start, {Row::_4, Column::D}, PieceColor::White, PieceType::Pawn, MoveType::Normal}
    };
    auto actual_moves = pawn.PawnValidMoves(start, board, last_move);

    EXPECT_EQ(actual_moves, expected_moves);
}

TEST(PieceTest, RookValidMoves) {
    Piece rook(PieceType::Rook,PieceColor::White);
    std::unordered_map<Position, Piece> board_position;
    Position start("a1");
    board_position[start] = rook;
    Position last_move("a2");
    std::unordered_set<Move> expected_moves{ {start, Position("b1"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("c1"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("d1"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("e1"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("f1"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("g1"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("h1"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("a2"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("a3"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("a4"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("a5"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("a6"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("a7"), PieceColor::White, PieceType::Rook, MoveType::Normal},
                                             {start, Position("a8"), PieceColor::White, PieceType::Rook, MoveType::Normal} };
    auto moves = rook.RookValidMoves(start, board_position, last_move);
    EXPECT_EQ(moves.size(), expected_moves.size());
    for (const auto& move : expected_moves) {
        EXPECT_EQ(moves.count(move), 1);
    }
}
