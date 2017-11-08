#pragma once

#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <map>
#include <list>

#include "JsonObject.h"
#include "../model/Block.h"

using namespace std;

enum BracketType{CURLY, SQUARE};

class JsonSerializer
{
private:
	const string WHITESPACES = " \t\n\r\f\v";

	/*
		container of loaded JsonObjects with their unique id key
	*/
	map<double, JsonObject*> jsObjectStorage;
	double iteratorCounter = 0L;
	
public:
	/*
		frees memory allocated for JsonObjects within jsObjectStorage
	*/
	~JsonSerializer();

	/*
		loads NEM block from a JSON object
	*/
	Block loadBlock(JsonObject* root);

	/*
		loads JSON object from JSON file
	*/
	JsonObject* fromJSONFile(const char* filename);

	/*
		loads single JSON object fom supplied string
	*/
	pair<double, JsonObject*> fromString(string& str);

	/*
		loads attribute name from string, which must start with " or whitespace before it
	*/
	string getJsonAttributeName(string& str);

	/*
		util method loading entire content of text file into string variable
	*/
	string loadStringFromFile(const char* filename);

	//source: http://www.cplusplus.com/forum/beginner/50209/
	/*
		removes characters defined in WHITESPACES from both ends of string
	*/
	string removeWhitespacesFromBothSides(string& str);

	/*
		creates new json object in jsObjectStorage
	*/
	pair<double, JsonObject*> createJsonObject();

	/*
		retreives json object from jsObjectStorage with supplied id
	*/
	JsonObject* getJsonObjectWithId(double id);

	/*
		loads STRING attribute value from the supplied str string
		(must be encapsulated with "")
	*/
	JsonAttribute getJsonStringAttribute(string& str, string name);

	/*
		loads SINGLE_OBJECT attribute value from the supplied str string
		(must be encapsulated with {})
	*/
	JsonAttribute getJsonSingleObjAttribute(string& str, string name);

	/*
		loads ARRAY attribute value from the supplied str string
		(must be encapsulated with [])
	*/
	JsonAttribute getJsonArrayObjAttribute(string& str, string name);

	/*
		retreives substring from str variable defined by brackets
		(count of left brackets must be equal to right brackets count in substring)
	*/
	string getBracketSubstring(string& str, BracketType bt, bool eraseFromStr = false);

	/*
		loads substring containing only number from the start of the str variable
	*/
	string getNumberSubstring(string& str);

	/*
		util method for formatting error message
	*/
	string getErrorStrSegment(string& str);
};

