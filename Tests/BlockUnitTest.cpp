#pragma once

#include "CppUnitTest.h"

#include "../src/h/model/Block.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(BlockUnitTest) {
		
public:
		TEST_METHOD(setVersion_Valid_Test) {
			Block b = Block();
			Assert::IsTrue(b.setVersion(1.0));
		}

		TEST_METHOD(setVersion_Invalid_Test) {
			Block b = Block();
			Assert::IsFalse(b.setVersion(1.1));
		}

		TEST_METHOD(setTimestamp_Valid_Test) {
			Block b = Block();
			Assert::IsTrue(b.setTimestamp(79545139));
		}

		TEST_METHOD(setTimestamp_Invalid_Test) {
			Block b = Block();
			Assert::IsFalse(b.setTimestamp(79545139.1));
		}

		TEST_METHOD(setType_Valid_Test) {
			Block b = Block();
			Assert::IsTrue(b.setType(2));
		}

		TEST_METHOD(setType_Invalid_Test) {
			Block b = Block();
			Assert::IsFalse(b.setType(2.2));
		}

		TEST_METHOD(setHeight_Valid_Test) {
			Block b = Block();
			Assert::IsTrue(b.setHeight(1313679));
		}

		TEST_METHOD(setHeight_Invalid_Test) {
			Block b = Block();
			Assert::IsFalse(b.setHeight(1313679.0001));
		}
	};
}
