#include "../../h/model/Mosaic.h"
#include "../../h/utils/SafeConvertor.h"

Mosaic::Mosaic() {}

Mosaic::~Mosaic() {}

bool Mosaic::setNamespaceId(string namespaceId) {
	if (isNamespaceIdValid(namespaceId)) {
		this->namespaceId = namespaceId;
		return true;
	}
	return false;
}
string Mosaic::getNamespaceId() {
	return this->namespaceId;
}
bool Mosaic::isNamespaceIdValid(string namespaceId) {
	// fqdn - like limitations
	if (namespaceId.length() <= 256 && namespaceId.length() > 0) {
		return true;
	}
	return false;
}

bool Mosaic::setName(string name) {
	if (isNameValid(name)) {
		this->name = name;
		return true;
	}
	return false;
}
string Mosaic::getName() {
	return this->name;
}
bool Mosaic::isNameValid(string name) {
	if (name.length() <= 512 && name.length() > 0) {
		return true;
	}
	return false;
}

bool Mosaic::setQuantity(double quantity) {
	long long tmp = SafeConvertor::toLong(quantity);
	if (isQuantityValid(tmp)) {
		this->quantity = tmp;
		return true;
	}
	return false;
}
long long Mosaic::getQuantity() {
	return this->quantity;
}
bool Mosaic::isQuantityValid(long long quantity) {
	if (quantity > 0) {
		return true;
	}
	return false;
}

bool Mosaic::isValid() {
	return isQuantityValid(this->quantity) &&
		isNamespaceIdValid(this->namespaceId) &&
		isNameValid(this->name);
}

