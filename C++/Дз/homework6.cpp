#include<iostream>
using namespace std;

class Vector {
    int N;
    double* mas;
public:
    Vector(int); // определение приватных полей
    Vector(int, double*); // размер и указатель на массив координат
    Vector(const Vector&); // копирующий
    ~Vector(); // удаление памяти
    Vector& operator=(const Vector&); // перезгрузка операции присваивания
    Vector operator+(const Vector&); // перезгрузка оператора +
    Vector operator-(const Vector&);
    Vector operator-();
    Vector operator*(double);
    double operator*(const Vector&);
    friend Vector operator*(double, Vector&);
    void PrintV(); // печать
};

Vector::Vector(int m) {
    N = m;
    mas = new double[N];
    for (int i = 0; i < N; i++) mas[i] = 0;
}
Vector::Vector(int m, double* u) {
    N = m;
    mas = new double[N];
    for (int i = 0; i < N; i++) mas[i] = u[i];
}
Vector::Vector(const Vector& z) {
    N = z.N;
    mas = new double[N];
    for (int i = 0; i < N; i++) mas[i] = z.mas[i];
}
Vector::~Vector() {
    delete[] mas;
}
Vector& Vector::operator=(const Vector& t) {
    if (this == &t) return *this;
    // Если вектор присваивается самому себе -
    // ничего не меняется. Если это не так, то
    // старый вектор (стоящий в левой части)
    // перед присваиванием должен быть удалён
    N = t.N;
    delete[] mas;
    mas = new double[N];
    for (int i = 0; i < N; i++) mas[i] = t.mas[i];
    return *this;
}
Vector Vector::operator+(const Vector& t) {
    if (N != t.N) {
        cout << "разные размеры векторов\n";
        return Vector(0);
    }
    double* MAS = new double[N];
    for (int i = 0; i < N; i++)
        MAS[i] = mas[i] + t.mas[i];
    return Vector(N, MAS);
}

Vector Vector::operator-(const Vector& t) {
    if (N != t.N) {
        cout << "разные размеры векторов\n";
        return Vector(0);
    }
    double* MAS = new double[N];
    for (int i = 0; i < N; i++)
        MAS[i] = mas[i] - t.mas[i];
    return Vector(N, MAS);
}

Vector Vector::operator-() {
    return *this * (-1);
}

Vector Vector::operator*(double a) {
    double* MAS = new double[N];
    for (int i = 0; i < N; i++){
        MAS[i] = mas[i] * a;
    }
    return Vector(N, MAS);
}

double Vector::operator*(const Vector& a) {
    if (N != a.N) {
        cout << "Разные размеры векторов\n";
        return 0;
    }
    double b = 0;
    for (int i = 0; i < N; i++)
        b += mas[i] * a.mas[i];
    return b;
}

Vector operator*(double a, Vector& t) {
    return t * a;
}

void Vector::PrintV() {
    cout << "{" << mas[0];
    for (int i = 1; i < N; i++)
    {
        cout << ", " << mas[i];
    }
    cout << "}" << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    double ma[3] = { 1,2,3 };
    Vector a(3, ma);
    double mb[3] = { 4,5,9 };
    Vector b(3, mb);
    Vector b2(b);
    Vector c(4);
    cout << "Вектор a = "; a.PrintV();
    cout << "Вектор b = "; b.PrintV();
    cout << "Вектор b2 = "; b2.PrintV();
    cout << "Вектор c = "; c.PrintV();
    c = a; cout << "обновлённый c = "; c.PrintV();
    Vector z = a + b; cout << "a + b = "; z.PrintV();
    Vector x = b - a; cout << "b - a = "; x.PrintV();
    b2 = -b2; cout << "Противоположный вектор b2: "; b2.PrintV();
    Vector v = a * 2; cout << "Умножение вектора на число: a * 2 = "; v.PrintV();
    Vector q = 2 * b; cout << "Умножение число на вектор: 2 * b = "; q.PrintV();
    double p = a * b; cout << "Скалярное произведение: a и b = " << p;
    return 0;
}
