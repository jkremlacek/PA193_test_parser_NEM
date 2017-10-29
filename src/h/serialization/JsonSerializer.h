#pragma once

#include <fstream>
#include <streambuf>
#include <string>
#include <map>

#include "JsonObject.h"

using namespace std;

class JsonSerializer
{
private:
	const string WHITESPACES = " \t\n\r\f\v";

	map<double, JsonObject> jsObjectStorage;
	double iteratorCounter = 0L;
	
public:
	JsonObject fromJSONFile(char* filename);

	JsonObject fromString(string& str);

	//TODO: test
	string getJsonAttributeName(string& str);

	string loadStringFromFile(const char* filename);

	//source: http://www.cplusplus.com/forum/beginner/50209/
	string removeWhitespacesFromBothSides(string& str);

	int getOtherBracketPos(const char leftBracket, const char rightBracket, string& str);

	JsonObject createJsonObject();

	JsonObject getJsonObjectWithId(double id);
};

