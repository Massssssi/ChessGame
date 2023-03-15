#include<string>


class user {
  user() = delete;

 public:
    //getters.


    //std::string fullname() const { return full_name_; }
    std::string& fullname() { return full_name_; }
    void fullname(std::string fullname) { full_name_ = fullname; }

    std::string username() const
    {
        return username_;
    }
    std::string& username() { return username_; }

    std::string password() const {
        return password_;
    }
    std::string& password() { return password_; }

    int age() const
    {
        return age_;
    }
    int& age() { return age_; }
    
    user(std::string username, std::string password, int age);

    int total_games() const { return game_won_ + game_lost_ + game_draw_; }

private:
    std::string username_;
    std::string password_;
    std::string full_name_;
    int age_;
    int points_;
    int game_won_;
    int game_lost_;
    int game_draw_;
};
