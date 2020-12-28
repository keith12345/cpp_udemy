#include "Player.h"

int Player::num_players {0};

Player::Player(std::string name_val, int health_val, int xp_val)
  : name {name_val} {
    health = new int;
    xp = new int;
    *health = health_val;
    *xp = xp_val;
    num_players++;
}

Player::Player(const Player& source)
  : Player::Player(source.name, std::move(*source.health), std::move(*source.xp)) {}

Player::~Player() {
  delete health;
  delete xp;
  num_players--;
}

Player::Player(Player&& source)
  : name {source.name}, health {source.health}, xp {source.xp} {
    source.health = nullptr;
    source.xp = nullptr;
}

int Player::get_num_players() {
  return num_players;
}

void Player::talk(std::string str) const {
    std::cout << name << " says "<< str << std::endl;
}
void Player::do_damage(int damage) {
    *health -= damage;
    std::cout << "You now have " << *health << " health" << std::endl;
}

int Player::get_health() {
    return std::move(*health);
}
