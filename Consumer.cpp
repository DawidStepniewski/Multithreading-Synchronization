#include "Consumer.h"
#include "Producer.h"
#include "IThread.h"


void Consumer::ThreadRoutine() {

	srand(time(NULL));

	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::list<double> temp = PrPtr->GetColection();
		mtx.lock();
		avg = 0;
		for (auto const& n : temp) {

			avg = avg + n;

		}
		avg = avg / temp.size();
		mtx.unlock();
	}
	while (IThread::isRunning);
}

double Consumer::GetAverage()
{
	mtx.lock();
	double actAvg = avg;
	mtx.unlock();
	return actAvg;
}
