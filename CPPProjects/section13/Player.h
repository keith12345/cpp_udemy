#ifndef _PLAYER_h_
#define _PLAYER_h_
#include <iostream>
#include <string>

class Player {
private:
    static int num_players;
public:
    std::string name;
    int* health;
    int* xp;

    Player(std::string name = "None", int health = 10, int xp = 3);
    Player(const Player& source);
    Player(Player&& source);
    ~Player();

    static int get_num_players();
    void talk(std::string str) const;
    void do_damage(int damage);
    int get_health();
};
#endif
