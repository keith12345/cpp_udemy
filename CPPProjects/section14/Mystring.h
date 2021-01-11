#include <ostream>
#include <istream>

class Mystring {
    private:
        char* str;

    public:
        Mystring();
        Mystring(const char* s);
        Mystring(const Mystring& source);
        ~Mystring();
        void display() const;
        int get_length() const;
        const char* get_str() const;
        Mystring& operator=(const Mystring& source);
        Mystring& operator=(Mystring&& source);
        //Mystring operator-();
        //bool operator==(const Mystring& source);
        //Mystring operator+(const Mystring& source) const;
        friend Mystring operator-(const Mystring& obj);
        friend bool operator==(const Mystring& obj1, const Mystring& obj2);
        friend Mystring operator+(const Mystring& obj1, const Mystring& obj2);
        friend std::ostream& operator<<(std::ostream& os, const Mystring& obj);
        friend std::istream& operator>>(std::istream& is, Mystring& obj);
};
