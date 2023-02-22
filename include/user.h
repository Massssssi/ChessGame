#pragma once

#include<string>


class user
{
    user() = delete;

  
public:


    //getters.
    std::string get_fullname()
    {
        return full_name;
    }

    std::string get_username()
    {
        return username;
    }

    std::string get_password()
    {
        return password;
    }

    int get_age()
    {
        return age;
    }



    //setters.
    void set_username(std::string Username)
    {
        username = Username;
    }

    void set_password(std::string Password)
    {
        password = password;
    }

    void set_age(int Age)
    {
        age = Age;
    }


    
    user(std::string username, std::string password, int age);

private:
    std::string username;
    std::string password;
    std::string full_name;
    int age;
    int points;
    int game_played;
    int game_won;
    int game_lost;
    int game_draw;
};

