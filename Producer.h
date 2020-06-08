#pragma once
#include "IThread.h"
#include <list>
#include <mutex>
#include <chrono>
#include <cstdlib>

class Producer : public IThread
{
	std::list<double> kolekcja;
	std::mutex mtx;

public:
	int GetRandom(int);
    std::list<double> GetColection();
	virtual void ThreadRoutine();
};
