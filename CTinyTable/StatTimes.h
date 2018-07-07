#pragma once

#include <chrono>

class StatTimes
{
public:
	StatTimes():avgAddTime(0), medianAddTime(0), avgDeleteTime(0), medianDeleteTime(0), avgFindTime(0), medianFindTime(0),
		avgFreqCalcTime(0), medianFreqCalcTime(0)
	{

	}
	~StatTimes()
	{

	}

	std::chrono::nanoseconds avgAddTime;
	std::chrono::nanoseconds medianAddTime;
	std::chrono::nanoseconds avgDeleteTime;
	std::chrono::nanoseconds medianDeleteTime;
	std::chrono::nanoseconds avgFindTime;
	std::chrono::nanoseconds medianFindTime;
	std::chrono::nanoseconds avgFreqCalcTime;
	std::chrono::nanoseconds medianFreqCalcTime;
};

