#include "..\..\h\utils\SafeConvertor.h"

int SafeConvertor::toInt(double num)
{
	int i = (int) num;

	if (((double) i) - num != 0)
	{
		throw runtime_error("Cannot safely convert " + to_string(num) + " to int.");
	}

	return i;
}

time_t SafeConvertor::toTime(double num)
{
	time_t time = num;

	if (((double)time) - num != 0)
	{
		throw runtime_error("Cannot safely convert " + to_string(num) + " to time_t.");
	}

	return time;
}
