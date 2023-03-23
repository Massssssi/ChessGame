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

TEST(PieceTest, KnightValidMoves) {
    Piece knight(PieceType::Knight, PieceColor::White);
    std::unordered_map<Position, Piece> board_position;
    Position start("b1");
    board_position[start] = knight;
    Position last_move("a3");


    std::unordered_set<Move> expected_moves{ {start, Position("a3"), PieceColor::White, PieceType::Knight, MoveType::Normal},
                                             {start, Position("c3"), PieceColor::White, PieceType::Knight, MoveType::Normal}};
    auto moves = knight.KnightValidMoves(start, board_position, last_move);
    EXPECT_EQ(moves.size(), expected_moves.size());
    for (const auto& move : expected_moves) {
        EXPECT_EQ(moves.count(move), 1);
    }
}



TEST(PieceTest, BishopValidMoves) {
    Piece bishop(PieceType::Bishop, PieceColor::White);
    std::unordered_map<Position, Piece> board_position;
    Position start("c1");
    board_position[start] = bishop;
    Position last_move("c1");
    std::unordered_set<Move> expected_moves{ {start, Position("d2"), PieceColor::White, PieceType::Bishop, MoveType::Normal},
                                             {start, Position("e3"), PieceColor::White, PieceType::Bishop, MoveType::Normal},
                                             {start, Position("f4"), PieceColor::White, PieceType::Bishop, MoveType::Normal},
                                             {start, Position("g5"), PieceColor::White, PieceType::Bishop, MoveType::Normal},
                                             {start, Position("h6"), PieceColor::White, PieceType::Bishop, MoveType::Normal},
                                             {start, Position("b2"), PieceColor::White, PieceType::Bishop, MoveType::Normal},
                                             {start, Position("a3"), PieceColor::White, PieceType::Bishop, MoveType::Normal}};
    auto moves = bishop.BishopValidMoves(start, board_position, last_move);
    EXPECT_EQ(moves.size(), expected_moves.size());
    for (const auto& move : expected_moves) {
        EXPECT_EQ(moves.count(move), 1);
    }
}

TEST(PieceTest, QueenValidMoves) {
    Piece queen(PieceType::Queen, PieceColor::White);
    std::unordered_map<Position, Piece> board_position;
    Position start("d1");
    board_position[start] = queen;
    Position last_move("d1");
    std::unordered_set<Move> expected_moves{ {start, Position("e1"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("f1"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("g1"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("h1"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("c1"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("b1"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("a1"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("d2"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("d3"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("d4"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("d5"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("d6"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("d7"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("d8"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("e2"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("f3"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("g4"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("h5"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("c2"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("b3"), PieceColor::White, PieceType::Queen, MoveType::Normal},
                                             {start, Position("a4"), PieceColor::White, PieceType::Queen, MoveType::Normal} };
    auto moves = queen.QueenValidMoves(start, board_position, last_move);
    EXPECT_EQ(moves.size(), expected_moves.size());
    for (const auto& move : expected_moves) {
        EXPECT_EQ(moves.count(move), 1);
    }
}

TEST(PieceTest, KingValidMoves) {
    Piece king(PieceType::King, PieceColor::White);
    std::unordered_map<Position, Piece> board_position;
    Position start("e1");
    board_position[start] = king;
    Position last_move("e1");


    std::unordered_set<Move> expected_moves{ {start, Position("d1"), PieceColor::White, PieceType::King, MoveType::Normal},
                                             {start, Position("d2"), PieceColor::White, PieceType::King, MoveType::Normal},
                                             {start, Position("e2"), PieceColor::White, PieceType::King, MoveType::Normal},
                                             {start, Position("f2"), PieceColor::White, PieceType::King, MoveType::Normal},
                                             {start, Position("f1"), PieceColor::White, PieceType::King, MoveType::Normal}};

    auto moves = king.KingValidMoves(start, board_position, last_move);
    EXPECT_EQ(moves.size(), expected_moves.size());
    for (const auto& move : expected_moves) {
        EXPECT_EQ(moves.count(move), 1);
    }
}



TEST(PieceTest, RookCanTakeOtherPieces) {
  // Set up the board
  std::unordered_map<Position, Piece> board_position = {
      {Position("a1"), Piece(PieceType::Rook, PieceColor::White)},
      {Position("c1"), Piece(PieceType::Bishop, PieceColor::White)},
      {Position("a4"), Piece(PieceType::Bishop, PieceColor::Black)},
      {Position("d4"), Piece(PieceType::Knight, PieceColor::Black)},
      {Position("g4"), Piece(PieceType::Queen, PieceColor::Black)},
      {Position("a8"), Piece(PieceType::Rook, PieceColor::Black)},
      {Position("e8"), Piece(PieceType::King, PieceColor::Black)},
  };
  
  // Get the rook's valid moves
  Piece rook(PieceType::Rook, PieceColor::White);
  std::unordered_set<Move> rook_moves = rook.ValidMoves(Position("a1"), board_position, Position(""));
  Move move{ Position("a1"), Position("c1"), PieceColor::White, PieceType::Rook, MoveType::Normal };
  Move move2{ Position("a1"), Position("a4"), PieceColor::White, PieceType::Rook, MoveType::Normal };
  Move move3{ Position("a1"), Position("d4"), PieceColor::White, PieceType::Rook, MoveType::Normal };
  Move move4{ Position("a1"), Position("g4"), PieceColor::White, PieceType::Rook, MoveType::Normal };
  Move move5{ Position("a1"), Position("a8"), PieceColor::White, PieceType::Rook, MoveType::Normal };
  // Check that the rook can take the bishop on c1, but not the bishop or knight on a4 or d4
  EXPECT_TRUE(rook_moves.count(move)) << "Rook should be able to take bishop on c1";
  EXPECT_FALSE(rook_moves.count(move2)) << "Rook should not be able to take bishop on a4";
  EXPECT_FALSE(rook_moves.count(move3)) << "Rook should not be able to take knight on d4";
  EXPECT_FALSE(rook_moves.count(move4)) << "Rook should not be able to take queen on g4";
  EXPECT_FALSE(rook_moves.count(move5)) << "Rook should not be able to take own piece on a8";
}




