#include <vector>
#include <iostream>
#include "user.h"
#include "users.h"
#include "board.h"

using namespace std;


int main() {
  Board board;
  board.Initialize("wPe4 bKh8 bNf3");
  board.Show();

    int choice = 0;
    std::string username;
    std::string password;
    int age;

    users users;


    while (choice!=3)
    {
        printf("*************************************************************\n");
        cout << "choose an option: \n";
        cout << "1-Login. \n";
        cout << "2-Register\n";
        cout << "3-exit. \n";
        cin >> choice;


        switch (choice)
        {
        case 1:
            cout << "enter your username: \n";
            cin >> username;
            cout << "enter your password: \n";
            cin >> password;
            users.login(username, password);
            break;

        case 2:
            cout << "choose a username: \n";
            cin >> username;
            cout << "choose a password: \n";
            cin >> password;
            cout << "enter your age: \n";
            cin >> age;
            users.create_user(username, password, age);
        }
    }
}



