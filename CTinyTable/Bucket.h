///////////////////////////////////////////////////////////
//  Bucket.h
//  Implementation of the Class Bucket
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////

#pragma once

#include <bitset>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <memory>
#include "TT_Key.h"
#include "TTStatistics.h"

class Bucket 
{
public:
	Bucket(bool _collect_statistics) : collect_statistics(_collect_statistics)
	{
		fingerPrint.reserve(40);
		isLast.reserve(40);
		itemCounter.reserve(40);

		if (collect_statistics)
			statistics = std::make_unique<TTStatistics>();
	}
	virtual ~Bucket()
	{
		
	}

	Bucket(Bucket &&oBucket) : collect_statistics(oBucket.collect_statistics), statistics(nullptr)
	{
		if (oBucket.statistics != nullptr)
			statistics = std::move(oBucket.statistics);
	}

	Bucket& operator=(Bucket &&oBucket)
	{
		if (this != &oBucket)
		{
			collect_statistics = oBucket.collect_statistics;
			if (oBucket.statistics != nullptr)
				statistics = std::move(oBucket.statistics);
		}
		return *this;
	}

	Bucket(Bucket const &) = delete;
	Bucket &operator=(Bucket const &) = delete;

	void DeleteItem(TT_Key key); 
	int FindItem(TT_Key key);
	unsigned int CalcItemFreq(TT_Key key);
	void InsertItem(TT_Key key);
	void UpdateItem(int index);
	int NumberOfItems();
	StatTimes& CalcStatistics(int bucketId);

private:
	bool collect_statistics;
	std::bitset<64> chainIndex;
	std::vector<char> fingerPrint;
	std::vector<bool> isLast;
	std::vector<unsigned char> itemCounter;
	std::unique_ptr<TTStatistics> statistics;
	StatTimes times;

	unsigned int calc_aco(int chainId, int lco);
	unsigned int calc_fco(int aco);
	unsigned int calc_lco(int chainId);
};

