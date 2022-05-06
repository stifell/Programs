#include<iostream>
#include<fstream>

using namespace std;

struct Worker {
	char name[16];
	int yob, sal;
	Worker* next;
};

Worker readW() {
	Worker w;
	cout << "Фаимилия:\n"; cin >> w.name;
	cout << "Год рождения:\n"; cin >> w.yob;
	cout << "Оклад:\n"; cin >> w.sal;
	return w;
}

Worker* add(Worker** ppbeg, const Worker& w) {
	Worker* pv = new Worker;
	*pv = w;
	pv->next = 0;
	if (*ppbeg) {
		Worker* temp = *ppbeg;
		while (temp->next) temp = temp->next; temp->next = pv;
	}
	else *ppbeg = pv;
	return *ppbeg;
}

Worker* readDB() {
	ifstream fin("data.txt");
	Worker* pbeg = 0;
	Worker w;
	for (int i = 1; i <= 10; i++)
	{
		fin >> w.name >> w.yob >> w.sal;
		pbeg = add(&pbeg, w);
	}
	return pbeg;
}

void que(Worker* pbeg, int y) {
	bool a = true;
	Worker* pv = pbeg;
	while (pv){
		if (pv->yob > y) {
			cout << "Фамилия: " << pv->name << "; " << "год рождения: " << pv->yob << "; " << "оклад: " << pv->sal << endl;
			a = false;
		}
		pv = pv->next;
	}
	if (a == true) {
		cout << "Такого работника нет!\n";}
}

void printDB(Worker* pbeg) {
	Worker* pv = pbeg;
	while (pv) {
		cout << "Фамилия: " << pv->name << "; " << "год рождения: " << pv->yob << "; " << "оклад: " << pv->sal << endl;
		pv = pv->next;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	Worker* pbeg = readDB();
	int k;
	while (1) {
		do {
			cout << "\nВариант действия:\n" <<
				"1 - добавить\n" << "2 - запрос\n" <<
				"3 - печать\n" << "4 - выход\n" <<
				"---------------------------------\n";
			cin >> k;
		} while ((k < 1) || (k > 4));
		switch (k) {
		case 1: add(&pbeg, readW()); break;
		case 2: int y; cout << "Задайте год: "; cin >> y; que(pbeg, y); break;
		case 3: printDB(pbeg); break;
		case 4: return 0;
		}
	}

	return 0;
}