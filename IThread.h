#pragma once
#include <thread>
class IThread
{
public:
	enum Status
	{
		STOPPED,
		RUNNING
	};
	std::thread* thr;
	Status status;
	IThread();
	virtual ~IThread();
	void Start();
	void Stop();
	void Join();
	bool isRunning();
	virtual void ThreadRoutine() = 0;

protected:
	Status thrStatus;
	std::thread* thrPointer;
};

