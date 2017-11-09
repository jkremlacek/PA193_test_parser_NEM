#include "../../h/model/Block.h"

Block::Block()
{
}

Block::~Block()
{
}

int Block::getVersion()
{
	return this->version;
}

time_t Block::getTimestamp()
{
	return this->timestamp;
}

Key Block::getSigner()
{
	return this->signer;
}

Signature Block::getSignature()
{
	return this->signature;
}

Hash Block::getPrevBlockHash()
{
	return this->prevBlockHash;
}

int Block::getType()
{
	return this->type;
}

int Block::getHeight()
{
	return this->height;
}

list<Transaction> Block::getTransactions()
{
	return this->transactions;
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

void Block::setSignature(Signature signature)
{
	this->signature = signature;
}

void Block::setPrevBlockHash(Hash hash)
{
	this->prevBlockHash = hash;
}

void Block::setSigner(Key key)
{
	this->signer = key;
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
		//this->version == 1 &&
		//TODO: validate timestamp
		this->signature.isValid() &&
		this->prevBlockHash.isValid() &&
		this->signer.isValid() &&
		//TODO: define which block height is valid
		transactionsValidResult;
}

bool Block::isValid(Block prevBlock) {
	bool transactionsValidResult = true;

	for each (Transaction t in this->transactions)
	{
		transactionsValidResult = transactionsValidResult && t.isValid();
	}

	return
		//TODO: define which block versions are allowed
		//this->version == 1 &&
		//TODO: validate timestamp
		this->signature.isValid() &&
		this->prevBlockHash.isValid() &&
		this->signer.isValid() &&
		//TODO: define which block height is valid
		transactionsValidResult;
}
