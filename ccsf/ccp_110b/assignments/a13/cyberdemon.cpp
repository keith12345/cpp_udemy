#include "cyberdemon.h"

namespace cs_creature {

    Cyberdemon::Cyberdemon() {};






    Cyberdemon::Cyberdemon(int strength, int hitpoints)
        : Demon(strength, hitpoints) {};






    std::string Cyberdemon::getSpecies() const {
        return "Cyberdemon";
    }

}
