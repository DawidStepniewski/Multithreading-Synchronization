#include "Integrator.h"

Integrator::Integrator() : status(IDLE), step(0), result(0){}

void Integrator::ThreadRoutine()
{
	while (thrStatus == RUNNING)
	{
		if (GetStatus() == WORKING)
		{
			dataMutex.lock();
			resultMutex.lock();
			result = 0;
			for (int i = 0; i < data.size(); i++)
			{
				result += data[i] * step;
			}
			resultMutex.unlock();
			dataMutex.unlock();
			SetStatus(IDLE);
		}
		else
		{
			std::this_thread::yield();
		}
	}
}

double Integrator::GetResult()
{
	resultMutex.lock();
	double tempResult = result;
	resultMutex.unlock();
	return tempResult;
}

Integrator::Status Integrator::GetStatus()
{
	statusMutex.lock();
	Integrator::Status tempStatus = status;
	statusMutex.unlock();
	return tempStatus;
}

void Integrator::Count(const std::vector<double>& beginning, const double end)
{
	dataMutex.lock();
	data = beginning;
	step = end;
	SetStatus(WORKING);
	dataMutex.unlock();
}


void Integrator::SetStatus(Integrator::Status inStatus)
{
	statusMutex.lock();
	status = inStatus;
	statusMutex.unlock();
}
