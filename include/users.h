#pragma once

#include"user.h"
#include <vector>
#include <iostream>


class users {

public:
	std::vector <user> vtr;

	std::unique_ptr <user> create_user(std::string username, std::string password, int age);

	std::vector <bool> delete_users(std::vector <user> User);

	user update_user(std::string username, std::string password);

	std::unique_ptr <user> login(std::string username, std::string password);

	void recover_password(std::string username);

};
