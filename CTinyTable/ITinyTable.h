///////////////////////////////////////////////////////////
//  ITinyTable.h
//  Implementation of the Interface ITinyTable
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////

#pragma once
#include <string>

class ITinyTable
{
public:
	ITinyTable() 
	{

	}

	virtual ~ITinyTable() 
	{

	}

	virtual void AddItem(long item) =0;
	virtual void AddItem(std::string item) = 0;
	virtual int CountItemsInBucket(unsigned char bucketId) =0;
	virtual bool FindItem(long item) =0;
	virtual bool FindItem(std::string item) = 0;
	virtual unsigned int ItemFrequency(long item) = 0;
	virtual unsigned int ItemFrequency(std::string item) = 0;
	virtual void RemoveItem(long item) =0;
	virtual void RemoveItem(std::string item) = 0;
	virtual void PrintStatistics() = 0;
};

