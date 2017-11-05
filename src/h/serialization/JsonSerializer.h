#pragma once

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <map>

#include "JsonObject.h"
#include "../model/Block.h"

using namespace std;

enum BracketType{CURLY, SQUARE};

class JsonSerializer
{
private:
	const string WHITESPACES = " \t\n\r\f\v";

	map<double, JsonObject*> jsObjectStorage;
	double iteratorCounter = 0L;
	
public:
	~JsonSerializer();

	Block loadBlock(const char* filename);

	JsonObject* fromJSONFile(const char* filename);

	pair<double, JsonObject*> fromString(string& str);

	//TODO: test
	string getJsonAttributeName(string& str);

	string loadStringFromFile(const char* filename);

	//source: http://www.cplusplus.com/forum/beginner/50209/
	string removeWhitespacesFromBothSides(string& str);

	pair<double, JsonObject*> createJsonObject();

	JsonObject* getJsonObjectWithId(double id);

	JsonAttribute getJsonStringAttribute(string& str, string name);

	JsonAttribute getJsonSingleObjAttribute(string& str, string name);

	JsonAttribute getJsonArrayObjAttribute(string& str, string name);

	string getBracketSubstring(string& str, BracketType bt, bool eraseFromStr = false);

	string getNumberSubstring(string& str);

	string getErrorStrSegment(string& str);
};

