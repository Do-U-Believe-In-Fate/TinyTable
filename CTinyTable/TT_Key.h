///////////////////////////////////////////////////////////
//  TT_Key.h
//  Implementation of the Class TT_Key
//  Created on:      20-Apr-2018 18:18:20
//  Original author: JS
///////////////////////////////////////////////////////////

#pragma once

class TT_Key
{
public:
	TT_Key(unsigned int _bucketId, unsigned char _chainId, char _fingerprint) : bucketId(_bucketId), chainId(_chainId), fingerprint(_fingerprint)
	{
		
	}
	~TT_Key()
	{

	}

	unsigned int bucketId;
	unsigned char chainId;
	char fingerprint;
};

