#include "Player.h"

int main() {
    int x {10};
    int &&r {20};
    r = std::move(x);
    std::cout << x << " " << r << std::endl;
    std::cout << &x << " " << &r << std::endl;
    Player* keith = new Player();
    (*keith).name = "Keith";
    (*keith).talk("yo");
    keith->do_damage(10);

    Player villain = Player("Qamudo");
    villain.talk("I will destroy you!");

    std::cout << "There are " << keith->get_num_players() << " players" << std::endl;

//    Player* hero = new Player("hero", 400, 250);

//    hero->do_damage(12);

    {
        Player schmope {"schmope", 5, 1};
        Player dope = schmope;
        std::cout << schmope.get_health() << std::endl;
        std::cout << "There are " << keith->get_num_players() << " players" << std::endl;
        schmope.do_damage(7);
        std::cout << dope.get_health() << std::endl;
        std::cout << dope.get_health() << std::endl;
    }

    std::cout << "There are " << keith->get_num_players() << " players" << std::endl;
}
