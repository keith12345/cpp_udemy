#include "elf.h"

namespace cs_creature {

    Elf::Elf() {};






    Elf::Elf(int strength, int hitpoints)
        : Creature(strength, hitpoints) {};






    std::string Elf::getSpecies() const {
        return "Elf";
    }






    int Elf::getDamage() const {
        int damage = Creature::getDamage();
        if (rand() % 2 == 0) {
            std::cout << "Magical attack inflicts "
                      << damage
                      << " additional damage points!"
                      << std::endl;
            damage *= 2;
        }
        return damage;
    }

}
