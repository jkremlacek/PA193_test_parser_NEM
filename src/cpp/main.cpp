#include "../../stdafx.h"

#include <iostream>
#include <string>
#include "../h/main.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string filename1;
	string filename2;

	// if the filename(s) were not supplied to the program as arguments, prompt for them
	if (argc < 2)
	{
		cout << "Please provide filepath to the block JSON file:" << endl;
		cin >> filename1;
		cout << "Optionally provide filepath to the previous block JSON file:" << endl;
		cin >> filename2;
	}
	else {
		/* if the filenames were supplied as arguments, retrieve them (with conversion from a Unicode
		   string to std::string */
		// src: https://stackoverflow.com/questions/6291458/how-to-convert-a-tchar-array-to-stdstring
#ifndef UNICODE
		str = t;
#else
		std::wstring wStr = argv[1];
		filename1 = std::string(wStr.begin(), wStr.end());
#endif
	}

	// try to open the file with the current block
	if (!ifstream(filename1).good())
	{
		cerr << "Cannot open JSON file: " << filename1 << endl;
		return 1;
	}

	// load the current block into JsonObject
	JsonSerializer jss;
	JsonObject* jo1 = jss.fromJSONFile(filename1.c_str());
	JsonObject* jo2 = nullptr;

	/* if the second filename was supplied to the program as an argument, retrieve it and try to open
	   that file analogically as the first one - this is the file with the previous block, which will
	   allow us to perform full validation */
	if (argc == 3)
	{
#ifndef UNICODE
		str = t;
#else
		std::wstring wStr = argv[2];
		filename2 = std::string(wStr.begin(), wStr.end());
#endif
		if (!ifstream(filename2).good())
		{
			cerr << "Cannot open JSON file: " << filename2 << endl;
			return 1;
		}

		jo2 = jss.fromJSONFile(filename1.c_str());
	}

	// check if the blocks were successfully loaded to the JsonObjects
	if (jo1 == nullptr)
	{
		cout << "-----------------" << endl;
		cerr << "First JSON file is invalid." << endl;
		return 1;
	}
	if ((argc == 3) && (jo2 == nullptr))
	{
		cout << "-----------------" << endl;
		cerr << "Second JSON file is invalid." << endl;
		return 1;
	}

	try
	{
		// load the current block into Block object
		Block b1 = jss.loadBlock(jo1);
		Block b2;
		
		/* if the previous block is also available, load it into Block object as well and perform
		   full validation using both blocks */
		if (jo2 != nullptr)
		{
			b2 = jss.loadBlock(jo2);

			if (b1.isValid(b2))
			{
				cout << "Current block is valid." << endl;
			}
			else {
				cout << "Current block is invalid" << endl;
			}
		}
		// otherwise, perform partial validation using only current block
		else
		{
			if (b1.isValid())
			{
				cout << "Current block is valid." << endl;
			}
			else {
				cout << "Current block is invalid" << endl;
			}
		}
	}
	catch (const std::exception& e)
	{
		cout << "Block is corrupted." << endl;
		cout << "-----------------" << endl;
		cout << "Reason:" << endl;
		cout << e.what() << endl;
		return 1;
	}

	cout << "DONE" << endl;
	return 0;
}

int testReturnOne() {
	return 1;
}
