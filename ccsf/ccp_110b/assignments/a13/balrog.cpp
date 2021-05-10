#include "balrog.h"

namespace cs_creature {

    Balrog::Balrog() {};






    Balrog::Balrog(int strength, int hitpoints)
        : Demon(strength, hitpoints) {};






    std::string Balrog::getSpecies() const {
        return "Balrog";
    }






    int Balrog::getDamage() const {
        int damage = Demon::getDamage();
        int balrogDamange = (rand() % this->getStrength()) + 1;
        std::cout << "Balrog speed attack inflicts "
                  << balrogDamange
                  << " additional damage points!"
                  << std::endl;
        damage += balrogDamange;
        return damage;
    }

}
