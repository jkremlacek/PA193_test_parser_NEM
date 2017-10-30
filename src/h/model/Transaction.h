#pragma once

#include <time.h>

#include "Validatable.h"
#include "Signature.h"
#include "Key.h"
#include "Mosaic.h"
#include <list>

#define NEM_NEMESIS_EPOCH 1427587585

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
	time_t timestamp;
	long long amount;
	Signature signature;
	int fee;
	Key recipient;
	int type;
	time_t deadline;
	string messagePayload;
	int messageType;
	int version;
	Key signer;
	std::list<Mosaic> mosaics;
	//TODO: Mosaic - Mosaic transaction?
	//TODO: Sender - Transfer transaction
	bool isAmountValid(long long amount);
	bool isTypeValid(int type);
	bool isTimestampValid(time_t timestamp);
	bool isFeeValid(int fee);
	bool isDeadlineValid(time_t deadline);
	bool isMessagePayloadValid(string messagePayload);
	bool isMessageTypeValid(int messageType);
	bool isVersionValid(int version);
	bool isMosaicsValid(std::list<Mosaic> mosaics);

public:
	Transaction();
	~Transaction();

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

