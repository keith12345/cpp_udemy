#include <iostream>
#include <vector>

class Shape {
    private:
    public:
       virtual void draw() const = 0;
       virtual void rotate() const = 0;
       //virtual void flip() const = 0;
       virtual ~Shape() {};
};

class Rectangle: public Shape {
    public:
        virtual void draw() const override {
            std::cout << "------\n|    |\n------" << std::endl;
        }
        virtual void rotate() const override {
            std::cout << " -\n| |\n| |\n| |\n| |\n -" << std::endl;
        }
        virtual ~Rectangle() {};
};


class Square: public Shape {
    public:
        virtual void draw() const override {
            std::cout << " ----\n|    |\n|    |\n ----" << std::endl;
        }
        virtual void rotate() const override {
            std::cout << " ----\n|    |\n|    |\n ----" << std::endl;
        }
        virtual ~Square() {};
};

int main() {
    // Shape s; // cannot declare variable 's' to be of abstract type 'Shape'
    Shape* rect = new Rectangle();
    rect->draw();
    rect->rotate();

    Shape* sqr = new Square();

    std::vector<Shape*> shapes {rect, sqr};

    for (const Shape* s: shapes) {
        std::cout << "Printing Shape:" << std::endl;
        s->draw();
        std::cout << "Printing rotated Shape:" << std::endl;
        s->rotate();
    }

}
