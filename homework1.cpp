// �������� ������� �1
// �������� ����� ������������, �����-02-21, �1032212279

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
	cout << "������� ����� ��������: ";
	cin >> mN;
	for (int i = 0; i < 10; i++)
	{
		file >> w[i].bN >> w[i].mN >> w[i].fio;
		if (mN == w[i].mN) {
			cout << "\n����� ��������: " << w[i].mN << "\n�������� �����: " << w[i].bN << "\n������� ��������: " << w[i].fio << endl;
			a = true;
		}
	}
	if (a == false) {
		cout << "������ �������� ���!\n";
	}
	file.close();

	return 0;
}