#pragma once
#include <string>
#include <map>

enum JsonObjectType {NODE, LEAF};

class JsonObject
{
private:
	std::string data;
	std::map<std::string, JsonObject> subObjects;
	const JsonObjectType type;

public:
	JsonObject(JsonObjectType type);
	~JsonObject();

	void setData(std::string data);
	std::string getData();


	/*
		discards object if id is empty
	*/
	void addSubObject(std::string id, JsonObject object);
	JsonObject getSubObjectWithId(std::string id);
	int getSubObjectCount();

	JsonObjectType getType();

	static JsonObject createRootObject();
};

