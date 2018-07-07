///////////////////////////////////////////////////////////
//  TTStatistics.h
//  Implementation of the Class TTStatistics
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////
#pragma once

#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <iostream>
#include "StatTimes.h"

class TTStatistics
{
public:
	TTStatistics()
	{
		insertTimes.reserve(40);
		deleteTimes.reserve(40);
		findTimes.reserve(40);
		calcFreqTimes.reserve(40);
	}
	~TTStatistics()
	{

	}

	void StoreAddTime(std::chrono::nanoseconds elapsedTime);
	void StoreDeleteTime(std::chrono::nanoseconds elapsedTime);
	void StoreFindTime(std::chrono::nanoseconds elapsedTime);
	void StoreCalcFreqTime(std::chrono::nanoseconds elapsedTime);
	void CalcStatistics(StatTimes& times);

private:
	std::vector<std::chrono::nanoseconds> insertTimes;
	std::vector<std::chrono::nanoseconds> deleteTimes;
	std::vector<std::chrono::nanoseconds> findTimes;
	std::vector<std::chrono::nanoseconds> calcFreqTimes;
};

