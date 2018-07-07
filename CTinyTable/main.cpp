
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "TinyTable.h"

bool getFileContent(std::string fileName, std::vector<long> & vecOfInts)
{

	// Open the File
	std::ifstream inFile(fileName.c_str());

	// Check if object is valid
	if (!inFile)
	{
		std::cerr << "Cannot open the File : " << fileName << std::endl;
		return false;
	}

	std::string str;
	// Read the next line from File untill it reaches the end.
	while (std::getline(inFile, str))
	{
		// Line contains string of length > 0 then save it in vector
		if (str.size() > 0)
		{
			int value = std::stoi(str);
			vecOfInts.push_back(value);
		}

	}

	//Close The File
	inFile.close();
	return true;
}

void main(int argc, char * argv[])
{
	std::vector<long> toAdd;
	std::vector<long> toFind;
	std::vector<long> toDelete;
	std::vector<long> toFindFreq;

	// Get the contents of the file into the vector
	std::string addFile = argv[1];
	bool res1 = false;
	if (!addFile.empty())
		res1 = getFileContent(addFile, toAdd);
	if (res1)
	{
		TinyTable ttable(toAdd.size(), true);
		for (long& e : toAdd)
			ttable.AddItem(e);
		ttable.PrintTableCapacity();

		std::string findFile = argv[2];
		bool res2 = false;
		if (!findFile.empty())
			res2 = getFileContent(findFile, toFind);
		if (res2)
		{
			for (long& e : toFind)
			{
				bool res = ttable.FindItem(e);
			}
		}

		std::string findFreqFile = argv[3];
		bool res3 = false;
		if (!findFreqFile.empty())
			res3 = getFileContent(findFreqFile, toFindFreq);
		if (res3)
		{
			for (long& e : toFindFreq)
			{
				unsigned int freq = ttable.ItemFrequency(e);
			}
		}

		std::string deleteFile = argv[4];
		bool res4 = false;
		if (!deleteFile.empty())
			res4 = getFileContent(deleteFile, toDelete);
		if (res4)
		{
			for (long& e : toDelete)
				ttable.RemoveItem(e);
		}
		ttable.PrintStatistics();
	}	

	system("pause");
	return;
}