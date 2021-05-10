#include <string>
#include <iostream>
#include "creature.h"
using namespace std;

#ifndef HUMAN_H
#define HUMAN_H

namespace cs_creature {

    class Human: public Creature {
        public:
            Human();
            Human(int strengh, int hitpoints);
            string getSpecies() const;
    };
}

#endif
