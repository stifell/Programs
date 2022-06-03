#include<iostream>
#include<math.h>

using namespace std;
const double pi = 3.1415926;

class point {
protected:
    double x, y;
public:
    point(double x1, double y1)
    {
        x = x1; y = y1; aa
    }
    double getx() { return x; }
    double gety() { return y; }
    void show() {
        cout << "Координаты: (" << x << ", " << y << ")\n";
    }
    double distto(point b) {
        return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
    }
    void move(double dx, double dy) {
        x += dx; y += dy;
    }
    void moveto(double a, double b) {
        x = a; y = b;
    }
};


class circle : public point {
protected:
    double rad;
public:
    circle(double x1, double y1, double r1) : point(x1, y1) {
        if (r1 > 0) rad = r1;
        else rad = 0;
    }
    void show() {
        cout << "Центр: (" << x << ", " << y << ")" << endl;
        cout << "Радиус: " << rad << endl;
    }
    void move(double dx, double dy) {
        x += dx; y += dy;
    }
    void moveto(double a, double b) {
        x = a; y = b;
    }
    void vary(double t) {
        if (t > 0) rad *= t;
        else rad = 0;
    }
    double length() {
        return pi * 2 * rad;;
    }
    double square() {
        return pi * rad * rad;
    }
};


int main() {
    setlocale(LC_ALL, "ru");

    // Координаты
    point a(5, 9); a.show();
    point b(10, 2);
    a.moveto(2, 7); a.show();
    a.move(1, 1); a.show();
    cout << "Расстояние: " << a.distto(b) << endl << endl;

    // Окружность
    circle c(5, 6, 7); c.show();
    c.moveto(1, 2); c.show();
    c.move(10, 10); c.show();
    cout << "Длина = " << c.length() << endl;
    cout << "Площадь = " << c.square() << endl;
    c.vary(2);
    cout << "\nНовый радиус: \n"; c.show();
    cout << "Длина = " << c.length() << endl;
    cout << "Площадь = " << c.square() << endl;
    return 0;
}
