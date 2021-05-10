#include "creature.h"

namespace cs_creature {

    Creature::Creature() {
        strength = 10;
        hitpoints = 10;
    }






    Creature::Creature(int strengh, int hitpoints) {
        this->strength = strengh;
        this->hitpoints = hitpoints;
    }






    int Creature::getDamage() const {
        int damage = (rand() % this->strength) + 1;
        std::cout << "The "
                  << this->getSpecies()
                  << " attacks for "
                  << damage
                  << " points!"
                  << std::endl;
        return damage;
    }






    int Creature::getStrength() const {
        return this->strength;
    }






    int Creature::getHitpoints() const {
        return this->hitpoints;
    }






    bool Creature::updateStrengh(int strengh) {
        this->strength = strengh;
        return true;
    }






    bool Creature::updateHitpoints(int hitpoints) {
        this->hitpoints = hitpoints;
        return true;
    }

}
