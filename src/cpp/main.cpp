#include "../../stdafx.h"

#include <iostream>
#include <string>
#include "../h/main.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string filename;

	if (argc < 2)
	{
		cout << "Please provide filepath to the block JSON file:" << endl;
		cin >> filename;
	}
	else {
		//src: https://stackoverflow.com/questions/6291458/how-to-convert-a-tchar-array-to-stdstring
#ifndef UNICODE
		str = t;
#else
		std::wstring wStr = argv[1];
		filename = std::string(wStr.begin(), wStr.end());
#endif
	}

	if (!ifstream(filename).good())
	{
		cerr << "Cannot open JSON file: " << filename << endl;
		return 1;
	}

	JsonSerializer jss;
	JsonObject* jo = jss.fromJSONFile(filename.c_str());

	if (jo == nullptr)
	{
		cout << "-----------------" << endl;
		cerr << "Json file is invalid." << endl;
		return 1;
	}

	try
	{
		Block b = jss.loadBlock(jo);
		
		if (b.isValid())
		{
			cout << "Block is valid." << endl;
		}
		else {
			cout << "Block is invalid" << endl;
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
