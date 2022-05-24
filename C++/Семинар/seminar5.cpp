#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>
using namespace std;

class trm {
    // приватные поля:
    int nb, nm;
    char fio[21];
public:   // публичные поля:
    // конструктор по умолчанию -
    // трамвай "нулевой" или без водителя:
    trm(int b = 0, int m = 0)
    {
        nb = b; nm = m; strcpy(fio, "");
    }
    // другой конструктор:
    trm(int b, int m, char* f)
    {
        nb = b; nm = m; strcpy(fio, f);
    }
    int get_nb(); // возвращение борт. номера
    int get_nm(); // возвращение марш. номера
    char* get_fio(); // возвращение fio
    void chgm(int m); // замена маршрута
};

// описания объявленных функций:
int trm::get_nb() { return nb; }
int trm::get_nm() { return nm; }
char* trm::get_fio() { return fio; }
void trm::chgm(int m) { nm = m; }

int main() {
    setlocale(LC_ALL, "Russian");
    char c[21];
    trm t1; //"пустой" трамвай (1-й конструктор)
    trm t2(1627, 47); //трамвай без водителя
                     //(1-й конструктор)
    cout << "фамилия водителя : "; cin >> c;
    trm t3(1274, 39, c); //2-й конструктор
    trm t4 = t3; //конструктор копирования
      //контрольный вывод всех четырёх трамваев:
    cout << "трамвай t1 : \n";
    cout << "борт.номер: " << t1.get_nb() <<
        " маршрут : " << t1.get_nm() <<
        " фио: " << t1.get_fio() << endl;
    cout << "трамвай t2 : \n";
    cout << "борт.номер: " << t2.get_nb() <<
        " маршрут : " << t2.get_nm() <<
        " фио: " << t2.get_fio() << endl;
    cout << "трамвай t3 : \n";
    cout << "борт.номер: " << t3.get_nb() <<
        " маршрут : " << t3.get_nm() <<
        " фио: " << t3.get_fio() << endl;
    cout << "трамвай t4 : \n";
    cout << "борт.номер: " << t4.get_nb() <<
        " маршрут : " << t4.get_nm() <<
        " фио: " << t4.get_fio() << endl;
    //замена маршрута трамвая t4:
    int m1;
    cout << "новый маршрут трамвая t4 : ";
    cin >> m1;
    t4.chgm(m1);
    //вывод обновлённого t4:
    cout << "t4 с новым маршрутом : \n";
    cout << "борт.номер: " << t4.get_nb() <<
        " маршрут : " << t4.get_nm() <<
        " фио: " << t4.get_fio() << endl;
    return 0;
}
