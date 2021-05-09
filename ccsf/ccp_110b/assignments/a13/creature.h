#include <string>
#include <iostream>
using namespace std;

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

    class Human: public Creature {
        public:
            Human();
            Human(int strengh, int hitpoints);
            string getSpecies() const;
    };

    class Elf: public Creature {
        public:
            Elf();
            Elf(int strengh, int hitpoints);
            string getSpecies() const;
            int getDamage() const;
    };

    class Demon: public Creature {
        public:
            Demon();
            Demon(int strengh, int hitpoints);
            virtual string getSpecies() const = 0;
            virtual int getDamage() const;
    };

    class Balrog: public Demon {
        public:
            Balrog();
            Balrog(int strengh, int hitpoints);
            string getSpecies() const;
            int getDamage() const;
    };

    class Cyberdemon: public Demon {
        public:
            Cyberdemon();
            Cyberdemon(int strengh, int hitpoints);
            string getSpecies() const;
    };

}
