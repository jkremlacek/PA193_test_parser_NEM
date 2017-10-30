#pragma once

#include "CppUnitTest.h"
#include "stdafx.h"
#include "../src/h/model/Transaction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(TransactionUnitTest) {

public:
	TEST_METHOD(setType_Valid_Test) {
		Transaction t = Transaction();
		int types[] = { 0x101, 0x801, 0x1001, 0x1002, 0x1003 };
		for each (int type in types) {
			Assert::IsTrue(t.setType(type));
		}
	}
	TEST_METHOD(setType_Invalid_Test) {
		Transaction t = Transaction();
		double types[] = { 88333333338888888888.3, 103333 };
		for each (int type in types) {
			Assert::IsFalse(t.setType(type));
		}
	}
	TEST_METHOD(setTimestamp_Valid_Test) {
		Transaction t = Transaction();
		Assert::IsTrue(t.setTimestamp((double)time(NULL) - NEM_NEMESIS_EPOCH - 100));
	}
	TEST_METHOD(setTimestamp_Invalid_Test) {
		Transaction t = Transaction();
		// We expect this to be in future...
		Assert::IsFalse(t.setTimestamp((double)time(NULL) - NEM_NEMESIS_EPOCH + 100));
	}
	TEST_METHOD(setFee_Valid_Test) {
		Transaction t = Transaction();
		//TODO: Set alongside with amount and message payload to _calculate_ the fee.
		Assert::IsTrue(t.setFee(2005000000));
	}
	TEST_METHOD(setFee_Invalid_Test) {
		Transaction t = Transaction();
		//TODO: Set alongside with amount and message payload to _calculate_ the fee.
		Assert::IsFalse(t.setFee(-2005000000));
	}
	TEST_METHOD(setDeadline_Valid_Test) {
		Transaction t = Transaction();
		Assert::IsTrue(t.setDeadline(79552321));
	}
	TEST_METHOD(setDeadline_Invalid_Test) {
		Transaction t = Transaction();
		//Assert::IsFalse(t.setDeadline((double)time(NULL) - NEM_NEMESIS_EPOCH - 666));
		Assert::IsFalse(t.setDeadline(-666));
	}
	TEST_METHOD(setMessagePayload_Valid_Test) {
		Transaction t = Transaction();
		Assert::IsTrue(t.setMessagePayload(""));
		Assert::IsTrue(t.setMessagePayload("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	}
	TEST_METHOD(setMessagePayload_Invalid_Test) {
		Transaction t = Transaction();
		Assert::IsFalse(t.setMessagePayload("Xaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	}
	TEST_METHOD(setMessageType_Valid_Test) {
		Transaction t = Transaction();
		Assert::IsTrue(t.setMessageType(1));
		Assert::IsTrue(t.setMessageType(2));
	}
	TEST_METHOD(setMessageType_Invalid_Test) {
		Transaction t = Transaction();
		Assert::IsFalse(t.setMessageType(0));
		Assert::IsFalse(t.setMessageType(-1));
	}
	TEST_METHOD(setVersion_Valid_Test) {
		Transaction t = Transaction();
		Assert::IsTrue(t.setVersion(-1744830463));
		Assert::IsTrue(t.setVersion(-1744830462));
	}
	TEST_METHOD(setVersion_Invalid_Test) {
		Transaction t = Transaction();
		Assert::IsFalse(t.setVersion(-1744830488));
		Assert::IsFalse(t.setVersion(-1244830462));
	}
	};
}
