#include "MyTimer.h"
#include <time.h>


MyTimer::MyTimer()
{
	start_time = clock();
	time_limit = 0;
}


MyTimer::MyTimer(int _time_limit_MS)
{
	this->time_limit = _time_limit_MS;
	this->start_time = clock();
}

int MyTimer::getElapsedTime() {
	return (clock() - start_time);
}

bool MyTimer::hasTime()
{
	
	if (time_limit == 0)
		return true;
	else
		return 2*getElapsedTime() < time_limit;
}
