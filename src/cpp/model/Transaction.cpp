#include "..\..\h\model\Transaction.h"


Transaction::Transaction()
{
}


Transaction::~Transaction()
{
}

bool Transaction::setTimestamp(double timestamp)
{
	return false;
}

bool Transaction::setAmount(double amount)
{
	return false;
}

bool Transaction::setSignature(Signature signature)
{
	return false;
}

bool Transaction::setFee(double fee)
{
	return false;
}

bool Transaction::setRecipient(Key recipient)
{
	return false;
}

bool Transaction::setType(double type)
{
	return false;
}

bool Transaction::setDeadline(double deadline)
{
	return false;
}

bool Transaction::setMessagePayload(string messagePayload)
{
	return false;
}

bool Transaction::setMessageType(double messageType)
{
	return false;
}

bool Transaction::setVersion(double version)
{
	return false;
}

bool Transaction::setSigner(Key signer)
{
	return false;
}

bool Transaction::isValid() {
	//TODO: implement validation
	return true;
}