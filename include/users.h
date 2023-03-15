#include"user.h"
#include <vector>
#include <iostream>


class users {
  std::vector<user> vtr;

 public:
  users() { 
    create_user("user_1", "pass", 20);
    create_user("user_2", "pass", 10);
    create_user("user_3", "pass", 50);
  }

	std::unique_ptr <user> create_user(std::string username, std::string password, int age);

	std::vector <bool> delete_users(std::vector <user> User);

	user update_user(std::string username, std::string password);

	std::unique_ptr <user> login(const std::string& username, const std::string& password) const;

	void recover_password(std::string username);

};
