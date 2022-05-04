// Домашнее задание №2
// Матюшкин Денис Владимирович НПИбд-02-21 №1032212279
#include<iostream>

using namespace std;

struct Node1 {
	int d;
	Node1* next;
};

// Функция добавления пустого узла, так и не пустого
Node1* add(Node1** ppbeg, int dd) {
	Node1* pv = new Node1;
	pv->d = dd;
	pv->next = 0;
	if (*ppbeg)
	{
		// Используем "скользящий" узел для добавления не пустого списка
		Node1* temp = *ppbeg;
		while (temp->next) temp = temp->next;
		temp->next = pv;
	}
	else *ppbeg = pv;
	return *ppbeg;
}

// Функция для вычисления суммы списка
int sum(Node1* pbeg) {
	int s = 0;
	Node1* pv = pbeg;
	while (pv)
	{
		s += pv->d;
		pv = pv->next;
	}
	return s;
}

// Функция для подсчета кол-во экземпляров введенного числа
int find(Node1* pbeg, int key) {
	int f = 0;
	Node1* pv = pbeg;
	while (pv)
	{
		if (pv->d == key) f += 1;
		pv = pv->next;
	}
	return f;
}

// Функция для добавления нового узла в начало списка
Node1* first(Node1* pbeg, int key) {
	Node1* pv = new Node1;
	pv->d = key;
	pv->next = pbeg;
	pbeg = pv;

	return pv;
}

int main() {
	setlocale(LC_ALL, "Russian");
	Node1* pbeg = 0;
	int size;
	cout << "Задайте числа:\n";
	while (1)
	{
		cin >> size;
		if (size == 0) break;
		pbeg = add(&pbeg, size);
	}
	cout << "Сумма: " << sum(pbeg);
	cout << "\n\nВведите цисло для поиска: ";
	cin >> size;

	cout << "Кол-во экземпляров числа в списке: " << find(pbeg, size);

	cout << "\n\nВведите ключ нового узла: ";
	cin >> size;
	Node1* pv = first(pbeg, size);
	while (pv) {
		cout << pv->d << " ";
		pv = pv->next;
	}
	cout << endl;

	return 0;
}

