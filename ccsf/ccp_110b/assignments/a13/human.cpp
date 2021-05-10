#include "human.h"

namespace cs_creature {

    Human::Human() {};






    Human::Human(int strength, int hitpoints)
        : Creature(strength, hitpoints) {};






    std::string Human::getSpecies() const {
        return "Human";
    }

}
