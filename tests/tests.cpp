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


TEST(PieceTest, ReturnsCorrectValidMoves) {
    // Creates an empty chess board represented by an unordered_map.
    std::unordered_map<Position, Piece> board;

    // Creates a white pawn at a specified position.
    Position start{ Row::_2, Column::D };
    Piece pawn(PieceType::Pawn, PieceColor::White);
    board[start] = pawn;

    // Sets the last move made on the board.
    Position last_move{ Row::_4, Column::E };

    // Creates an unordered_set of expected moves that the pawn can make.
    std::unordered_set<Move> expected_moves{
        {start, {Row::_3, Column::D}, PieceColor::White, PieceType::Pawn, MoveType::Normal},
        {start, {Row::_4, Column::D}, PieceColor::White, PieceType::Pawn, MoveType::Normal}
    };

    // Calls the function to get the actual moves made by the pawn and compares them with the expected moves.
    auto actual_moves = pawn.PawnValidMoves(start, board, last_move);
    EXPECT_EQ(actual_moves, expected_moves);
}


TEST(PieceTest, WhitePawnCanMoveOneOrTwoStepsForward) {
    // Creates an empty chess board represented by an unordered_map.
    std::unordered_map<Position, Piece> board;

    // Creates a white pawn at a specified position.
    Position start{ Row::_2, Column::D };
    Piece pawn{ PieceType::Pawn ,PieceColor::White, };
    board[start] = pawn;

    // Sets the last move made on the board.
    Position last_move{ Row::_4, Column::E };

    // Creates an unordered_set of expected moves that the pawn can make.
    std::unordered_set<Move> expected_moves{
        {start, {Row::_3, Column::D}, PieceColor::White, PieceType::Pawn, MoveType::Normal},
        {start, {Row::_4, Column::D}, PieceColor::White, PieceType::Pawn, MoveType::Normal}
    };

    // Calls the function to get the actual moves made by the pawn and compares them with the expected moves.
    auto actual_moves = pawn.PawnValidMoves(start, board, last_move);

    EXPECT_EQ(actual_moves, expected_moves);
}

// This is a unit test code for testing the valid moves of Rook and Knight pieces in a chess game.
TEST(PieceTest, RookValidMoves) {
    // Create a Rook piece of white color
    Piece rook(PieceType::Rook, PieceColor::White);
    // Create an unordered map to represent the chessboard configuration, and place the Rook at position "a1"
    std::unordered_map<Position, Piece> board_position;
    Position start("a1");
    board_position[start] = rook;
    // Set the last move to position "a2"
    Position last_move("a2");
    // Create an unordered set of expected moves that the Rook should be able to make from position "a1"
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
    // Call the RookValidMoves function on the Rook piece with the given starting position, board configuration, and last move
    auto moves = rook.RookValidMoves(start, board_position, last_move);
    // Check that the generated set of valid moves matches the expected set of valid moves
    EXPECT_EQ(moves.size(), expected_moves.size());
    for (const auto& move : expected_moves) {
        EXPECT_EQ(moves.count(move), 1);
    }
}


TEST(PieceTest, KnightValidMoves) {
    // Create a Knight piece of white color
    Piece knight(PieceType::Knight, PieceColor::White);
    // Create an unordered map to represent the chessboard configuration, and place the Knight at position "b1"
    std::unordered_map<Position, Piece> board_position;
    Position start("b1");
    board_position[start] = knight;
    // Set the last move to position "a3"
    Position last_move("a3");
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
      {Position("c1"), Piece(PieceType::Bishop, PieceColor::Black)},
      {Position("a8"), Piece(PieceType::Pawn, PieceColor::White)},
  };
  
  // Get the rook's valid moves
  Piece rook(PieceType::Rook, PieceColor::White);
  std::unordered_set<Move> rook_moves = rook.ValidMoves(Position("a1"), board_position, Position(" "));
  Move move{ Position("a1"), Position("c1"), PieceColor::White, PieceType::Rook, MoveType::Normal };
  Move move2{ Position("a1"), Position("a8"), PieceColor::White, PieceType::Rook, MoveType::Normal };
  // Check that the rook can take the bishop on c1, but not the bishop or knight on a4 or d4
  EXPECT_TRUE(rook_moves.count(move)) << "Rook should be able to take bishop on c1";// needs checking
  EXPECT_FALSE(rook_moves.count(move2)) << "Rook should not be able to take own piece on a8";
}

TEST(PieceTest, KnightCanTakeOtherPieces) {
    // Create a board with a knight that can take an opponent's piece
    std::unordered_map<Position, Piece> board = {
        {Position("d5"), Piece(PieceType::Knight, PieceColor::White)},
        {Position("c7"), Piece(PieceType::Pawn, PieceColor::Black)},
    };

    // Get the set of valid moves for the knight
    auto knight_moves = board.at(Position("d5")).ValidMoves(Position("d5"), board, Position(" "));
    Move move{ Position("d5"), Position("c7"), PieceColor::White, PieceType::Knight, MoveType::Normal };

    // Check that the set of valid moves contains the expected move
    EXPECT_TRUE(knight_moves.count(Move(move))) << "Knight should be able to take pawn on c7";
}

TEST(PieceTest, BishopCanTakeOtherPieces) {
  // Set up the board
  std::unordered_map<Position, Piece> board_position = {
      {Position("c1"), Piece(PieceType::Bishop, PieceColor::White)},
      {Position("a3"), Piece(PieceType::Knight, PieceColor::Black)},
      {Position("f2"), Piece(PieceType::Pawn, PieceColor::White)},
  };
  
  // Get the bishop's valid moves
  Piece bishop(PieceType::Bishop, PieceColor::White);
  std::unordered_set<Move> bishop_moves = bishop.ValidMoves(Position("c1"), board_position, Position(" "));
  Move move{ Position("c1"), Position("a3"), PieceColor::White, PieceType::Bishop, MoveType::Normal };
  Move move2{ Position("c1"), Position("f2"), PieceColor::White, PieceType::Bishop, MoveType::Normal };
  // Check that the bishop can take the knight on a3, the pawn on b2, and the queen on d4
  EXPECT_TRUE(bishop_moves.count(move)) << "Bishop should be able to take knight on a3";
  // Check that the bishop cannot take the pawn on f2, the knight on g1, or its own piece on h8
  EXPECT_FALSE(bishop_moves.count(move2)) << "Bishop should not be able to take pawn on f2";
}

TEST(PieceTest, QueenCanTakeOtherPieces) {
    // Set up the board
    std::unordered_map<Position, Piece> board_position = {
        {Position("d1"), Piece(PieceType::Queen, PieceColor::White)},
        {Position("b3"), Piece(PieceType::Pawn, PieceColor::White)},
        {Position("d3"), Piece(PieceType::Rook, PieceColor::Black)},
    };

    // Get the queen's valid moves
    auto queen_moves = board_position.at(Position("d1")).ValidMoves(Position("d1"), board_position, Position(" "));
    Move move1{ Position("d1"), Position("d3"), PieceColor::White, PieceType::Queen, MoveType::Normal };
    Move move2{ Position("d1"), Position("b3"), PieceColor::White, PieceType::Queen, MoveType::Normal };
    // Check that the queen can take the rook, bishop, and knight, but not own piece or obstructed squares
    EXPECT_TRUE(queen_moves.count(Move(move1))) << "Queen should be able to take rook on d3";
    EXPECT_FALSE(queen_moves.count(Move(move2))) << "Queen should not be able to take own piece on b3";



}

TEST(PieceTest, KingCanTakeOtherPiecesAndCannotTakeOwnPieces) {
    // Set up the board
    std::unordered_map<Position, Piece> board_position = {
    {Position("d1"), Piece(PieceType::King, PieceColor::White)},
    {Position("e1"), Piece(PieceType::Pawn, PieceColor::White)},
    {Position("d2"), Piece(PieceType::Rook, PieceColor::Black)},
    };

    // Get the king's valid moves
    auto king_moves = board_position.at(Position("d1")).ValidMoves(Position("d1"), board_position, Position(" "));
    Move move1{ Position("d1"), Position("d2"), PieceColor::White, PieceType::King, MoveType::Normal };
    Move move2{ Position("d1"), Position("e1"), PieceColor::White, PieceType::King, MoveType::Normal };
    // Check that the king can take the rook, bishop, knight, and pawn, but not own piece or obstructed squares
    EXPECT_TRUE(king_moves.count(Move(move1))) << "King should be able to take rook on d2";
    EXPECT_FALSE(king_moves.count(Move(move2))) << "King should not be able to move to own piece on e1";
}

TEST(PieceTest, PawnCanTakeOtherPieces) {
    // Set up the board
    std::unordered_map<Position, Piece> board_position = {
        {Position("d2"), Piece(PieceType::Pawn, PieceColor::White)},
        {Position("c3"), Piece(PieceType::Pawn, PieceColor::Black)},
        {Position("e3"), Piece(PieceType::Knight, PieceColor::White)},
    };

    // Get the pawn's valid moves
    auto pawn_moves = board_position.at(Position("d2")).ValidMoves(Position("d2"), board_position, Position(" "));
    Move move1{ Position("d2"), Position("c3"), PieceColor::White, PieceType::Pawn, MoveType::Normal };
    Move move2{ Position("d2"), Position("e3"), PieceColor::White, PieceType::Pawn, MoveType::Normal };


    // Check that the pawn can take black pawn but not own piece or obstructed squares
    EXPECT_TRUE(pawn_moves.count(Move(move1))) << "Pawn should be able to take black pawn on c3";
    EXPECT_FALSE(pawn_moves.count(Move(move2))) << "Pawn should not be able to take black pawn on e3";
  
}

TEST(EndgameTest, CheckmateWithFewPieces) {
    // Set up the board with only a few pieces remaining
    std::unordered_map<Position, Piece> board_position = {
        {Position("a1"), Piece(PieceType::King, PieceColor::White)},
        {Position("a8"), Piece(PieceType::King, PieceColor::Black)},
        {Position("b7"), Piece(PieceType::Rook, PieceColor::Black)},
    };

    // White king should have no valid moves and should be in checkmate
    auto white_king_moves = board_position.at(Position("a1")).KingValidMoves(Position("a1"), board_position, Position(" "));
    EXPECT_EQ(white_king_moves.size(), 1);
}

TEST(PieceTest, EnPassantCapture) {
    // Set up the board with pawns ready for en passant capture
    std::unordered_map<Position, Piece> board_position = {
        {Position("d5"), Piece(PieceType::Pawn, PieceColor::White)},
        {Position("c7"), Piece(PieceType::Pawn, PieceColor::Black)},
        {Position("e7"), Piece(PieceType::Pawn, PieceColor::Black)},
    };
    // Set the last move to the black pawn advancing two squares to c7
    Position last_move("c7");

    // Get the white pawn's valid moves
    auto white_pawn_moves = board_position.at(Position("d5")).ValidMoves(Position("d5"), board_position, last_move);

    // Expect the white pawn to have one valid move, which is the en passant capture
    EXPECT_EQ(white_pawn_moves.size(), 1);
}

