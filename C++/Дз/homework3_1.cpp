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

double compute(double* x, int n) {
	int i = 0;
	Student* pv = pbeg;
	for (int i = 0; i < n; i++)
	{
		int size = 0;
		int j = 0;
		while (j != 5) {
			size += pv->pr[j];
			j++;
		}
		x[i] = size / 5.0;
		pv = pv->next;
	}
	return*x;
}

int print(Student* pbeg) {
	int f = 0;
	Student* pv = pbeg;
	while (pv) {
		cout << "\nФИО: " << pv->fio << "\nГруппа: " << pv->gr << "\nОценки: " << pv->pr[0] << ", " <<
			pv->pr[1] << ", " << pv->pr[2] << ", " << pv->pr[3] << ", " << pv->pr[4] << "\n-------------------";
		pv = pv->next;
		f++;
	}
	return f;
}

void cat(int m, double* x) {
	int i = 0;
	bool a = false;
	Student* pv = pbeg;
	while (pv) {
		if (m < x[i]) {
			cout << "\nФИО: " << pv->fio << "\nГруппа: " << pv->gr << "\nСредняя оценка: " << x[i] << endl;
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
	int n = print(pbeg);
	double* x = new double[n];
	*x = compute(x, n);
	cout << "\n\nСредний балл: "; cin >> s;
	cat(s, x);
	delete[] x;
	return 0;
}