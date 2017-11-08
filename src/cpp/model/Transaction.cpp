#include "../../h/model/Transaction.h"
#include "../../h/utils/SafeConvertor.h"

/*
Before migration to classes...

int type;
long version;
long time_stamp;
long deadline;
long fee;

typedef struct key_pair {
long long private_key;
string public_key;
} key_pair;

typedef struct address {
string encoded; // base-32 encoded address
string public_key;
bool is_valid;
} address;

typedef struct sender {
key_pair key_pair;
address address;
} sender;

typedef struct signer {
key_pair key_pair;
address address;
} signer;

typedef struct signature {
string r;
string s;
} signature;
*/

Transaction::Transaction() {}

Transaction::~Transaction() {}

bool Transaction::setTimestamp(double timestamp) {
	time_t tmp_t = SafeConvertor::toTime(timestamp);
	if (isTimestampValid(tmp_t)) {
		this->timestamp = tmp_t;
		return true;
	}
	return false;
}
time_t Transaction::getTimestamp() {
	return this->timestamp;
}
bool Transaction::isTimestampValid(time_t timestamp) {
	// TODO: Do not validate against UNIX epoch, use number of seconds since NEM nemesis block creation as "NEM epoch".
	if (timestamp > time(NULL)-NEM_NEMESIS_EPOCH) {
		return false;
	}
	return true;
}

bool Transaction::setAmount(double amount) {
	long long tmp = SafeConvertor::toLong(amount);
	if (isAmountValid(tmp)) {
		this->amount = tmp;
		return true;
	}
	return false;
}
long long Transaction::getAmount() {
	return this->amount;
}
bool Transaction::isAmountValid(long long amount) {
	if (amount < 0) {
		return false;
	}
	return true;
}

bool Transaction::setSignature(Signature signature) {
	if (signature.isValid()) {
		this->signature = signature;
		return true;
	}
	return false;
}
Signature Transaction::getSignature() {
	return this->signature;
}

bool Transaction::setFee(double fee) {
	int tmp = SafeConvertor::toInt(fee);
	if (isFeeValid(tmp)) {
		this->fee = tmp;
		return true;
	}
	return false;
}
int Transaction::getFee() {
	return this->fee;
}
bool Transaction::isFeeValid(int fee) {
	//TODO: Much more to be calculated: https://bob.nem.ninja/docs/#transaction-fees
	if (fee < 1) {
		return false;
	}
	return true;
}

bool Transaction::setRecipient(Key recipient) {
	if (recipient.isValid()) {
		this->recipient = recipient;
		return true;
	}
	return false;
}
Key Transaction::getRecipient() {
	return this->recipient;
}

bool Transaction::setType(double type) {
	int tmp = SafeConvertor::toInt(type);
	if (isTypeValid(tmp)) {
		this->type = tmp;
		return true;
	}
	return false;
}
int Transaction::getType() {
	return this->type;
}
bool Transaction::isTypeValid(int type) {
	/*
	0x101: Transfer of NEM from sender to recipient.
	0x801: Transfer of importance from sender to remote account.
	0x1001: An aggregate modification transaction, which converts a normal account into a multisig account.
	0x1002: A multisig signature transaction which is used to sign a multisig transaction.
	0x1003: A multisig transaction, which is used for multisig accounts.
	*/
	if (type == 0x101 || type == 0x801 || type == 0x1001 || type == 0x1002 || type == 0x1003) {
		return true;
	}
	return false;
}

bool Transaction::setDeadline(double deadline) {
	time_t tmp_t = SafeConvertor::toTime(deadline);
	if (isDeadlineValid(tmp_t)) {
		this->deadline = tmp_t;
		return true;
	}
	return false;
}
time_t Transaction::getDeadline() {
	return this->deadline;
}
bool Transaction::isDeadlineValid(time_t deadline) {
	// The deadline of the transaction. The deadline is given as the number of seconds elapsed since the creation of the nemesis block.
	// If a transaction does not get included in a block before the deadline is reached, it is deleted. 
	// @See: https://bob.nem.ninja/docs/#transaction-objects

	// TODO: Well, the transaction might be overdue, but does it mean the block is invalid?
	/*time_t now = time(NULL) - NEM_NEMESIS_EPOCH;
	if (deadline < now) {
		return false;
	}*/
	// But it could not have been before the NEM epoch...
	if (deadline < 1) {
		return false;
	}
	return true;
}

bool Transaction::setMessagePayload(string messagePayload) {
	if (isMessagePayloadValid(messagePayload)) {
		this->messagePayload = messagePayload;
		return true;
	}
	return false;
}
string Transaction::getMessagePayload() {
	return this->messagePayload;
}
bool Transaction::isMessagePayloadValid(string messagePayload) {
	// Optional field in case the transaction contains a message.The payload is the actual(possibly encrypted) message data.
	// The payload is allowed to have a maximal size of 512 bytes.Transaction validation detects if the limit is exceeded 
	// and returns an error in this case.
	// @See: https://bob.nem.ninja/docs/#transfer-transaction
	if (messagePayload.length() <= 512) {
		return true;
	}
	return false;
}

bool Transaction::setMessageType(double messageType) {
	int tmp = SafeConvertor::toInt(messageType);
	if (isMessageTypeValid(tmp)) {
		this->messageType = tmp;
		return true;
	}
	return false;
}
int Transaction::getMessageType() {
	return this->messageType;
}
bool Transaction::isMessageTypeValid(int messageType) {
	if (messageType == 1 || messageType == 2) {
		return true;
	}
	return false;
}

bool Transaction::setVersion(double version) {
	int tmp = SafeConvertor::toInt(version);
	if (isVersionValid(tmp)) {
		this->version = tmp;
		return true;
	}
	return false;
}
int Transaction::getVersion() {
	return this->version;
}
bool Transaction::isVersionValid(int version) {
	// Network versions:
	//  0x68 << 24 + 1 (1744830465 as 4 byte integer) : the main network version
	//  0x98 << 24 + 1 (-1744830463 as 4 byte integer) : the test network version
	// Transaction version:
	//  0x01
	//  0x02
	if (version == ((0x68 << 24) + 1) || version == ((0x98 << 24) + 1) || version == ((0x68 << 24) + 2) || version == ((0x98 << 24) + 2)) {
		return true;
	}
	return false;
}

bool Transaction::setSigner(Key signer) {
	if (signer.isValid()) {
		this->signer = signer;
		return true;

	}
	return false;
}
Key Transaction::getSigner() {
	return this->signer;
}

bool Transaction::setMosaics(std::list<Mosaic> mosaics) {
	for each (Mosaic mosaic in this->mosaics) {
		if (!mosaic.isValid()) {
			return false;
		}
	}
	this->mosaics = mosaics;
	return true;
}
Key Transaction::getMosaics() {
	return this->signer;
}


bool Transaction::isValid() {
	for each (Mosaic mosaic in this->mosaics) {
		if (!mosaic.isValid()) {
			return false;
		}
	}
	return  isTimestampValid(this->timestamp) &&
		isAmountValid(this->amount) &&
		this->signature.isValid() &&
		isFeeValid(this->fee) &&
		this->recipient.isValid() &&
		isTypeValid(this->type) &&
		isDeadlineValid(this->deadline) &&
		isMessagePayloadValid(this->messagePayload) &&
		isMessageTypeValid(this->messageType) &&
		isVersionValid(this->version) &&
		this->signer.isValid();
}
