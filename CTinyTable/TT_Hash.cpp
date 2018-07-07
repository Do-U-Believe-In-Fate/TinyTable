///////////////////////////////////////////////////////////
//  TT_Hash.cpp
//  Implementation of the Class TT_Hash
//  Created on:      20-Apr-2018 18:07:16
//  Original author: JS
///////////////////////////////////////////////////////////

#include "TT_Hash.h"

using namespace std;

TT_Key TT_Hash::GetHash(long item)
{
	std::hash<long> hash_fn;
	size_t hash = hash_fn(item);
	char fingerprint = hash & fpMask;
	hash >>= fpSize;
	unsigned char chain = hash & chainMask;
	hash >>= chainSize;
	unsigned int bucket = (hash & SIZE_MAX) % nBuckets;
	TT_Key key(bucket, chain, fingerprint);

	return key;
}

TT_Key TT_Hash::GetHash(std::string item)
{
	std::hash<std::string> hash_fn;
	size_t hash = hash_fn(item);
	char fingerprint = hash & fpMask;
	hash >>= fpSize;
	unsigned char chain = hash & chainMask;
	hash >>= chainSize;
	unsigned char bucket = (hash & SIZE_MAX) % nBuckets;
	TT_Key key(bucket, chain, fingerprint);

	return key;
}