///////////////////////////////////////////////////////////
//  TT_Hash.h
//  Implementation of the Class TT_Hash
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////

#pragma once

#include <functional>
#include <string>
#include "TT_Key.h"

class TT_Hash
{
public:
	TT_Hash(int _nBuckets, int _chainSize, int _fpSize) : nBuckets(_nBuckets), chainSize(_chainSize), fpSize(_fpSize)
	{
		chainMask = (1 << chainSize) - 1;
		fpMask = (1 << fpSize) - 1;
	}
	virtual ~TT_Hash()
	{

	}

	TT_Key GetHash(long item);
	TT_Key TT_Hash::GetHash(std::string item);

private:
	int nBuckets;
	int chainSize;
	int chainMask;
	int fpSize;
	int fpMask;
};

