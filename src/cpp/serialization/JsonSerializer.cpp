#include "..\..\h\serialization\JsonSerializer.h"

JsonObject JsonSerializer::fromJSONFile(char* filename) {
	return fromString(loadStringFromFile(filename));
}

JsonObject JsonSerializer::fromString(string& str) {
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
		string jsonObjectName;
		JsonObjectType type;

		removeWhitespacesFromBothSides(str);

		int separatorPos = str.find_first_of(':');

		jsonObjectName = str.substr(separatorPos);

		//TODO:check that : is erased
		str.erase(0, jsonObjectName.length() + 1);

		removeWhitespacesFromBothSides(str);

		int otherBracketPos;
		string value;

		switch (str[0])
		{
		case '"':
			
			str.erase(0, 1);

			loadLeafObjectValue();
			//TODO handle leaf object type

			break;
		case '[':
			//TODO multiple object
			//count [ before first ] then ignore ] that many times and then get position of next one ] (care for repeating of [ again)
			//use counter = 1 of {}, for every { +1 and for every } -1, do this untill counter = 0, because that is our } otherwise throw exception
			otherBracketPos = getOtherBracketPos('[', ']', str);

			type = JsonObjectType::NODE;
			break;
		case '{':
			//TODO single
			//count { before first } then ignore } that many times and then get position of next one } (care for repeating of { again)
			otherBracketPos = getOtherBracketPos('{', '}', str);
			
			type = JsonObjectType::NODE;
			break;
		default:
			throw new exception(string("Invalid format, expected one of: \", [, {, instead got: \"" + str.substr(1) + "\" in ..." + str.substr(20) + "...").c_str());
			break;
		}

		//TODO
	}
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

JsonObject JsonSerializer::loadLeafObjectValue(JsonObject& parent, string name, string& str)
{
	JsonObject jso = JsonObject(JsonObjectType::LEAF);
	int endPos = str.find_first_of("\"");

	jso.setData(str.substr(endPos));
	parent.addSubObject(name, jso);

	str.erase(0, jso.getData().lenght());

	return jso;
}


