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

    Human::Human() {};
    Human::Human(int strength, int hitpoints)
        : Creature(strength, hitpoints) {};
    std::string Human::getSpecies() const {
        return "Human";
    }
    //int Human::getDamage() const {
    //    std::cout << "The Human";
    //    int damage = Creature::getDamage();
    //    return damage;
    //}

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

    Cyberdemon::Cyberdemon() {};
    Cyberdemon::Cyberdemon(int strength, int hitpoints)
        : Demon(strength, hitpoints) {};
    std::string Cyberdemon::getSpecies() const {
        return "Cyberdemon";
    }

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
