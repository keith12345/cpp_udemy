#include "creature.h"
using namespace cs_creature;






void battleArena(Creature& c1, Creature& c2);
void printBattlePrompt(Creature& c1, Creature& c2);
void printHealth(Creature& c);
void printVictor(Creature& c1, Creature& c2);






int main()
{
	srand(static_cast<unsigned>(time(nullptr)));

	Elf e(50,50);
	Balrog b(50,50);

	battleArena(e, b);

	Human h(40,20);
	Cyberdemon c(30,50);

	battleArena(h, c);
}






void printBattlePrompt(Creature& c1, Creature& c2) {
	int len1 = c1.getSpecies().length();
	int len2 = c2.getSpecies().length();
	int padding = 36 - (len1 + len2);
	string rightPad = string(padding/2, ' ');
	string leftPad;
	if (padding % 2 == 1)
		leftPad = string(1+padding/2, ' ');
	else
		leftPad = rightPad;

	std::cout << "-------------------------------------------\n"
		      << "|          Get ready to Battle!!          |\n"
			  << "|" << leftPad << c1.getSpecies()
			  << " vs. "
			  << c2.getSpecies() << rightPad << "|\n"
			  << "|                                         |\n"
			  << "|                 \033[1;31mFIGHT!!!\033[0m                |\n"
			  << "|                                         |\n"
			  << "-------------------------------------------\n"
			  << std::endl;
}






void printHealth(Creature& c) {
	std::cout << "The "
			  << c.getSpecies()
			  << " has "
			  << c.getHitpoints()
			  << " hitpoints remaining!"
			  << std::endl;
}






void printVictor(Creature& c1, Creature& c2) {
	if (c1.getHitpoints() == c2.getHitpoints())
		std::cout << "It's a draw!" << std::endl;
	else if (c1.getHitpoints() > 0)
		std::cout << "The "
				  << c1.getSpecies()
				  << " wins!"
				  << std::endl;

	else
		std::cout << "The "
				  << c2.getSpecies()
				  << " wins!"
				  << std::endl;
	std::cout << std::endl;
}






void battleArena(Creature& c1, Creature& c2) {
	printBattlePrompt(c1, c2);
	int roundNumber = 1;
    while (c1.getHitpoints() > 0 && c2.getHitpoints() > 0) {
		c1.updateHitpoints(std::max(c1.getHitpoints() - c2.getDamage(), 0));
		c2.updateHitpoints(std::max(c2.getHitpoints() - c1.getDamage(), 0));
		printHealth(c1);
		printHealth(c2);
		std::cout << "\n\tRound number "
				  << roundNumber
				  << " complete!\n"
				  << std::endl;
		++roundNumber;
	}
	printVictor(c1, c2);
}
