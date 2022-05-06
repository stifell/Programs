#include<iostream>
#include<fstream>

using namespace std;

struct trm {
	char fio[16];
	int nb, nm;
	trm* prev;
	trm* next;
};
trm* pbeg=0, *pend=0;

void add(trm** ppbeg, trm** ppend, const trm& t) {
	trm* pv = new trm;
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

void readDBT(trm** ppbeg, trm** ppend) {
	ifstream fin("data.txt");
	trm* pbeg = 0;
	trm* pend = pbeg;
	trm t;
	for (int i = 1; i <= 10; i++)
	{
		fin >> t.nb >> t.nm >> t.fio;
		add(ppbeg, ppend, t);
	}
}

void printDBT(trm* pbeg) {
	trm* pv = pbeg;
	while (pv) {
		cout << "\nНомер маршрута: " << pv->nm << "\nБортовой номер: " << pv->nb << "\nФамилия водителя: " << pv->fio << 
			"\n-------------------";
		pv = pv->next;
	}
}

void marsh(int m) {
	bool a = false;
	trm* pv = pbeg;
	while (pv) {
		if (m == pv->nm) {
			cout << "\nНомер маршрута: " << pv->nm << "\nБортовой номер: " << pv->nb << "\nФамилия водителя: " << pv->fio << endl;
			a = true;
		}
		pv = pv->next;
	}
	if (a == false) {
		cout << "Такого маршрута нет!\n";
	}

}


int main()
{
	setlocale(LC_ALL, "Russian");
	int t;
	readDBT(&pbeg, &pend);
	printDBT(pbeg);
	cout << "\n\nНомер маршрута: "; cin >> t;
	marsh(t);

	return 0;
}