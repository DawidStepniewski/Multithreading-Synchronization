#include "Producer.h"

int Producer::GetRandom(int x)
{
	srand(time(NULL));
	return rand() % x;
}


void Producer::ThreadRoutine()
{
	
	srand(time(NULL));

	 do{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		double x = rand() % RAND_MAX;
		mtx.lock();
		kolekcja.push_back(x);
		mtx.unlock();
	 }
	 while (IThread::isRunning());

}
	std::list<double> Producer::GetColection()
	 {
		 std::list<double> temp;
		 mtx.lock();
		 temp = kolekcja;
		 mtx.unlock();

		 return temp;
	 }

