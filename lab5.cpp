/*Name: Wanposop Surayut Student ID:16800180*/

#include <iostream>
#include <cmath>

const double PI = 3.14159;

class Circle {
protected:
    double radius;

public:
    Circle(double r = 0.0) : radius(r) {}

    double getRadius() const {
        return radius;
    }

    double area() const {
        return PI * radius * radius;
    }

    friend std::ostream& operator<<(std::ostream& os, const Circle& c) {
        os << "Radius of circle: " << c.radius << " cm" << std::endl;
        os << "Area of circle: " << c.area() << " (cms)^2 " << std::endl;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Circle& c) {
        is >> c.radius;
        return is;
    }
};

class Sector : public Circle {
private:
    double angle;

public:
    Sector(double r = 0.0, double a = 0.0) : Circle(r), angle(a) {}

    double getAngle() const {
        return angle;
    }

    double area() const {
        return (0.5 * Circle::area() * angle) / PI;
    }

    friend std::ostream& operator<<(std::ostream& os, const Sector& s) {
        os << "Radius of sector: " << s.radius << " cm" << std::endl;
        os << "Angle of sector: " << s.angle << " radians" << std::endl;
        os << "Area of sector: " << s.area() << " (cms)^2 " << std::endl;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Sector& s) {
        is >> s.radius >> s.angle;
        return is;
    }
};

class Segment : public Circle {
private:
    double height;

public:
    Segment(double r = 0.0, double h = 0.0) : Circle(r), height(h) {}

    double getHeight() const {
        return height;
    }

    double area() const {
        double term1 = radius * radius * std::acos((radius - height) / radius);
        double term2 = (radius - height) * std::sqrt((2 * radius * height) - (height * height));
        return term1 - term2;
    }

    friend std::ostream& operator<<(std::ostream& os, const Segment& seg) {
        os << "Radius of segment: " << seg.radius << " cm" << std::endl;
        os << "Height of segment: " << seg.height << " cm" << std::endl;
        os << "Area of segemnt: " << seg.area() << " (cms)^2" << std::endl;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Segment& seg) {
        is >> seg.radius >> seg.height;
        return is;
    }
};

int main() {
    Circle circle;
    Sector sector;
    Segment segment;

    std::cout << "Enter radius of the circle in cm: ";
    std::cin >> circle;

    std::cout << "Enter radius and angle of the sector in cm and radians: ";
    std::cin >> sector;

    std::cout << "Enter radius and height of the segment in cm: ";
    std::cin >> segment;

    std::cout << std::endl << "Circle Details:" << std::endl;
    std::cout << circle << std::endl;

    std::cout << "Sector Details:" << std::endl;
    std::cout << sector << std::endl;

    std::cout << "Segment Details:" << std::endl;
    std::cout << segment << std::endl;

    return 0;
}


