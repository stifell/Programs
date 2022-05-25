#define _CRT_SECURE_NO_WARNINGS

//Домашнее задание №4
//Матюшкин Денис Владимирович 1032212279 НПИбд-02-21

#include<iostream>
#include<fstream>

using namespace std;

class Trm {
    int nb, nm;
    char fio[21];
public:
    Trm()
    {
        nb = 0; nm = 0; strcpy(fio, " ");
    }

    Trm(int b, int m, char* f)
    {
        nb = b; nm = m; strcpy(fio, f);
    }
    int Get_nm() { return nm; }
    void PrintBF();
};

void Trm::PrintBF() {
    cout << "Бортовой номер: " << nb << "\nМаршрутный номер: " << nm << "\nФио: " << fio << "\n\n";
}

int main() {
    setlocale(LC_ALL, "ru");
    const int N = 15;
    int b, m, i;
    char** f = new char* [N];
    for (int i = 0; i < N; i++) f[i] = new char[21];
    ifstream fin("data.txt");
    Trm t[N];
    for (i = 0; i < N; i++) {
        fin >> b >> m >> f[i];
        Trm T(b, m, f[i]);
        t[i] = T;
    }
    cout << "Задайте номер маршрута : ";
    cin >> m;
    bool a = true;
    for (i = 0; i < N; i++) {
        if (t[i].Get_nm() == m) {
            t[i].PrintBF();
            a = false;
        }
    }
    if (a) cout << "Такого маршрута нет!\n";
    return 0;
}
