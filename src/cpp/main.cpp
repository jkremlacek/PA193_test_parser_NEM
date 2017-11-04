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
		return 1;
	}

	//TODO: deserialize json object to app models

	cout << "DONE" << endl;
	return 0;
}

int testReturnOne() {
	return 1;
}
