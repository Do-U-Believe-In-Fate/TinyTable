///////////////////////////////////////////////////////////
//  TinyTable.cpp
//  Implementation of the Class TinyTable
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////

#include <fstream> 
#include "TinyTable.h"

void TinyTable::AddItem(long item)
{
	TT_Key key = hash_fn.GetHash(item);
	Bucket& bucket = buckets[key.bucketId];
	
	int index = bucket.FindItem(key);
	if (index != -1)
		bucket.UpdateItem(index);
	else
		bucket.InsertItem(key);
}

void TinyTable::AddItem(std::string item)
{
	TT_Key key = hash_fn.GetHash(item);
	Bucket& bucket = buckets[key.bucketId];

	int index = bucket.FindItem(key);
	if (index != -1)
		bucket.UpdateItem(index);
	else
		bucket.InsertItem(key);
}

int TinyTable::CountItemsInBucket(unsigned char bucketId)
{
	int nrItems = 0;
	if (bucketId < nBuckets)
	{
		Bucket& bucket = buckets[bucketId];
		nrItems = bucket.NumberOfItems();
	}
	return nrItems;
}

bool TinyTable::FindItem(long item)
{
	TT_Key key = hash_fn.GetHash(item);
	Bucket& bucket = buckets[key.bucketId];

	int index = bucket.FindItem(key);
	if (index != -1)
		return true;
	else
		return false;
}

bool TinyTable::FindItem(std::string item)
{
	TT_Key key = hash_fn.GetHash(item);
	Bucket& bucket = buckets[key.bucketId];

	int index = bucket.FindItem(key);
	if (index != -1)
		return true;
	else
		return false;
}

unsigned int TinyTable::ItemFrequency(long item)
{
	TT_Key key = hash_fn.GetHash(item);
	Bucket& bucket = buckets[key.bucketId];

	return bucket.CalcItemFreq(key);
}

unsigned int TinyTable::ItemFrequency(std::string item)
{
	TT_Key key = hash_fn.GetHash(item);
	Bucket& bucket = buckets[key.bucketId];

	return bucket.CalcItemFreq(key);
}

void TinyTable::RemoveItem(long item)
{
	TT_Key key = hash_fn.GetHash(item);
	Bucket& bucket = buckets[key.bucketId];
	bucket.DeleteItem(key);
}

void TinyTable::RemoveItem(std::string item)
{
	TT_Key key = hash_fn.GetHash(item);
	Bucket& bucket = buckets[key.bucketId];
	bucket.DeleteItem(key);
}

void TinyTable::PrintTableCapacity()
{
	std::ofstream ofs("Capacity.txt", std::ofstream::out);
	for (int i = 0; i < nBuckets; i++)
		ofs << "Bucket number " << i << "contains " << buckets[i].NumberOfItems() << " elements!" << std::endl;

	ofs.close();
}

void TinyTable::PrintStatistics()
{
	std::ofstream ofs("Statistics.txt", std::ofstream::out);

	std::vector<std::chrono::nanoseconds> AddOperationStats;
	std::vector<std::chrono::nanoseconds> DeleteOpertaionStats;
	std::vector<std::chrono::nanoseconds> FindOperationStats;
	std::vector<std::chrono::nanoseconds> FreqOperationStats;
	std::chrono::nanoseconds zero(0);
	if (use_statistics)
	{
		for (int i = 0; i < buckets.size(); i++)
		{
			auto bucket_stats = buckets[i].CalcStatistics(i);
			if (bucket_stats.avgAddTime != zero)
				AddOperationStats.push_back(bucket_stats.avgAddTime);
			if (bucket_stats.avgDeleteTime != zero)
				DeleteOpertaionStats.push_back(bucket_stats.avgDeleteTime);
			if (bucket_stats.avgFindTime != zero)
				FindOperationStats.push_back(bucket_stats.avgFindTime);
			if (bucket_stats.avgFreqCalcTime != zero)
				FreqOperationStats.push_back(bucket_stats.avgFreqCalcTime);
		}
		if (AddOperationStats.size() > 0)
		{
			auto addSum = std::accumulate(AddOperationStats.begin(), AddOperationStats.end(), zero);
			auto avgAddTime = addSum / AddOperationStats.size();
			ofs << "Average time for Add operation : " << std::chrono::duration_cast<std::chrono::nanoseconds>(avgAddTime).count() << "(ns)" << std::endl;
		}
		else
			ofs << "No Add operations were performed this time!" << std::endl;

		if (DeleteOpertaionStats.size() > 0)
		{
			auto deleteSum = std::accumulate(DeleteOpertaionStats.begin(), DeleteOpertaionStats.end(), zero);
			auto avgDeleteTime = deleteSum / DeleteOpertaionStats.size();
			ofs << "Average time for Delete operation : " << std::chrono::duration_cast<std::chrono::nanoseconds>(avgDeleteTime).count() << "(ns)" << std::endl;
		}
		else
			ofs << "No Delete operations were performed this time!" << std::endl;

		if (FindOperationStats.size() > 0)
		{
			auto findSum = std::accumulate(FindOperationStats.begin(), FindOperationStats.end(), zero);
			auto avgFindTime = findSum / FindOperationStats.size();
			ofs << "Average time for Find operation : " << std::chrono::duration_cast<std::chrono::nanoseconds>(avgFindTime).count() << "(ns)" << std::endl;
		}
		else
			ofs << "No Find operations were performed this time!" << std::endl;

		if (FreqOperationStats.size() > 0)
		{
			auto freqSum = std::accumulate(FreqOperationStats.begin(), FreqOperationStats.end(), zero);
			auto avgFreqTime = freqSum / FreqOperationStats.size();
			ofs << "Average time for Frequency operation : " << std::chrono::duration_cast<std::chrono::nanoseconds>(avgFreqTime).count() << "(ns)" << std::endl;
		}
		else
			ofs << "No Frequency operations were performed this time!" << std::endl;
	}
	else
		ofs << "No statistics were collected!" << std::endl;
	ofs.close();
}