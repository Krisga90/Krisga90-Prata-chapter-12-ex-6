#pragma once
#ifndef QUEUE_H_
#define QUEUE_H_
class Customer
{
private:
	long arrive;			//czas do³¹czenia klienta do kolejki
	int processtime;		// czas obs³ugi klienta

public:
	Customer() { arrive = processtime = 0; }
	~Customer() {}
	void set(long when);
	long when() const { return arrive; }
	int ptime()const { return processtime; }
};

typedef Customer Item;

class Queue
{
private:
	//Node to definicja zasiegu zagnie¿d¿ona klasy, lokalna wzglêdem tej klasy
	struct Node
	{
		Item item;
		struct Node*next;
	};
	enum { Q_SIZE = 10 };
	Node * front;
	Node * rear;
	int items;
	const int qsize;		//maksymalna wielkosc kolejki
	//definicje blokujace publiczny dostep do kopiowania
	Queue(const Queue &q) :qsize(0) {}
	Queue & operator=(const Queue & q) { return *this; }

public:
	Queue(int qs = Q_SIZE);
	~Queue();
	bool is_empty()const;
	bool is_full()const;
	int queue_count()const;
	bool end_queue(const Item & item);	//dodaje element na koniec kolejki
	bool del_queue(Item & item);		//wyciaga element z czo³a kolejki

};

#endif //QUEUE_H_