#include <iostream>
#include <string>
using namespace std;

int main() {
    string journal_entry_1 {"Isaac Newton"};
    string journal_entry_2 {"Leibniz"};

    journal_entry_1 = journal_entry_1.erase(0, 6);
    if (journal_entry_1 > journal_entry_2)
        journal_entry_1.swap(journal_entry_2);
    cout << journal_entry_1 << "\n" << journal_entry_2 << endl;
}
