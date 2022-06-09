#include<iostream>

using namespace std;

class point
{
protected:
    double x, y;
public:
    point() {}
    point(double valueX, double valueY)
    {
        x = valueX; y = valueY;
    }
    double getx() { return x; }
    double gety() { return y; }
    void show() {
        cout << "координаты: (" << x << ", " << y << ")\n";
    }
    void move(double dx, double dy) {
        x += dx; y += dy;
    }
    void moveto(double a, double b) {
        x = a; y = b;
    }
};

class line
{
protected:
    point X, Y;
public:
    line() {}
    line(point a, point b) {
        X = a; Y = b;
    }
    void move(double dx, double dy) {
        X.move(dx, dy); Y.move(dx, dy);
    }
    void moveto_p1(double a, double b) {
        X.moveto(a, b);
    }
    void moveto_p2(double a, double b) {
        Y.moveto(a, b);
    }
    void show() {
        cout << "Прорисовка линии: \n";
        cout << "Точка x "; X.show();
        cout << "Точка y "; Y.show(); cout << "\n";
    }
};

class triangle
{
protected:
    point A, B, C;
public:
    triangle() {}
    triangle(point a, point b, point c) {
        A = a, B = b, C = c;
    }
    void move(double dx, double dy) {
        A.move(dx, dy); B.move(dx, dy); C.move(dx, dy);
    }
    void moveto_p1(double a, double b) {
        A.moveto(a, b);
    }
    void moveto_p2(double a, double b) {
        B.moveto(a, b);
    }
    void moveto_p3(double a, double b) {
        C.moveto(a, b);
    }
    void show() {
        cout << "Прорисовка треугольника: \n";
        cout << "Вершина A "; A.show();
        cout << "Вершина B "; B.show();
        cout << "Вершина C "; C.show(); cout << "\n";
    }
};

class circle : public point
{
protected:
    double rad;
public:
    circle() {}
    circle(double valueX, double valueY, double valueR) : point(valueX, valueY) {
        if (valueR > 0) rad = valueR;
        else rad = 0;
    }
    void show() {
        cout << "Прорисовка окружности: \n";
        cout << "Центр: (" << x << ", " << y << ")" << endl;
        cout << "Радиус: " << rad << "\n";
    }
    void move(double dx, double dy) {
        x += dx; y += dy;
    }
    void moveto(double a, double b) {
        x = a; y = b;
    }
};

class figure
{
protected:
    point arr[6];
public:
    figure() {}
    figure(point a, point b, point c, point d, point e, point f) {
        arr[0] = a; arr[1] = b; arr[2] = c; arr[3] = d; arr[4] = e; arr[5] = f;
    }
    void show() {
        cout << "\nПрорисовка фигуры:\n";
        for (int i = 0; i < 6; i++)
        {
            cout << "Точка №" << i + 1 << " "; arr[i].show();
        }
    }
};

class picture
{
protected:
    line W; triangle E; circle Q; figure T;
public:
    picture(line a, triangle b, circle c, figure d) {
        W = a; E = b; Q = c; T = d;
    }

    void show() {
        cout << "\n---------------------------\n" <<
            "Рисуем картину...\n\n";
        W.show(); E.show(); Q.show(); T.show();
    }
};


int main() {
    setlocale(LC_ALL, "ru");

    // Точка
    cout << "Зададим точки в пространстве: \n";
    point a(5, 9); cout << "Точка №1 "; a.show();
    point b(10, 2); cout << "Точка №2 "; b.show();
    point c(9, 5); cout << "Точка №3 "; c.show();
    point d(164, 25); cout << "Точка №4 "; d.show();
    point e(53, 12); cout << "Точка №5 "; e.show();
    point f(500, 900); cout << "Точка №6 "; f.show();
    cout << endl;

    // Линия
    line l(a, b); l.show();

    // Треугольник
    triangle tr(a, d, f); tr.show();

    // Окружность
    circle oc(342, 123, 67); oc.show();

    // Фигура
    figure fi(a, b, c, d, e, f); fi.show();

    // Рисунок
    picture p(l, tr, oc, fi); p.show();
    return 0;
}