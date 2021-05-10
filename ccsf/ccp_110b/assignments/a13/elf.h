#include <string>
#include <iostream>
#include "creature.h"
using namespace std;

#ifndef ELF_H
#define ELF_H

namespace cs_creature {

    class Elf: public Creature {
        public:
            Elf();
            Elf(int strengh, int hitpoints);
            string getSpecies() const;
            int getDamage() const;
    };

}

#endif
