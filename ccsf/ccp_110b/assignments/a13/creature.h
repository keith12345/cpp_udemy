#include <string>
#include <iostream>
using namespace std;

#ifndef CREATURE_H
#define CREATURE_H

namespace cs_creature {

    class Creature {
        private:
            int strength;
            int hitpoints;
        public:
            Creature();
            Creature(int newStrength, int newHitpoints);

            virtual string getSpecies() const = 0;
            virtual int getDamage() const;

            int getStrength() const;
            int getHitpoints() const;
            bool updateStrengh(int strengh);
            bool updateHitpoints(int hitpoints);
    };
}

#endif
