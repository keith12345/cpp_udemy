#include <iostream>
using namespace std;

//----DO NOT MODIFY THE CODE ABOVE THIS LINE----
//----WRITE YOUR FUNCTION PROTOTYPE BELOW THIS LINE----

void print_grocery_list(int mangos = 13, int apples = 3, int oranges = 7);

//----WRITE YOUR FUNCTION PROTOTYPE ABOVE THIS LINE----
//----DO NOT MODIFY THE CODE BELOW THIS LINE----

void modify_grocery_list() {

    //----DO NOT MODIFY THE CODE ABOVE THIS LINE----
    //----WRITE YOUR FUNCTION CALLS BELOW THIS LINE----
    int apples {};
    int oranges {};
    print_grocery_list();
    print_grocery_list(apples = 5);
    print_grocery_list(apples=7, oranges=11);



    //----WRITE YOUR FUNCTION CALLS ABOVE THIS LINE----
    //----DO NOT MODIFY THE CODE BELOW THIS LINE----
}

void print_grocery_list(int mangos, int apples, int oranges) { //----WRITE THE FUNCTION PARAMETER LIST WITHIN THE PARENTHESES
                                     //----DO NOT MODIFY THE CODE BELOW THIS LINE----
    cout << apples << " apples" << "\n" << oranges << " oranges" << "\n" << mangos << " mangos" << "\n";
}
