#include "demon.h"

namespace cs_creature {

    Demon::Demon() {};






    Demon::Demon(int strength, int hitpoints)
        : Creature(strength, hitpoints) {};






    int Demon::getDamage() const {
        int damage = Creature::getDamage();
        if (rand() % 4 == 0) {
            std::cout << "Demonic attack inflicts 50 additional damage points!"
                      << std::endl;
            damage += 50;
        }
        return damage;
    }

}
