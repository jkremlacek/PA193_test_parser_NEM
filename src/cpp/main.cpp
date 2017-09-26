#include "../../stdafx.h"

#include <iostream>

using namespace std;

int _tmain(int argc, TCHAR* argv[])
{
	cout << "Hello World" << endl;

	if (argc == 1 && argv)
	{
		return 0;
	}

	int i;

	cin >> i;

	return 0;
}

