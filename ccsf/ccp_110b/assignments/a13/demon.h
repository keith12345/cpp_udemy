#include <string>
#include <iostream>
#include "creature.h"
using namespace std;

#ifndef DEMON_H
#define DEMON_H

namespace cs_creature {

    class Demon: public Creature {
        public:
            Demon();
            Demon(int strengh, int hitpoints);
            virtual string getSpecies() const = 0;
            virtual int getDamage() const;
    };

}

#endif
