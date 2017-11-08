#pragma once

#include "CppUnitTest.h"

#include "../src/h/model/Hash.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(HashUnitTest) {

public:
		TEST_METHOD(isValid_Valid_Test1) {
			Hash hash("55bf6da9a1f5fe5baabc8d07dcacc9a9e52abd0fb6081097845952a7e7706ada");
			Assert::IsTrue(hash.isValid());
		}
		TEST_METHOD(isValid_Valid_Test2) {
			Hash hash("0ac445c0eae1324850b4e8c4bb564c7c259b4919f53bba3053c53f649ef97c3e");
			Assert::IsTrue(hash.isValid());
		}
		TEST_METHOD(isValid_Invalid_Test1) {
			Hash hash("55bf6da9a1f5fe5baabc8d07dcacb9a9e52abd0fb6081097845952a7e7706ada");
			Assert::IsFalse(hash.isValid());
		}
		TEST_METHOD(isValid_Invalid_Test2) {
			Hash hash("0ac445c0eae1324850b4e8c4bb564c7c259b49219f53bba3053c53f649ef97c3e");
			Assert::IsFalse(hash.isValid());
		}
		TEST_METHOD(isValid_Invalid_TestEmpty) {
			Hash hash("");
			Assert::IsFalse(hash.isValid());
		}
	};
}