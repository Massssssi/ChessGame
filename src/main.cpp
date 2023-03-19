#include <vector>
#include <iostream>
#include "../include/user.h"
#include "../include/users.h"
#include "../include/board.h"


int main() {
  Board board;
  board.Initialize();
  board.Show();

  std::string input;
  bool white_to_play = true;
  while (true) {
    printf("*************************************************************\n");
    std::cout << (white_to_play? "white ":"black ") <<"to play:" << std::endl;
    std::cout << "Enter move:" << std::endl;
    std::cin >> input;

    if (input.empty() || input == "0") {
      break;
    }
    if (input.size() != 4) {
      std::cout << "This is not a move! Please retry." << std::endl;
      continue;
    }
    Position start = Position(input.substr(0, 2));
    Position end = Position(input.substr(2, 2));
    if (!board.Exist(start)) {
      std::cout << "This is not a move! Please retry." << std::endl;
      continue;
    }
    PieceType type = board[start].Type();
    PieceColor color = board[start].Color();
    Move move = {start, end, color, type};
    auto valid_moves =
        board.ValidMoves(white_to_play ? PieceColor::White : PieceColor::Black);
    auto it = valid_moves.find(move);
    if (it == valid_moves.end()) {
      std::cout << "This move is not allowed! Please retry." << std::endl;
      continue;
    }
    board.Excute(move);
    board.Show();
    white_to_play = !white_to_play;
  }
  
  //auto moves = board.ValidMoves(Position("e4"));

  //board.Excute(*moves.begin());

  //std::cout << "------------------- Move PAWN------------------------"
  //          << std::endl;
  //board.Show();
    int choice = 0;
    std::string username;
    std::string password;
    int age;

    users users;


    while (choice!=3)
    {
        printf("*************************************************************\n");
        std::cout << "choose an option: \n";
        std::cout << "1-Login. \n";
        std::cout << "2-Register\n";
        std::cout << "3-exit. \n";
        std::cin >> choice;


        switch (choice)
        {
        case 1:
            std::cout << "enter your username: \n";
          std::cin >> username;
            std::cout << "enter your password: \n";
          std::cin >> password;
            users.login(username, password);
            break;

        case 2:
          std::cout << "choose a username: \n";
          std::cin >> username;
          std::cout << "choose a password: \n";
          std::cin >> password;
          std::cout << "enter your age: \n";
          std::cin >> age;
            users.create_user(username, password, age);
        }
    }
}



