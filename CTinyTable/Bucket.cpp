///////////////////////////////////////////////////////////
//  Bucket.cpp
//  Implementation of the Class Bucket
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////

#include "Bucket.h"

unsigned int Bucket::calc_aco(int chainId, int lco)
{
	int aco = 0;
	int lastbits = 0;
	if (lco > 0)
	{
		while ((lastbits < lco) && (aco < isLast.size()))
		{
			if (isLast[aco])
				lastbits++;
			aco++;
		}
	}
	return aco;
}

unsigned int Bucket::calc_fco(int aco)
{
	int fco = aco;
	while (fco < isLast.size())
	{
		if (!isLast[fco])
			fco++;
		else
			break;
	}
	return fco + 1;
}

unsigned int Bucket::calc_lco(int chainId)
{
	int lco = 0;
	for (int i = 0; i < chainId; i++)
	{
		if (chainIndex.test(i))
			lco++;
	}
	return lco;
}

void Bucket::DeleteItem(TT_Key key)
{
	auto start = std::chrono::high_resolution_clock::now();

	if (chainIndex.test(key.chainId))
	{
		int lco = calc_lco(key.chainId);
		int aco = calc_aco(key.chainId, lco);
		int fco = calc_fco(aco);

		auto start_pos = fingerPrint.begin() + aco;
		auto end_pos = fingerPrint.begin() + fco;
		auto it = std::find(start_pos, end_pos, key.fingerprint);

		if (it != fingerPrint.end())
		{
			auto index = std::distance(fingerPrint.begin(), it);
			if (index > 0)
			{
				if (isLast[index] == true)
				{
					if (isLast[index - 1] == false)
					{
						isLast[index - 1] = true;
					}
					// This is the last element in the chain
					else 
					{
						chainIndex.reset(key.chainId);
					}
				}
			}
			//This is the last element in the chain
			else if (isLast[index] == true)
			{
				chainIndex.reset(key.chainId);
			}
			auto item_counter = itemCounter[index];
			if (item_counter <= 1)
			{
				itemCounter.erase(itemCounter.begin() + index);
				isLast.erase(isLast.begin() + index);
				fingerPrint.erase(fingerPrint.begin() + index);
			}
			else
				itemCounter[index]--;
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsedtime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	if (collect_statistics)
		statistics->StoreDeleteTime(elapsedtime);
}

int Bucket::FindItem(TT_Key key)
{
	auto start = std::chrono::high_resolution_clock::now();
	int distance = -1;

	if (chainIndex.test(key.chainId))
	{
		int lco = calc_lco(key.chainId);
		int aco = calc_aco(key.chainId, lco);
		int fco = calc_fco(aco);

		auto start_pos = fingerPrint.begin() + aco;
		auto end_pos = fingerPrint.begin() + fco;
		auto result = std::find(start_pos, end_pos, key.fingerprint);
		if (result != end_pos)
			distance = std::distance(fingerPrint.begin(), result);
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsedtime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	if (collect_statistics)
		statistics->StoreFindTime(elapsedtime);
	return distance;
}

unsigned int Bucket::CalcItemFreq(TT_Key key)
{
	auto start = std::chrono::high_resolution_clock::now();
	unsigned int freq = 0;

	if (chainIndex.test(key.chainId))
	{
		int lco = calc_lco(key.chainId);
		int aco = calc_aco(key.chainId, lco);
		int fco = calc_fco(aco);

		auto start_pos = fingerPrint.begin() + aco;
		auto end_pos = fingerPrint.begin() + fco;
		auto result = std::find(start_pos, end_pos, key.fingerprint);
		if (result != end_pos)
		{
			auto index = std::distance(fingerPrint.begin(), result);
			freq = itemCounter[index];
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsedtime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	if (collect_statistics)
		statistics->StoreCalcFreqTime(elapsedtime);
	return freq;
}

void Bucket::InsertItem(TT_Key key)
{
	auto start = std::chrono::high_resolution_clock::now();

	bool last = false;
	if (chainIndex.test(key.chainId) == false)
	{
		chainIndex.set(key.chainId);
		last = true;
	}
	int lco = calc_lco(key.chainId);
	int aco = calc_aco(key.chainId, lco);

	fingerPrint.emplace(fingerPrint.begin() + aco, key.fingerprint);
	itemCounter.emplace(itemCounter.begin() + aco, 1);
	if (last)
		isLast.emplace(isLast.begin() + aco, true);
	else
		isLast.emplace(isLast.begin() + aco, false);

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsedtime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	if (collect_statistics)
		statistics->StoreAddTime(elapsedtime);
}

void Bucket::UpdateItem(int index)
{
	itemCounter[index]++;
}

int Bucket::NumberOfItems()
{
	int nrItems = std::accumulate(itemCounter.begin(), itemCounter.end(), 0);
	return nrItems;
}

StatTimes& Bucket::CalcStatistics(int bucketId)
{
	statistics->CalcStatistics(times);
	return times;
}