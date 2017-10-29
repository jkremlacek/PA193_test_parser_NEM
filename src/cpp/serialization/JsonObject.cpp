#include "..\..\h\serialization\JsonObject.h"

void JsonObject::addAttribute(JsonAttribute attr) {
	this->attributes.insert(std::pair<string, JsonAttribute>(attr.getName(), attr));
}

JsonAttribute JsonObject::getAttributeWithId(string id) {
	map<string, JsonAttribute>::iterator it = this->attributes.find(id);

	if (it != this->attributes.end())
	{
		return this->attributes.find(id)->second;
	}

	throw exception(("Object with id: " + id + " was not found.").c_str());
}

int JsonObject::getAttributeCount() {
	return this->attributes.size();
}