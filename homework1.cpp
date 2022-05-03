// Домашнее задание №1
// Матюшкин Денис Владимирович, НПИбд-02-21, №1032212279

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Tram {
	char fio[16];
	int bN, mN;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	ifstream file("data.txt");
	Tram w[10];
	int mN;
	bool a = false;
	cout << "Введите номер маршрута: ";
	cin >> mN;
	for (int i = 0; i < 10; i++)
	{
		file >> w[i].bN >> w[i].mN >> w[i].fio;
		if (mN == w[i].mN) {
			cout << "\nНомер маршрута: " << w[i].mN << "\nБортовой номер: " << w[i].bN << "\nФамилия водителя: " << w[i].fio << endl;
			a = true;
		}
	}
	if (a == false) {
		cout << "Такого маршрута нет!\n";
	}
	file.close();

	return 0;
}