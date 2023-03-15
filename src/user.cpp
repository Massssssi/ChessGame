#include "../include/user.h"


user::user(std::string username, std::string password, int age)
    : username_{username},
      password_{password},
      age_{age},
      game_draw_{0},
      game_lost_{0},
      game_won_{0},
      points_{0} {

}

