// Стек

#include<iostream>

using namespace std;

struct NodeQ {
	int nb;
	NodeQ* next;
};
NodeQ* pbeg1, * pbeg2;

// Добавление
void push(NodeQ** ppbeg, int n) {
	NodeQ* pv = new NodeQ;
	pv->nb = n;
	if (!*ppbeg) {
		pv->next = 0;
		*ppbeg = pv;
	}
	else {
		pv->next = *ppbeg;
		*ppbeg = pv;
	}
}

// Удаление
int pop(NodeQ** ppbeg) {
	NodeQ* pv = *ppbeg;
	int a = pv->nb;
	*ppbeg = pv->next;
	delete pv;
	return a;
}

// Вывод
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
	NodeQ* pbeg1 = 0, * pbeg2 = 0;
	int k, n, w;
	while (1) {
		cout << "\nЗадайте вариант действия : \n 1 - добавить\n 2 - удаление\n 3 - печать\n другое число - удаление\n";
		cin >> k;
		switch (k) {
		case 1: cout << "Введите номер трамвая: "; cin >> n; push(&pbeg1, n); break;
		case 2: {
			cout << "Введите номер трамвая для удаления: ";
			cin >> n;
			while (1) {
				if (!pbeg1) {
					cout << "Вагона нет!\n";
					break;
				}
				w = pop(&pbeg1);
				if (w == n) break;
				push(&pbeg2, w);
			}
			while (pbeg2) {
				push(&pbeg1, pop(&pbeg2));
			}
			break;
		}
		case 3: print(pbeg1); break;
		default: return 0;
		}
	}
}