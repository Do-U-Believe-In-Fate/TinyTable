///////////////////////////////////////////////////////////
//  TTStatistics.cpp
//  Implementation of the Class TTStatistics
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////
#include "TTStatistics.h"

void TTStatistics::StoreAddTime(std::chrono::nanoseconds elapsedTime)
{
	insertTimes.emplace_back(elapsedTime);
}

void TTStatistics::StoreDeleteTime(std::chrono::nanoseconds elapsedTime)
{
	deleteTimes.push_back(elapsedTime);
}

void TTStatistics::StoreFindTime(std::chrono::nanoseconds elapsedTime)
{
	findTimes.push_back(elapsedTime);
}

void TTStatistics::StoreCalcFreqTime(std::chrono::nanoseconds elapsedTime)
{
	calcFreqTimes.push_back(elapsedTime);
}

void TTStatistics::CalcStatistics(StatTimes& times)
{
	std::chrono::nanoseconds zero(0);
	if (insertTimes.size() > 0)
	{
		auto addSum = std::accumulate(insertTimes.begin(), insertTimes.end(), zero);
		auto avgAddTime = addSum / insertTimes.size();
		std::sort(insertTimes.begin(), insertTimes.end());
		times.avgAddTime = avgAddTime;
		times.medianAddTime = (insertTimes.at(insertTimes.size() / 2));
	}
	else
	{
		times.avgAddTime = zero;
		times.medianAddTime = zero;
	}
		

	if (deleteTimes.size() > 0)
	{
		auto deleteSum = std::accumulate(deleteTimes.begin(), deleteTimes.end(), zero);
		auto avgDeleteTime = deleteSum / deleteTimes.size();
		times.avgDeleteTime = avgDeleteTime;
		times.medianDeleteTime = (deleteTimes.at(deleteTimes.size() / 2));
	}
	else
	{
		times.avgDeleteTime = zero;
		times.medianDeleteTime = zero;
	}
	
	if (findTimes.size() > 0)
	{
		auto findSum = std::accumulate(findTimes.begin(), findTimes.end(), zero);
		auto avgFindTime = findSum / findTimes.size();
		times.avgFindTime = avgFindTime;
		times.medianFindTime = (findTimes.at(findTimes.size() / 2));
	}
	else
	{
		times.avgFindTime = zero;
		times.medianFindTime = zero;
	}
	if (calcFreqTimes.size() > 0)
	{
		auto freqSum = std::accumulate(calcFreqTimes.begin(), calcFreqTimes.end(), zero);
		auto avgFreqTime = freqSum / findTimes.size();
		times.avgFreqCalcTime = avgFreqTime;
		times.medianFreqCalcTime = (calcFreqTimes.at(calcFreqTimes.size() / 2));
	}
	else
	{
		times.avgFreqCalcTime = zero;
		times.medianFreqCalcTime = zero;
	}
}