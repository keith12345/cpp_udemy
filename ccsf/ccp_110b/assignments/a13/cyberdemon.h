#include <string>
#include <iostream>
#include "demon.h"
using namespace std;

#ifndef CYBERDEMON_H
#define CYBERDEMON_H

namespace cs_creature {

    class Cyberdemon: public Demon {
        public:
            Cyberdemon();
            Cyberdemon(int strengh, int hitpoints);
            string getSpecies() const;
    };

}

#endif
