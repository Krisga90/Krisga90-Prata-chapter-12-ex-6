#include "queue.h"
#include <cstdlib>	//funkcja rand()




Queue::Queue(int qs) :qsize(qs)		// inicjalizacja wartoœci const!!
{
	front = rear = nullptr;
	items = 0;
}

Queue::~Queue()
{
	Node * temp;
	while (front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
	items = 0;
}

bool Queue::is_empty()const
{
	return items == 0;
}

bool Queue::is_full()const
{
	return items == qsize;
}

int Queue::queue_count()const
{
	return items;
}


bool Queue::end_queue(const Item & item)	//dodaje element na koniec kolejki
{
	if (is_full())
		return false;
	Node * add = new Node;
	add->item = item;		//ustawienie wska¿ników wêz³ów nie kopiuje adrsu tylko wartosci
	add->next = nullptr;
	items++;
	if (front == nullptr)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

//kopiuje element czo³owy kolejki do argumentu wywo³ania i usuwa go z kolejki

bool Queue::del_queue(Item & item)
{
	if (front == NULL)
		return false;
	item = front->item;
	items--;
	Node *temp = front;
	front = front->next;
	delete temp;
	if (items == 0)
		rear = NULL;
	return true;

}


//metody klasy customer



void Customer::set(long when)
{
	processtime = std::rand() % 3 + 1;
	arrive = when;
}