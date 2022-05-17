// Очередь

#include<iostream>
#include<fstream>

using namespace std;

struct NodeQ {
	int nb;
	NodeQ* next;
};
NodeQ* pbeg;

// Добавление
void push(NodeQ** ppbeg, int n) {
	NodeQ* pv = new NodeQ;
	pv->nb = n;
	pv->next = 0;
	if (*ppbeg) {
		NodeQ* temp = *ppbeg;
		while (temp->next) temp = temp->next;
		temp->next = pv;
	}
	else *ppbeg = pv;
}

// Удаление
int pop(NodeQ** ppbeg) {
	NodeQ* pv = *ppbeg;
	if (*ppbeg == 0) {
		return -111;
	}
	else {
		int a = pv->nb;
		*ppbeg = pv->next;
		delete pv;
		return a;
	}
}

// Просмотр первого

int peek(NodeQ* pbeg) {
	NodeQ* pv = pbeg;
	if (pbeg == 0) {
		return -111;
	}
	else {
		return pv->nb;
	}
}

void print(NodeQ* pbeg) {
	bool a = false;
	NodeQ* pv = pbeg;
	while (pv) {
		cout << pv->nb << " ";
		pv = pv->next;
		a = true;
	}
	if (a == false) {
		cout << "Список пустой!\n";
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	NodeQ* pbeg = 0;
	int k, n;
	while (1) {
		cout << "\nЗадайте вариант действия : \n 1 - добавить\n 2 - просмотр первого\n 3 - удалить из очереди\n 4 - распечатка\n другое число - удаление\n";
		cin >> k;
		switch (k) {
		case 1: cout << "Введите номер трамвая: "; cin >> n; push(&pbeg, n); break;
		case 2: cout << peek(pbeg) << endl; break;
		case 3: cout << pop(&pbeg) << endl; break;
		case 4: print(pbeg); break;
		default: return 0;
		}
	}
}