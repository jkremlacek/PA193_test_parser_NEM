#include "../../h/model/Block.h"

Block::Block()
{
}

Block::~Block()
{
}

bool Block::setVersion(double version)
{
	try
	{
		this->version = SafeConvertor::toInt(version);
	}
	catch (const std::exception&)
	{
		return false;
	}
	
	return true;
}

bool Block::setTimestamp(double timestamp)
{
	try
	{
		this->timestamp = SafeConvertor::toTime(timestamp);
	}
	catch (const std::exception&) 
	{
		return false;
	}

	return true;
}

void Block::setHarversterKey(Key key)
{
	this->harvesterKey = key;
}

void Block::setSignature(Signature signature)
{
	this->signature = signature;
}

void Block::setPrevBlockHash(Hash hash)
{
	this->prevBlockHash = hash;
}

void Block::setGenerationHash(Hash hash)
{
	this->generationHash = hash;
}

bool Block::setType(double type)
{
	try
	{
		this->type = SafeConvertor::toInt(type);
	}
	catch (const std::exception&)
	{
		return false;
	}

	return true;
}

bool Block::setHeight(double height)
{
	try
	{
		this->height = SafeConvertor::toInt(height);
	}
	catch (const std::exception&)
	{
		return false;
	}

	return true;
}

void Block::addTransaction(Transaction transaction)
{
	this->transactions.push_back(transaction);
}

bool Block::isValid() {
	bool transactionsValidResult = true;

	for each (Transaction t in this->transactions)
	{
		transactionsValidResult = transactionsValidResult && t.isValid();
	}

	return
		//TODO: define which block versions are allowed
		this->version == 1 &&
		//TODO: validate timestamp
		this->harvesterKey.isValid() &&
		this->signature.isValid() &&
		this->prevBlockHash.isValid() &&
		this->generationHash.isValid() &&
		//TODO: define which block height is valid
		transactionsValidResult;
}
