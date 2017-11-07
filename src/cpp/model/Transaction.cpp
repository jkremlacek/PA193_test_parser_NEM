#include "..\..\h\model\Transaction.h"


Transaction::Transaction()
{
}


Transaction::~Transaction()
{
}

bool Transaction::setTimestamp(double timestamp)
{
	return true;
}

bool Transaction::setAmount(double amount)
{
	return true;
}

bool Transaction::setSignature(Signature signature)
{
	return true;
}

bool Transaction::setFee(double fee)
{
	return true;
}

bool Transaction::setRecipient(Key recipient)
{
	return true;
}

bool Transaction::setType(double type)
{
	return true;
}

bool Transaction::setDeadline(double deadline)
{
	return true;
}

bool Transaction::setMessagePayload(string messagePayload)
{
	return true;
}

bool Transaction::setMessageType(double messageType)
{
	return true;
}

bool Transaction::setVersion(double version)
{
	return true;
}

bool Transaction::setSigner(Key signer)
{
	return true;
}

bool Transaction::isValid() {
	//TODO: implement validation
	return true;
}