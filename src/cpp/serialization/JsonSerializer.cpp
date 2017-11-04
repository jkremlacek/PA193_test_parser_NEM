#include "..\..\h\serialization\JsonSerializer.h"

JsonSerializer::~JsonSerializer()
{
	for (
		map<double, JsonObject*>::iterator it = jsObjectStorage.begin();
		it != jsObjectStorage.end();
		it++)
	{
		delete(it->second);
	}
}

JsonObject* JsonSerializer::fromJSONFile(char* filename) {
	return fromString(loadStringFromFile(filename)).second;
}

pair<double,JsonObject*> JsonSerializer::fromString(string& str) {
	pair<double, JsonObject*> pdj = createJsonObject();
	JsonObject* jso = pdj.second;

	removeWhitespacesFromBothSides(str);

	if (str[0] != '{')
	{
		throw runtime_error("Invalid format, missing '{' bracket.");
	}

	str.erase(0, 1);

	if (str[str.length() - 1] != '}') {
		throw runtime_error("Invalid format, missing '}' bracket.");
	}

	str.erase(str.length() - 1, 1);

	while (str.length() != 0)
	{
		string jsonAttributeName = getJsonAttributeName(str);

		removeWhitespacesFromBothSides(str);

		switch (str[0])
		{
		case '"':
			jso->addAttribute(getJsonStringAttribute(str, jsonAttributeName));
			break;
		case '[':
			jso->addAttribute(getJsonArrayObjAttribute(getBracketSubstring(str, SQUARE, true), jsonAttributeName));
			break;
		case '{':
			jso->addAttribute(getJsonSingleObjAttribute(getBracketSubstring(str, CURLY, true), jsonAttributeName));
			break;
		default:
			if (str.substr(0,4) == "true")
			{
				jso->addAttribute(JsonAttribute::createBoolAttribute(str.substr(0, 4), jsonAttributeName));
				str.erase(0, 4);
			}
			else if (str.substr(0, 5) == "false") {
				jso->addAttribute(JsonAttribute::createBoolAttribute(str.substr(0, 5), jsonAttributeName));
				str.erase(0, 5);
			}
			else if (str.substr(0,1).find_first_of(".0123456789") != string::npos) {
				jso->addAttribute(JsonAttribute::createNumAttribute(getNumberSubstring(str), jsonAttributeName));
			}
			else {
				throw runtime_error(string("Invalid format, expected one of: \", [, {, instead got: \"" + str.substr(1) + "\" in ..." + str.substr(20) + "...").c_str());
				break;
			}
			
		}
	}

	return pdj;
}

string JsonSerializer::getJsonAttributeName(string & str)
{
	removeWhitespacesFromBothSides(str);

	int separatorPos = str.find_first_of(':');

	if (separatorPos == string::npos)
	{
		throw runtime_error("Invalid format, missing ':'");
	}

	string jsonAttributeName = str.substr(0, separatorPos);

	//TODO:check that : is erased
	str.erase(0, jsonAttributeName.length() + 1);

	return jsonAttributeName;
}

string JsonSerializer::loadStringFromFile(const char* filename) {
	ifstream file(filename);

	return string((
		istreambuf_iterator<char>(file)),
		istreambuf_iterator<char>()
	);
}

string JsonSerializer::removeWhitespacesFromBothSides(string& str) {
	str.erase(0, str.find_first_not_of(WHITESPACES));
	str.erase(str.find_last_not_of(WHITESPACES) + 1);
	return str;
}

pair<double, JsonObject*> JsonSerializer::createJsonObject()
{
	double id = iteratorCounter;
	iteratorCounter++;

	JsonObject* jo = new JsonObject(id);

	jsObjectStorage.insert(pair<double, JsonObject*>(id, jo));

	return pair<double, JsonObject*>(id, jo);
}

JsonObject* JsonSerializer::getJsonObjectWithId(double id)
{
	map<double, JsonObject*>::iterator it = jsObjectStorage.find(id);

	if (it == jsObjectStorage.end())
	{
		throw new runtime_error("Object not found within the storage.");
	}

	return it->second;
}

JsonAttribute JsonSerializer::getJsonStringAttribute(string & str, string name)
{
	//note that str must start with the " symbol starting the attribute value
	str.erase(0, 1);

	int endPos = str.find_first_of("\"");
	if (endPos == string::npos)
	{
		throw runtime_error("Invalid format, missing '\"'");
	}

	JsonAttribute ja(STRING, name);
	ja.setTextValue(str.substr(0, endPos));

	str.erase(0, endPos + 1);
	removeWhitespacesFromBothSides(str);

	if (str.length() != 0)
	{
		if (str[0] != ',')
		{
			throw runtime_error("Invalid format, missing ','");
		}
		
		str.erase(0, 1);
	}

	return ja;
}

JsonAttribute JsonSerializer::getJsonSingleObjAttribute(string & str, string name)
{
	JsonAttribute ja(SINGLE_OBJECT, name);
	string substr = getBracketSubstring(str, CURLY);

	str.erase(0, substr.length() + 1);

	ja.addJsonValue(fromString(substr).first);

	return ja;
}

JsonAttribute JsonSerializer::getJsonArrayObjAttribute(string & str, string name)
{
	JsonAttribute ja(ARRAY, name);

	string substr = getBracketSubstring(str, SQUARE);
	
	str.erase(0, substr.length() + 1);

	substr.erase(0, 1);
	substr.erase(substr.length() - 1, 1);

	while (substr.length() != 0)
	{
		removeWhitespacesFromBothSides(substr);

		string joStr = getBracketSubstring(substr, CURLY);
		substr.erase(0, joStr.length());

		ja.addJsonValue(fromString(joStr).first);

		removeWhitespacesFromBothSides(substr);

		if (substr.length() != 0)
		{
			if (substr[0] != ',')
			{
				throw runtime_error("Invalid format, missing ','");
			}

			substr.erase(0, 1);
		}
	}

	return ja;
}

string JsonSerializer::getBracketSubstring(string & str, BracketType bt, bool eraseFromStr)
{
	const char leftBracket =
		bt == CURLY ? '{' :
		bt == SQUARE ? '[' :
		'\0';

	const char rightBracket =
		bt == CURLY ? '}' :
		bt == SQUARE ? ']' :
		'\0';

	if (leftBracket == '\0' || rightBracket == '\0')
	{
		throw runtime_error("Undefined BracketType.");
	}

	if (str[0] != leftBracket)
	{
		throw runtime_error("Unexpected bracket type: " + str[0]);
	}

	int semaphore = 1;

	for (unsigned int i = 1; i < str.length(); i++)
	{
		if (str[i] == leftBracket)
		{
			semaphore++;
		}
		else if (str[i] == rightBracket)
		{
			semaphore--;

			if (semaphore == 0)
			{
				string substr = str.substr(0, i + 1);

				if (eraseFromStr)
				{
					str.erase(0, substr.length() + 1);
				}
				
				return substr;
			}
		}
	}

	throw runtime_error("Other bracket not found.");
}

string JsonSerializer::getNumberSubstring(string & str)
{
	string substr = str.substr(0, str.find_first_not_of(".0123456789"));
	str.erase(0, substr.length() + 1);
	return substr;
}

