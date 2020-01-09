#include <iostream>
#include <cstdlib>		//funkcje rand() i srand()
#include <ctime>		//funkcja time()
#include "queue.h"

const int MIN_PER_HR = 60;
const int CYCLE_PER_MIN = 1;
bool Newcustomer(double x); //czy dotar³ ju¿ nowy klient
const int ilosc_bankomatów = 2;
int main()
{
	Queue line[ilosc_bankomatów];
	using std::cin;
	using std::cout;
	using std::endl;
	using std::ios_base;

	int test_time_in_hours;
	double max_wait_time_in_queue;
	int max_queue_lenght;
	int clients_per_hour;
	//cout << "Podaj czas proby w godzinach: ";
	//cin >> test_time_in_hours;
	test_time_in_hours = 100;
	cout << "Podaj maksymalny czas oczekiwania klienta w minutach: ";
	cin >> max_wait_time_in_queue;
	cout << " Podaj dlugosc kolejki: ";
	cin >> max_queue_lenght;
	cout << "Podaj poczatkowa srednia ilosc klientow na godzine: ";
	cin >> clients_per_hour;
	long cycles_limit = test_time_in_hours * MIN_PER_HR*CYCLE_PER_MIN;
	double cycles_per_client = double(MIN_PER_HR) * CYCLE_PER_MIN / clients_per_hour;
	double average_wait_time = 1000;


	long turnaways;
	long customers;
	long served;
	long sum_line;
	int wait_time[ilosc_bankomatów];
	long line_wait;
	while (average_wait_time > max_wait_time_in_queue && clients_per_hour > 1)
	{
		Item temp[ilosc_bankomatów];
		turnaways = 0;
		customers = 0;
		served = 0;
		sum_line = 0;
		wait_time [ 0, 0 ];
		line_wait = 0;
		for (int cycles = 0; cycles < cycles_limit; cycles++)
		{
			//nowy klient
			if (Newcustomer(cycles_per_client))	
			{

				if (line[0].is_full())
				{
					if (line[0].queue_count() <= line[1].queue_count())
						turnaways++;
				}
				else
					if (line[0].queue_count() <= line[1].queue_count())
					{
						customers++;
						temp[0].set(cycles);
						line[0].end_queue(temp[0]);
					}
					else
					{
						customers++;
						temp[1].set(cycles);
						line[1].end_queue(temp[1]);
					}
			} //koniec tworzenia nowego klienta
			for (int i = 0; i < ilosc_bankomatów; i++)
			{
				if (wait_time[i] <= 0 && !line[i].is_empty())
				{
					line[i].del_queue(temp[i]);
					wait_time[i] = temp[i].ptime();
					line_wait += cycles - temp[i].when();
					//cout << "suma czasu oczekiwania: " << line_wait << "\n";
					served++;
				}
				if (wait_time[i] > 0)
					wait_time[i]--;
				sum_line += line[i].queue_count();
			}
		}
		//cout << "Line_wait: " << line_wait << "\t served: " << served << endl;
		average_wait_time = double(line_wait) / served;
		if (average_wait_time > max_wait_time_in_queue)
		{
			clients_per_hour--;
			cout << "sredni czas oczekiwania: " << average_wait_time << endl;
			cycles_per_client = double(MIN_PER_HR) * CYCLE_PER_MIN / clients_per_hour;
			line[0].~Queue();
			line[0];
			line[1].~Queue();
			line[1];
			cout << line[0].queue_count();
			cout << line[1].queue_count();

		}
		cout << "klientów na godzine: " << clients_per_hour << endl;

	}

	if (customers > 0)
	{
		cout << "Liczba klientow przyjetych: " << customers << endl;
		cout << "Liczba klientow obsluzonych: " << served << endl;
		cout << "Liczba klientow odeslanych: " << turnaways << endl;
		cout << "Srednia dlugosc kolejki: ";
		cout.precision(2);
		cout.setf(ios_base::fixed, ios_base::floatfield);
		cout.setf(ios_base::showpoint);
		cout << (double)sum_line / cycles_limit << endl;
		cout << "sredni czas oczekiwania: " << double(line_wait) / served << " minut\n";
	}
		else
			cout << "Brak klientow.\n";

	cout << "Gotowe!\n";
	cin.get();
	cin.get();
	return 0;
}


bool Newcustomer(double x)
{
	return (std::rand()*x < RAND_MAX);
}