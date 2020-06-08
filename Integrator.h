#pragma once
#include "IThread.h"
#include <vector>
#include <mutex>

class Integrator : public IThread {

public:
	
	enum  Status 
	{
		IDLE,
		WORKING
	};

	Integrator();
	void Count(const std::vector<double>&, const double);
	Status GetStatus();
	double GetResult();

private:

	std::vector<double> data;
	std::mutex dataMutex;
	std::mutex statusMutex;
	std::mutex resultMutex;
	Status status;
	double result;
	double step;
	void SetStatus(Status);
	void ThreadRoutine();
};

