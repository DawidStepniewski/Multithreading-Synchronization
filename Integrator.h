#pragma once
#include "IThread.h"
#include <vector>
#include <mutex>

class Integrator : public IThread {

	std::vector<double> data;
	std::mutex dataMutex;
	std::mutex statusMutex;
	std::mutex resultMutex;
	double step;
	void SetStatus(Status);
	void ThreadRoutine();
public:

	enum Status {
		IDLE,
		WORKING
	};

	Integrator();
	void Count(const std::vector<double>&, const double);
	Status GetStatus();
	double GetResult();
};
