#pragma once

#include <time.h>

#include "Validatable.h"
#include "Signature.h"
#include "Key.h"
#include "Mosaic.h"
#include <list>
#include <iostream>

#define NEM_NEMESIS_EPOCH 1427587585

#define TRANSFER 0x101
#define TRANSFER_OF_IMPORTANCE 0x801
#define AGGREGATE_MODIFICATION_TRANSACTION 0x1001
#define MULTISIG_SIGNATURE_TRANSACTION 0x1002
#define MULTISIG_TRANSACTION 0x1003

using namespace std;

/*
Doc source: https://bob.nem.ninja/docs/
*/
class Transaction : public Validatable
{
	/*
	The number of seconds elapsed since the creation of the nemesis block. Future timestamps are not allowed.
	Transaction validation detects future timestamps and returns an error in that case.
	*/
	time_t timestamp = NULL;
	long long amount = LLONG_MIN;
	Signature signature;
	int fee = INT_MIN;
	Key recipient;
	int type = INT_MIN;
	time_t deadline = NULL;
	string messagePayload;
	int messageType = INT_MIN;
	int version = INT_MIN;
	Key signer;
	std::list<Mosaic> mosaics;

public:
	Transaction();
	~Transaction();

	bool isAmountValid(long long amount);
	bool isTypeValid(int type);
	bool isTimestampValid(time_t timestamp);
	bool isFeeValid(int fee);
	bool isDeadlineValid(time_t deadline);
	bool isMessagePayloadValid(string messagePayload);
	bool isMessageTypeValid(int messageType);
	bool isVersionValid(int version);
	bool isSignatureValid(Signature signature);

	bool setTimestamp(double timestamp);
	time_t getTimestamp();
	bool setAmount(double amount);
	long long getAmount();
	bool setSignature(Signature signature);
	Signature getSignature();
	bool setFee(double fee);
	int getFee();
	bool setRecipient(Key recipient);
	Key getRecipient();
	bool setType(double type);
	int getType();
	bool setDeadline(double deadline);
	time_t getDeadline();
	bool setMessagePayload(string messagePayload);
	string getMessagePayload();
	bool setMessageType(double messageType);
	int getMessageType();
	bool setVersion(double version);
	int getVersion();
	bool setSigner(Key signer);
	Key getSigner();
	bool setMosaics(std::list<Mosaic> mosaics);
	Key getMosaics();

	bool isValid() override;

};

