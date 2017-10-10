#include "..\..\h\serialization\JsonObject.h"

JsonObject::JsonObject(JsonObjectType type) : type(type)
{

}

JsonObject::~JsonObject()
{
}

void JsonObject::setData(std::string data) {
	if (this->type != LEAF)
	{
		throw std::exception("Set data cannot be used on non leaf object type.");
	}
	else {
		this->data = data;
	}
}

std::string JsonObject::getData() {
	if (this->type != LEAF)
	{
		throw std::exception("Get data cannot be used on non leaf object type.");
	}
	else {
		return this->data;
	}
}

void JsonObject::addSubObject(std::string id, JsonObject object) {
	if (this->type != NODE)
	{
		throw std::exception("AddSubObject cannot be used on non node object type.");
	}

	if (id == "") {
		return;
	}

	this->subObjects.insert(std::pair<std::string, JsonObject>(id, object));
}

JsonObject JsonObject::getSubObjectWithId(std::string id) {
	if (this->type != NODE)
	{
		throw std::exception("GetSubObject cannot be used on non node object type.");
	}
	else {
		std::map<std::string, JsonObject>::iterator it = this->subObjects.find(id);

		if (it != this->subObjects.end())
		{
			return this->subObjects.find(id)->second;
		}

		throw std::exception(("Object with id: " + id + " was not found.").c_str());
	}
}

int JsonObject::getSubObjectCount() {
	if (this->type != NODE)
	{
		throw std::exception("GetSubObjectCount cannot be used on non node object type.");
	}
	else {
		return this->subObjects.size();
	}
}

JsonObjectType JsonObject::getType() {
	return this->type;
}

JsonObject JsonObject::createRootObject() {
	JsonObject o = JsonObject(NODE);

	return o;
}