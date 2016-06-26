#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <list>
#include <set>

using namespace std;
//Структура для хранения узла списка
template <typename T>
struct Node
{
	T info;
	Node* prev;
	Node* next;
	Node* down;
};
//Структура для хранения списка списков
template <typename T>
struct SLNode
{
	T info;
	SLNode* prev;
	SLNode* next;
};

//Функция добавления нового уровня в начало списка списков(списка с пропусками)
template <typename T>
void push_front(SLNode<Node<T>* >*&first, SLNode<Node<T>* >*&last, Node<T>* info)
{
	SLNode<Node<T>* >* tmp = new SLNode<Node<T>* >;
	tmp->info = info;
	tmp->prev = NULL;
	tmp->next = first;
	if (first)
		first->info.prev = tmp;
	first = tmp;
	if (!last)
		last = first;
}

//Функция добавления нового уровня в конец списка списков(списка с пропусками)
template <typename T>
void push_back(SLNode<Node<T>* >*&first, SLNode<Node<T>* >*&last, Node<T>* info)
{
	SLNode<Node<T>* >*tmp = new SLNode<Node<T>* >;
	tmp->info = info;
	tmp->prev = last;
	tmp->next = NULL;
	if (last)
		last->next = tmp;
	last = tmp;
	if (!first)
		first = last;
}

//Функция удаления уровня с начала списка списков(списка с пропусками)
template <typename T>
void pop_front(SLNode<Node<T>* >*&first, SLNode<Node<T>* >*&last)
{
	if (first)
	{
		SLNode<Node<T>* >*tmp = first;
		first = first->next;
		if (first)
			first->prev = NULL;
		if (!first)
			last = NULL;
		delete tmp;
	}
}
//Функция удаления уровня с конца списка списков(списка с пропусками)
template <typename T>
void pop_back(SLNode<Node<T>* >*&first, SLNode<Node<T>* >*&last)
{
	if (last)
	{
		SLNode<Node<T>* >*tmp = last;
		last = last->prev;
		if (last)
			last->next = NULL;
		if (!last)
			first = NULL;
		delete tmp;
	}
}
//Функция удаления узла списка из начала
template <typename T>
void pop_node(Node<T>*& node)
{
	if (node)
	{
		auto tmp = node;
		node = node->next;
		if (node)
			node->prev = NULL;
	}
}
//Функция удаления списка списков(списка с пропусками)
template <typename T>
void clear(SLNode<Node<T>* >*&first, SLNode<Node<T>* >*&last)
{
	while (first) 
	{	
		while (first->info)
			pop_node(first->info);

		pop_front(first, last);
	}
}

//Функция возвращающая случайное число в заданном диапазоне
double random(double min, double max)
{
	return (double)(rand()) / RAND_MAX*(max - min) + min;
}

//Функция генерирования случайного уровня, не выше указанного максимального уровня
int generatelvl(int maxlvl)
{
	int lvl = 1;
	while (random(0, 1) > 0.5&&lvl < maxlvl)
		lvl++;
	return lvl;
	//return 1;
}

//Функция поиска адреса элемента в списке. Результат - адрес элемента
Node<int>* findadress(SLNode<Node<int>* >* slback, int key)
{
	if (slback)
	{
		auto p = slback->info;
		if (p->down)
		{
			while (p->info>key&&slback)
			{
				slback = slback->prev;
				if(slback)
					p = slback->info;
			}
			if (p->info <= key)
			{
				while (p)
				{
					if (p->info == key)
						return p;
					else
						if (p->info < key)
						{
							if (p->next&&p->next->info <= key)
								p = p->next;
							else
									p = p->down;
						}
						else
							p = p->down;
				}
			}
		}
		else
		{
			while (p)
			{
				if (p->info == key)
					return p;
				else
					if (p->info < key)
						p = p->next;
					else
						return NULL;
			}
		}
		return p;
	}
	else
		return NULL;
}

//Функция проверки на существование элемента в списке. Результат - булевое значение
bool contains(SLNode<Node<int>* >* slback, int key)
{
	if (slback)
	{
		if (findadress(slback, key))
			return true;
		else
			return false;
	}
	else
		return false;
}

//Функция проверки на существование элемента в списке. Результат - вывод на экран 
void containsElement(SLNode<Node<int>* >* slback, int key)
{
	if (slback)
	{
		if (findadress(slback, key))
			cout << key << " is contains in the skiplist." << endl;
		else
			cout << key << " isn't found in the skiplist." << endl;
	}
	else
		cout << "Skiplist is empty" << endl;

}

//Функция вывода списка списков (списка с пропусками)
//внутренний цикл проходит по узлам списка
//внешний цикл - по уровням
void skip_list_show(SLNode<Node<int>* >* sl)
{
	if (sl)
	{
		for (auto q = sl; q; q=q->prev)
		{
			for (auto p = q->info;p;p = p->next)
				cout << p->info << ' ';
			cout << endl;
		}
	}
	else
		cout << "Skip list is empty!" << endl;
}

//Функция поиска нужного адреса для вставки элемента
Node<int>* findadresstoinsert(SLNode<Node<int>* >* slback, Node<int>** array, int maxlvl, int key)
{
	if (slback)
	{
		int i = 0;
		auto p = slback->info;
		if (p->down)
		{
			while (p->down)
			{
				if (p->info <= key)
				{
					if (p->info == key)
					{
						while (p->next&&p->next->info == key)
							p = p->next;
						array[i] = p;
						i++;
						p = p->down;
					}
					else
						if (p->next)
						{
							if (p->next->info > key)
							{
								array[i] = p;
								i++;
								p = p->down;
							}
							else
								p = p->next;
						}
						else
							if (!p->next&&key > p->info)
							{
								array[i] = p;
								i++;
								p = p->down;
							}
				}
				else
				{
					array[i] = p;
					i++;
					slback = slback->prev;
					if (slback)
					p = slback->info;
				}
			}
			if (!p->down)
			{
				while (p&&key < p->info)
				{
					if (p->prev == NULL&&key < p->info)
						return NULL;
					if (p->prev&&key < p->info&&key >= p->prev->info)
						return p->prev;
					else
						p = p->prev;
				}
				while (p&&key >= p->info)
				{
					if (p->next == NULL&&key >= p->info)
						return p;
					if (p->next&&key >= p->info&&key < p->next->info)
						return p;
					else
						p = p->next;
				}
			}
		}
		else
		{
			while (p&&key < p->info)
			{
				if (p->prev == NULL&&key < p->info)
					return NULL;
				if (p->prev&&key < p->info&&key >= p->prev->info)
					return p->prev;
				else
					p = p->prev;
			}
			while (p&&key >= p->info)
			{
				if (p->next == NULL&&key >= p->info)
					return p;
				if (p->next&&key >= p->info&&key < p->next->info)
					return p;
				else
					p = p->next;
			}
		}
	}
	else
		return NULL;
}

//Функция, добавляющая узел на уровни выше
void addup(SLNode<Node<int>*>*& first, SLNode<Node<int>*>*&last,Node<int>* down, int maxlvl, Node<int>** array)
{
	int currlvl = 1;
	int lvl = generatelvl(maxlvl);

	//cout << "lvl= " << lvl << ' ' << endl;
	if (lvl > 1)
	{
		auto tmpdown = down;
		int i = maxlvl - 2;
		while (!array[i])
			i--;

		while (currlvl < lvl)
		{
			Node<int>* tmp = new Node<int>;
			tmp->info = down->info;
			tmp->down = tmpdown;

			if (i >= 0 && array[i]->info <= tmp->info)
			{
				tmp->prev = array[i];
				tmp->next = array[i]->next;
				if (array[i]->next)
					array[i]->next->prev = tmp;
				array[i]->next = tmp;
				if (i >= 0)
					i--;
				currlvl++;
				tmpdown = tmp;

			}
			else if (i >= 0 && array[i]->info > tmp->info)
			{
				tmp->prev = array[i]->prev;
				tmp->next = array[i];
				if (array[i]->prev)
					array[i]->prev->next = tmp;
				array[i]->prev = tmp;
				auto sl = last;
				while (sl&&sl->info != array[i])
					sl = sl->prev;
				if (sl->info == array[i])
					sl->info = tmp;
				currlvl++;
				if (i >= 0)
					i--;
				tmpdown = tmp;
			}

			else
			{
				if (i < 0 && currlvl < maxlvl)
				{
					tmp->next = NULL;
					tmp->prev = NULL;
					push_back(first, last, tmp);
					currlvl++;
					tmpdown = tmp;
				}
			}
		}
	}
}

//Функция вставки узла в список списков (список с пропусками)
void insert(SLNode<Node<int>* >*& first, SLNode<Node<int>* >*& last, int maxlvl, int key)
{
	if (!first)
	{
		Node<int>* tmp = new Node<int>;
		tmp->info = key;
		tmp->down = NULL;
		tmp->prev = NULL;
		tmp->next = NULL;
		push_back(first, last, tmp);

		int currlvl = 1;
		int lvl = generatelvl(maxlvl);

		auto tmpdown = tmp;
		while (currlvl < lvl)
		{
			Node<int>* tmpup = new Node<int>;
			tmpup->info = key;
			tmpup->down = tmpdown;
			tmpup->prev = NULL;
			tmpup->next = NULL;
			push_back(first, last, tmpup);
			currlvl++;
			tmpdown = tmpup;
		}
	}
	else
	{
		Node<int>** array = new Node<int>*[maxlvl-1];
		for (int i = 0; i < maxlvl-1; i++)
			array[i] = NULL;
		Node<int>* p = findadresstoinsert( last, array, maxlvl, key);
		if (!p)
		{
			Node<int>* tmp = new Node<int>;
			tmp->info = key;
			tmp->down = NULL;
			tmp->prev = NULL;
			tmp->next = first->info;
			first->info->prev = tmp;
			first->info = tmp;
			addup( first,last, tmp, maxlvl, array);
		}
		else
		{
				Node<int>* tmp = new Node<int>;
				tmp->info = key;
				tmp->down = NULL;
				tmp->prev = p;
				tmp->next = p->next;
				if (p->next)
					p->next->prev = tmp;
				p->next = tmp;
				addup(first, last, tmp, maxlvl, array);
		}
		delete[] array;
	}
}
//Удаление узла из списка списков(списка с пропусками)
void remove(SLNode<Node<int>* >*& slfront, SLNode<Node<int>* >*& slback, int key)
{
	auto p = findadress(slback, key);
	while (p)
	{
		if (!p->prev&&!p->next)
		{
			auto tmp = p;
			p = p->down;
			delete tmp;
			pop_back(slfront, slback);
		}
		else
			if (!p->prev&&p->next)
			{
				auto tmp = p;
				auto sl = slback;
				while (sl&&sl->info != p)
					sl = sl->prev;
				if (sl&&sl->info == p)
					sl->info = p->next;
				p->next->prev = NULL;
				p = p->down;
				delete tmp;
			}
			else
				if (p->prev&&!p->next)
				{
					auto tmp = p;
					p->prev->next = NULL;
					p = p->down;
					delete tmp;
				}
				else
				{
					if (p->prev&&p->next)
					{
						auto tmp = p;
						p->prev->next = p->next;
						p->next->prev = p->prev;
						p = p->down;
						delete tmp;
					}
				}
	}
}
//Фукнция поиска адреса начального элемента из диапазона 
Node<int>* findadresstoshow(SLNode<Node<int>* >* slback, int key)
{
	if (slback)
	{
		auto p = slback->info;
		if (p->down)
		{
			while (p->down)
			{
				if (p->info <= key)
				{
					if (p->info == key)
					{
						while (p->prev&&p->prev->info == key)
							p = p->prev;
						p = p->down;
					}
					else
						if (p->next)
						{
							if (p->next->info > key)
								p = p->down;
							else
								p = p->next;
						}
						else
							if (!p->next&&key > p->info)
								p = p->down;
				}
				else
				{
					slback = slback->prev;
					if (slback)
					p = slback->info;
				}
			}
			if (!p->down)
			{
				while (p&&key < p->info)
				{
					if (p->prev == NULL&&key < p->info)
						return p;
					if (p->prev&&key <= p->info&&key > p->prev->info)
						return p;
					else
						p = p->prev;
				}
				while (p&&key >= p->info)
				{
					if (p->next == NULL&&key >= p->info)
						return p;
					if (p->next&&key > p->info&&key <= p->next->info)
						return p;
					else
						p = p->next;
				}
			}
		}
		else
		{
			while (p&&key < p->info)
			{
				if (p->prev == NULL&&key < p->info)
					return p;
				if (p->prev&&key <= p->info&&key > p->prev->info)
					return p;
				else
					p = p->prev;
			}
			while (p&&key >= p->info)
			{
				if (p->next == NULL&&key >= p->info)
					return p;
				if (p->next&&key > p->info&&key <= p->next->info)
					return p->next;
				else
					p = p->next;
			}
		}
	}
	else
		return NULL;
}
//функция вывода всех элементов в заданном диапазоне
void showrange(SLNode<Node<int>* >* slback)
{
	if (slback)
	{
		int r1, r2;
		cout << "Enter the start of range: ";
		cin >> r1;
		cout << "Enter the end of range: ";
		cin >> r2;
		auto p = findadresstoshow(slback, r1);
		if (p->info < r1)
			p = p->next;
		else
			if (p->prev&&p->prev->info>=r1)
				p = p->prev;
		while (p->prev&&p->prev->info == r1)
			p = p->prev;
		cout << "The elements in this range( " << r1 << " - " << r2 << " ):";
		while (p&&p->info<=r2)
		{
			cout << p->info << ' ';
			p = p->next;
		}
		cout << endl;
	}
	else
		cout << "Skip list is empty!" << endl;
}

//заполнение списка с пропусками случайно сгенерированными числами
void randomfill(SLNode<Node<int>* >*& first, SLNode<Node<int>* >*& last, int maxlvl)
{
	for (int i = 0;i < 1000000;i++)
	{
		int d = (int)random(-10000, 1000000);
		insert(first, last, maxlvl, d);
	}
}

int main()
{
	srand(time(NULL));
	
	int maxlvl = 20;
	SLNode<Node<int>* >* skip_list_front = NULL;
	SLNode<Node<int>* >* skip_list_back = NULL;

	int t = clock();
	randomfill(skip_list_front, skip_list_back, maxlvl);
	cout << "Time of 1 000 000 insertings in SKIP LIST = " << ((double)clock() - (double)t) * 1000. / CLOCKS_PER_SEC
		<< " milliseconds" << endl;

	t = clock();
	insert(skip_list_front, skip_list_back, maxlvl, 500510);
	cout << "Time of inserting in SKIP LIST = " << ((double)clock() - (double)t) * 1000 / CLOCKS_PER_SEC
		<< " milliseconds" << endl;

	t = clock();
	findadress(skip_list_back, 500510);
	cout << "Time of searching in SKIP LIST = " << ((double)clock() - (double)t) * 1000 / CLOCKS_PER_SEC << " milliseconds" << endl;

	t = clock();
	remove(skip_list_front, skip_list_back, 500510);
	cout << "Time of deleting in SKIP LIST = " << ((double)clock() - (double)t) * 1000 / CLOCKS_PER_SEC
		<< " milliseconds" << endl;

	clear(skip_list_front, skip_list_back);
	cout << endl;

	//вставка 1000000 элементов в стандартный список
	list<int> mylist;
	int b = clock();
	for (int i = 0; i < 1000000; ++i)
		mylist.push_front(random(-10000,1000000));
	cout << "Time of 1 000 000 insertings in LIST: "<< ((double)(clock() - (double)b)) * 1000. / CLOCKS_PER_SEC << " milliseconds" <<endl;

	b = clock();
	mylist.push_back(500510);
	cout << "Time of inserting in LIST: " << ((double)(clock() - (double)b)) * 1000. / CLOCKS_PER_SEC << " milliseconds" << endl;

	b = clock();
	auto j = find(mylist.begin(), mylist.end(), 500510);
	cout << "Time of searching in LIST: " << ((double)(clock() - (double)b)) * 1000. / CLOCKS_PER_SEC << " milliseconds" << endl;

	b = clock();
	auto i = find(mylist.begin(), mylist.end(), 500510);
	mylist.erase(i);
	cout << "Time of deleteing in LIST: " << ((double)(clock() - (double)b)) * 1000. / CLOCKS_PER_SEC << " milliseconds" << endl;

	cout << endl;

	//вставка 1000000 элементов в стандартный сэт, основанный на реализации красно-черных деревьев
	set<int> myset;
	b = clock();
	for (int i = 0;i < 1000000;i++)
		myset.insert(random(-10000,1000000));
	cout << "Time of 1 000 000 insertings in SET: "<< ((double)(clock() - (double)b)) * 1000. / CLOCKS_PER_SEC << " milliseconds" << endl;

	b = clock();
	myset.insert(500510);
	cout << "Time of inserting in SET: " << ((double)(clock() - (double)b)) * 1000. / CLOCKS_PER_SEC << " milliseconds" << endl;

	b = clock();
	myset.find(500510);
	cout << "Time of searching in SET: " << ((double)(clock() - (double)b)) * 1000. / CLOCKS_PER_SEC << " milliseconds" << endl;

	b = clock();
	myset.erase(500510);
	cout << "Time of removing in SET: " << ((double)(clock() - (double)b)) * 1000. / CLOCKS_PER_SEC << " milliseconds" << endl;

	cout << endl;

	

	///////checking up methods
	/*cout << "SKIP LIST:" << endl;
	skip_list_show(skip_list_back);cout << endl;

	randomfill20(skip_list_front, skip_list_back, maxlvl);
	
	cout << "SKIP LIST:" << endl;
	skip_list_show(skip_list_back);cout << endl;

	containsElement(skip_list_back, skip_list_front->info->info);

	cout << "Delete first element on a first lvl." << endl;
	remove(skip_list_front, skip_list_back, skip_list_front->info->info);

	cout << "SKIP LIST:" << endl;
	skip_list_show(skip_list_back);cout << endl;

	cout << "Insrting 5" << endl;
	insert(skip_list_front, skip_list_back, maxlvl, 5);

	cout << "SKIP LIST:" << endl;
	skip_list_show(skip_list_back);cout << endl;

	containsElement(skip_list_back, 5);

	cout << "Delete 5." << endl;
	remove(skip_list_front, skip_list_back, 5);

	cout << "SKIP LIST:" << endl;
	skip_list_show(skip_list_back);cout << endl;

	containsElement(skip_list_back, 5);cout << endl;

	showrange(skip_list_back);

	cout << "Delete all skip list." << endl;
	clear(skip_list_front, skip_list_back);
	
	cout << "SKIP LIST:" << endl;
	skip_list_show(skip_list_back);cout << endl;
	system("pause");*/
	
	system("pause");
	return 0;
}