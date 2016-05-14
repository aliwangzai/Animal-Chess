#pragma once


class MyTimer {
public:
	MyTimer(int _time_limit_MS);
	MyTimer();
	~MyTimer() {};
private:
	int start_time;
	int time_limit;
public:
	int getElapsedTime();
	bool hasTime();
};
