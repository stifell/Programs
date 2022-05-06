#include <iostream>

using namespace std;


struct Node2 {
	int d;
	Node2* next;
	Node2* prev;
};


// Добавление данных:
void add(Node2** ppbeg, Node2** ppend, int dd) {
	Node2 *pv = new Node2;
	// Заполнение полей:
	pv->d = dd;
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

// Поиск ключа:
Node2* find(Node2* const pbeg, int key) {
	Node2 *pv = pbeg;
	while (pv) {
		if (pv->d == key) break;
		pv = pv->next;
	}
	return pv;
}

// Удаление узла:
bool remove(Node2** ppbeg, Node2** ppend, int key) {
	if (Node2* pkey = find(*ppbeg, key)) {
		if (pkey == *ppbeg) {
			*ppbeg = (*ppbeg)->next;
			(*ppbeg)->prev = 0;
		}
		else if (pkey == *ppend) {
			*ppend = (*ppend)->prev;
			(*ppend)->next = 0;
		}
		else {
			(pkey->prev)->next = pkey->next;
			(pkey->next)->prev = pkey->prev;
		}
		delete pkey;
		return true;
	}
	return false;
}

// Добавление узла до/после/конец (insert):
Node2* insert(Node2* const pbeg, Node2** ppend, int key, int dd) {
	if (Node2* pkey = find(pbeg, key)) {
		Node2* pv = new Node2;
		pv->d = dd;
		pv->next = pkey->next;
		pv->prev = pkey;
		pkey->next = pv;
		if (pkey != *ppend) (pv->next)->prev = pv;
		else *ppend = pv;
		return pv;
	}
	return 0;
}


int main()
{
	Node2* pbeg = 0;
	Node2* pend = 0;
	for (int i = 1; i <= 5; i++)
	{
		add(&pbeg, &pend, i);}
	insert(pbeg, &pend, 2, 49);
	if (!remove(&pbeg, &pend, 4)) cout << "Узел не найден!" << endl;
	Node2* pv = pbeg;
	while (pv) {
		cout << pv->d << ' ';
		pv = pv->next;
	}
	return 0;
}