#include <string>
#include <iostream>
#include "demon.h"
using namespace std;

#ifndef BALROG_H
#define BALROG_H

namespace cs_creature {

    class Balrog: public Demon {
        public:
            Balrog();
            Balrog(int strengh, int hitpoints);
            string getSpecies() const;
            int getDamage() const;
    };

}

#endif
