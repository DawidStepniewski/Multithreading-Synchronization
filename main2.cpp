#include "Producer.h"
#include "Consumer.h"
#include "IThread.h"
#include "IntegratorPool.h"
#include <conio.h>
#include <iostream>
#include <vector>
#include <chrono>


int main() {

	//test zad7:
	
	Producer* pr[5];
	Consumer* cs[5];

	for (int i = 0; i < 5; i++)
	{
		pr[i] = new Producer();
		pr[i]->Start();

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		cs[i] = new Consumer(pr[i]);
		cs[i]->Start();
	}

	while (true)
	{
		int buff = _getch();

		if (buff == 13) //ENTER
		{
			for (int i = 0; i < 3; i++)
			{
				std::cout << "Consumer " << i + 1 << ": " << cs[i]->GetAverage() << std::endl;
			}
			std::cout << std::endl;
		}
		else if (buff == 27) //ESCAPE
		{
			std::cout << "Stopping threads...";
			break;
		}
	}
	for (int i = 0; i < 3; i++)
	{
		pr[i]->Stop();
		cs[i]->Stop();
	}

	// test zad8

	// wyniki zadanie 8
	//
	// 1000000 punktow 100 calek: Brak puli: 4024.086ms Pula obiektow: 3285.679ms
	// 1000000 punktow 10 calek: Brak puli: 424.984ms Pula obiektow: 366.226ms
	// 10000000 punktow 10 calek: Brak puli: 3345.948ms Pula obiektow: 3849.910ms
	//


	//create dataset
	double dt = 0.1;
	std::vector<double> dataSet;
	for (size_t i = 0; i < 1000000; i++)
	{
		dataSet.push_back(sin(i * dt) + 1);
		//dataSet.push_back(i);
	}

	//creating threads when needed (conventional way)
	{
		Integrator* integrators[100];
		auto tstart = std::chrono::high_resolution_clock::now();
		//create and start 100 threads
		for (size_t i = 0; i < 100; i++)
		{
			integrators[i] = new Integrator();
			integrators[i]->Start();
			integrators[i]->Count(dataSet, dt);
		}
		//wait until threads are done
		for (size_t i = 0; i < 100; i++)
		{
			while (integrators[i]->GetStatus() == Integrator::Status::WORKING);
			integrators[i]->Stop();
			delete integrators[i];
		}
		auto tstop = std::chrono::high_resolution_clock::now();
		std::cout << "Brak puli: " << std::chrono::duration_cast<std::chrono::microseconds>(tstop - tstart).count() << "us\n";

	}

	//pool
	{
		//create integrator pool with 10 workers
		auto threadPool = new IntegratorPool(10);
		auto tstart = std::chrono::high_resolution_clock::now();
		//perform count 100 times
		for (size_t i = 0; i < 100; i++)
		{
			Integrator* integrator;
			//blocking wait until any integrator is free
			while ((integrator = threadPool->GetInstance()) == nullptr);
			integrator->Count(dataSet, dt);
		}
		//wait until all threads are done
		while (threadPool->GetLoad() > 0);
		auto tstop = std::chrono::high_resolution_clock::now();
		std::cout << "Pula obiektow: " << std::chrono::duration_cast<std::chrono::microseconds>(tstop - tstart).count() << "us\n";
		delete threadPool;
	}

}
