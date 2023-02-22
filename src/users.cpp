#include"user.h"
#include <vector>
#include <iostream>
#include "users.h"







 std::unique_ptr <user> users::login(std::string username, std::string password)
{

    for (int i = 0; i < vtr.size(); i++) {

        if (vtr[i].get_username() == username && vtr[i].get_password() == password)
        {
        return std::make_unique<user>(username, password, vtr[i].get_age());
        }
    } 

    std::cout << "User not found!";

        
    return nullptr;
 }

 std::unique_ptr <user> users::create_user(std::string username, std::string password, int age)
 {

     return std::make_unique<user>(username, password, age);

 }
