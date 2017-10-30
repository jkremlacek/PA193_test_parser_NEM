#pragma once

#include <time.h>
#include <string>

using namespace std;

class SafeConvertor
{
public:
	SafeConvertor() {};
	~SafeConvertor() {};

	/*
		converts double value to int only if no precision loss occurs,
		otherwise runtime_error is thrown
	*/
	static int toInt(double num);

	/*
	converts double value to long only if no precision loss occurs,
	otherwise runtime_error is thrown
	*/
	static long long toLong(double num);

	/*
		converts double value to time_t only if no precision loss occurs,
		otherwise runtime_error is thrown
	*/
	static time_t toTime(double num);
};

