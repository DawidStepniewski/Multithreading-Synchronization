#pragma once
#include "IThread.h"
#include "Producer.h"


class Consumer : public IThread
{
	Producer* PrPtr;
	std::mutex mtx;
	double avg;

public:
	Consumer(Producer* PrPtr) {};
	double GetAverage();
	virtual void ThreadRoutine();
};
