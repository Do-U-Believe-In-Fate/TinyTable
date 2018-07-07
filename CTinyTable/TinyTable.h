///////////////////////////////////////////////////////////
//  TinyTable.h
//  Implementation of the Class TinyTable
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////

#pragma once

#include <cmath>
#include <memory>
#include <chrono>
#include "ITinyTable.h"
#include "Bucket.h"
#include "TT_Hash.h"


class TinyTable : public ITinyTable
{
public:
	TinyTable(unsigned int nItems, bool _use_statistics) : use_statistics(_use_statistics), hash_fn(round((nItems / 40.0f) + 0.5f), 6, 8)
	{
		nBuckets = round((nItems / 40.0f) + 0.5f);
		for (int i = 0; i < nBuckets; i++)
		{
			buckets.emplace_back(_use_statistics);
		}
	}
	virtual ~TinyTable()
	{
		
	}

	void AddItem(long item);
	void AddItem(std::string item);
	int CountItemsInBucket(unsigned char bucketId);
	bool FindItem(long item);
	bool FindItem(std::string item);
	unsigned int ItemFrequency(long item);
	unsigned int ItemFrequency(std::string item);
	void RemoveItem(long item);
	void RemoveItem(std::string item);
	void PrintStatistics();
	void PrintTableCapacity();
	
private:
	std::vector<Bucket> buckets;
	int nBuckets;
	TT_Hash hash_fn;
	bool use_statistics;
};

