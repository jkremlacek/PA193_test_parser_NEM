#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/h/utils/SafeConvertor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(SafeConvertorUnitTest) {
public:
		TEST_METHOD(toInt_Valid_Test) {
			double d = 100;

			Assert::AreEqual(100, SafeConvertor::toInt(d));
		}

		TEST_METHOD(toInt_Invalid_Test) {
			double d = 100.1001;

			Assert::ExpectException<std::exception>([&]
			{
				SafeConvertor::toInt(d);
			});
		}

		TEST_METHOD(toTime_Valid_Test) {
			double d = 100;

			Assert::IsTrue(time_t(100) == SafeConvertor::toTime(d));
		}

		TEST_METHOD(toTime_Invalid_Test) {
			double d = 100.1001;

			Assert::ExpectException<std::exception>([&]
			{
				SafeConvertor::toTime(d);
			});
		}
	};
}
