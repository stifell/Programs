// Домашнее задание №3
// Матюшкин Денис Владимирович НПИбд-02-21 №1032212279

#include<iostream>
#include<fstream>

using namespace std;

struct Student {
    char fio[16], gr[16];
    int pr[5];
    Student* prev;
    Student* next;
};
Student* pbeg, * pend;

//Добавление нового узла в пустой/не пустой список
void add(Student** ppbeg, Student** ppend, const Student& t) {
    Student* pv = new Student;
    *pv = t;
    pv->next = 0;
    if (*ppbeg == 0 && *ppend == 0) {
        pv->prev = 0;
        *ppbeg = pv;
        *ppend = pv;
    }
    else {
        pv->prev = *ppend;
        (*ppend)->next = pv;
        *ppend = pv;
    }
}

//Чтение из файла
void read(Student** ppbeg, Student** ppend) {
    ifstream fin("data.txt");
    Student* pbeg = 0;
    Student s;
    for (int i = 1; i <= 10; i++)
    {
        fin >> s.fio >> s.gr;
        int j = 0;
        while (j != 5) {
            fin >> s.pr[j];
            j++;
        }
        add(ppbeg, ppend, s);
    }
}

//Вычисление сред. оценки
double compute(int* arr) {
    int size = 0;
    for (int i = 0; i < 5; i++)
    {
        size += arr[i];
    }
    return size / 5.0;
}

//Вывод данных из файла
void print(Student* pbeg) {
    Student* pv = pbeg;
    while (pv) {
        cout << "\nФИО: " << pv->fio << "\nГруппа: " << pv->gr << "\nСредняя оценка: " << compute(pv->pr) <<
            "\n-------------------";
        pv = pv->next;
    }
}

//Вывод нужных студентов
void cat(int m) {
    int i = 0;
    bool a = false;
    Student* pv = pbeg;
    while (pv) {
        if (m < compute(pv->pr)) {
            cout << "\nФИО: " << pv->fio << "\nГруппа: " << pv->gr << "\nСредняя оценка: " << compute(pv->pr) << endl;
            a = true;
        }
        pv = pv->next;
        i++;
    }
    if (a == false) {
        cout << "Таких студентов нет!\n";
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    int s;
    read(&pbeg, &pend);
    print(pbeg);
    cout << "\n\nСредний балл: "; cin >> s;
    cat(s);

    return 0;
}
