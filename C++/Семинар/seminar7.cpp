#include <iostream>

using namespace std;

class Time
{
    int h, m;

public:
    Time()
    {
        h = 0; m = 0;

    }
    Time(int hours, int minutes)
    {
        int A = hours * 60 + minutes;
        h = (A / 60) % 24;
        m = A % 60;
    }

    Time operator+(const Time& other) {
        int a = h + other.h;
        int b = m + other.m;
        return Time(a, b);
    }

    Time operator+(int value) {
        int a = h + value / 60;
        int b = m + value % 60;
        return Time(a, b);
    }

    bool operator==(const Time& other) {
        return h == other.h && m == other.m;
    }

    bool operator!=(const Time& other) {
        return h != other.h || m != other.m;
    }

    void ShowTime()
    {
        cout << h << ":" << m << endl;
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");

    Time a(22, 70);
    Time b(60, 70);
    Time c = a + b;
    cout << "Время a: ";
    a.ShowTime();
    cout << "Время b: ";
    b.ShowTime();
    cout << "a + b: ";
    c.ShowTime();
    Time m = a + 70;
    cout << "a + int: ";
    m.ShowTime();
    if (a == b) {
        cout << "a == b" << endl;
    }
    if (a != b) {
        cout << "a != b" << endl;
    }
    return 0;
}