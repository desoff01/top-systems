#include <iostream>
#include <memory>
#include <cmath>

// Абстрактный класс, является базовым для всех остальных классов
class Shape {
    protected:
    char symbol {'#'};
    bool full {true};
    public:
    virtual void print() const = 0;
    void setSymbol(char _symbol) {
        symbol = _symbol;
    }
    void setFull(bool _full) {
        full = _full;
    }
    bool getFull() const {
        return full;
    }

    virtual ~Shape() = default;
};

class Rectangle : public Shape {
    protected:
    size_t width, height;
    Rectangle() = default;
    public:
    Rectangle(size_t _width, size_t _height) : width(_width), height(_height) {}

    size_t getWidth() const {
        return width;
    }
    size_t getHeight() const {
        return height;
    }
    void print() const override {
        if (full) { // вывод заполненного прямоугольника
            for (size_t i {}; i < height; ++i) {
                std::string s(width, symbol);
                std::cout << s << '\n';
            }
        } else if (height > 1) { // вывод пустого прямоугольника
            std::string edge(width, symbol);
            std::cout << edge << '\n';
            if (width > 1) {
                for (size_t i {}; i < height-2; ++i) {
                    std::string s(width-2, ' ');
                    std::cout << symbol << s << symbol << '\n';
                }
            } else {
                for (size_t i {}; i < height-2; ++i) {
                    std::cout << symbol << '\n';
                }
            }
            std::cout << edge << '\n';
        } else { // вывод пустого прямоугольника, где height = 1
            if (width > 1) {
                std::string s(width-2, ' ');
                std::cout << symbol << s << symbol << '\n';
            } else {
                std::cout << symbol << '\n';
            }
        }
    }

};

class Square : public Rectangle {
    public:
    Square(size_t edge) {
        height = edge;
        width = edge;
    }
};

class Ellipse : public Shape {
    protected:
    double radiusX, radiusY;

    // Находится ли точка на поверхности эллипса
    bool isOnEllipse(double x, double y) const { 
        double tmp {std::pow(x, 2) / std::pow(radiusX-.1, 2) + std::pow(y, 2) / std::pow(radiusY-.1, 2)};
        return tmp >= .6 && tmp <= 1.0;
    }

    // Находится ли точка внутри эллипса
    bool isInsideEllipse(double x, double y) const { 
         return std::pow(x, 2) / std::pow(radiusX-.1, 2) + std::pow(y, 2) / std::pow(radiusY-.1, 2) < .6;
    }
    Ellipse() = default;
    public:
    Ellipse(double radX, double radY) {
        if (radX < 0) radiusX = 0;
        else radiusX = radX;
        
        if (radY < 0) radiusX = 0;
        else radiusY = radY;
    }
    void print() const override {
        for (double y {radiusY}; y >= -radiusY; --y) {
            for (double x {-radiusX}; x < radiusX; x += .5) {
                if (isOnEllipse(x, y)) std::cout << symbol;
                else if (isInsideEllipse(x, y) && full) std::cout << symbol;
                else std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }
    double getRadiusX() const {
        return radiusX;
    }
    double getRadiusY() const {
        return radiusY;
    }
};

class Circle : public Ellipse {
    public:
    Circle(double radius) {
        if (radius < 0) {
            radiusX = 0;
            radiusY = 0;
        }
        radiusX = radius;
        radiusY = radius;
    }
};

class Triangle : public Shape {
    size_t height, width;
    public:
    Triangle(size_t _height) : height(_height) {
        width = height * 2;
    }
    void print() const override {
        // Указатели на левую и правую стороны треугольника
        size_t l {width/2-1}, r {width/2};
        // Количество символов, которое необходимо вывести внутри треугольника
        size_t ins {};
        for (size_t i {}; i < height-1; ++i) {
            // строки для заполнения пустого пространства
            std::string l_str(l, ' ');
            std::string r_str(width-r, ' ');
            std::cout << l_str << symbol;

            // Проверка на то, каким должен быть треугольник - заполненным или пустым
            if (full) {
                std::string inside(ins, symbol);
                std::cout << inside;
            } else {
                std::string inside(ins, ' ');
                std::cout << inside;
            }
            
            std::cout << symbol << r_str << '\n';
            --l;
            ++r;
            ins += 2;
        }
        // Вывод основания треугольника
        std::string base(width, symbol);
        std::cout << base << std::endl;
    }
};

int main() {
    std::unique_ptr<Shape> circle {std::make_unique<Circle>(6)};
    circle->setFull(false);
    circle->print();

    std::unique_ptr<Shape> rect {std::make_unique<Rectangle>(10, 4)};
    rect->setSymbol('5');
    rect->print();

    std::unique_ptr<Shape> ellipse {std::make_unique<Ellipse>(9, 19)};
    ellipse->setSymbol('?');
    ellipse->print();

    std::unique_ptr<Shape> square {std::make_unique<Square>(8)};
    square->setFull(false);
    square->setSymbol('\\');
    square->print();

    std::unique_ptr<Shape> triangle {std::make_unique<Triangle>(7)};
    triangle->print();
    std::cout << '\n';
    triangle->setFull(false);
    triangle->setSymbol('%');
    triangle->print();
    return 0;
}