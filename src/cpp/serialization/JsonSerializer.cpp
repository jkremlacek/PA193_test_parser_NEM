#include "..\..\h\serialization\JsonSerializer.h"

JsonObject JsonSerializer::fromJSONFile(char* filename) {
	return fromString(loadStringFromFile(filename));
}

JsonObject JsonSerializer::fromString(string& str) {
	JsonObject jso = createJsonObject();

	removeWhitespacesFromBothSides(str);

	if (str[0] != '{')
	{
		throw new exception("Invalid format, missing '{' bracket.");
	}

	str.erase(0, 1);

	if (str[str.length() - 1] != '}') {
		throw new exception("Invalid format, missing '}' bracket.");
	}

	str.erase(str.length() - 1, 1);

	while (str.length() != 0)
	{
		string jsonAttributeName = getJsonAttributeName(str);

		removeWhitespacesFromBothSides(str);

		int otherBracketPos;
		int textContentEndPos;

		switch (str[0])
		{
		case '"':
			str.erase(0, 1);

			textContentEndPos = str.find_first_of("\'");
			if (textContentEndPos == string::npos)
			{
				throw new exception("Invalid format, missing '\"'");
			}

			jso.addAttribute(JsonAttribute(STRING, str.substr(textContentEndPos)));

			str.erase(0, textContentEndPos);

			break;
		case '[':
			//TODO multiple object
			//count [ before first ] then ignore ] that many times and then get position of next one ] (care for repeating of [ again)
			//use counter = 1 of {}, for every { +1 and for every } -1, do this untill counter = 0, because that is our } otherwise throw exception
			otherBracketPos = getOtherBracketPos('[', ']', str);

			break;
		case '{':
			//TODO single
			//count { before first } then ignore } that many times and then get position of next one } (care for repeating of { again)
			otherBracketPos = getOtherBracketPos('{', '}', str);
			
			break;
		default:
			throw new exception(string("Invalid format, expected one of: \", [, {, instead got: \"" + str.substr(1) + "\" in ..." + str.substr(20) + "...").c_str());
			break;
		}

		//TODO
	}

	return jso;
}

string JsonSerializer::getJsonAttributeName(string & str)
{
	removeWhitespacesFromBothSides(str);

	int separatorPos = str.find_first_of(':');

	if (separatorPos == string::npos)
	{
		throw new exception("Invalid format, missing ':'");
	}

	string jsonAttributeName = str.substr(separatorPos);

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

int JsonSerializer::getOtherBracketPos(const char leftBracket, const char rightBracket, string & str)
{
	//TODO
	return 0;
}

JsonObject JsonSerializer::createJsonObject()
{
	double id = iteratorCounter;
	iteratorCounter++;

	JsonObject jo(id);

	jsObjectStorage.insert(pair<double, JsonObject>(id, jo));

	return JsonObject(iteratorCounter);
}

JsonObject JsonSerializer::getJsonObjectWithId(double id)
{
	map<double, JsonObject>::iterator it = jsObjectStorage.find(id);

	if (it == jsObjectStorage.end())
	{
		throw new exception("Object not found within the storage.");
	}

	return it->second;
}


