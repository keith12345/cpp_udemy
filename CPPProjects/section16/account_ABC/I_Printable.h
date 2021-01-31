#include <iostream>

class I_Printable {
    public:
        ~I_Printable() {
            std::cout << "Calling I_Printable Desctructor" << std::endl;
        }
        friend inline std::ostream& operator<<(std::ostream &os, const I_Printable& acc);
        virtual void print(std::ostream& os) const = 0;
};
