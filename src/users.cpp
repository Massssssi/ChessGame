#include"user.h"
#include <vector>
#include <iostream>
#include "users.h"



 std::unique_ptr<user> users::login(const std::string& username,
                                      const std::string& password) const {
    for (const auto& u:vtr) {
        if (u.username() == username && u.password() == password)
        {
        return std::make_unique<user>(username, password, u.age());
        }
    } 

    std::cout << "User not found!";

        
    return nullptr;
 }

 std::unique_ptr <user> users::create_user(std::string username, std::string password, int age)
{
   if (age <= 0 && password.empty() && username.empty()) {
     return nullptr;
   }

   for (const auto& u : vtr) {
     if (u.username() == username) {
       return nullptr;
     }
   }

   vtr.push_back(user(username, password, age));
   return std::make_unique<user>(vtr[vtr.size()-1]);
}
