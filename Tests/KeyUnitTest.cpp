#pragma once

#include "CppUnitTest.h"
#include "stdafx.h"
#include "../src/h/model/Key.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(KeyUnitTest) {

public:
		TEST_METHOD(isValid_Valid_Test1) {
			Key key("69538810566d0cf539836b8a9c4ddf0de65d8e1ad2e92d146d6ca3f98c41fb18");
			Assert::IsTrue(key.isValid());
		}
		TEST_METHOD(isValid_Valid_Test2) {
			Key key("5a1d78f37f5ad44dfbe54a853fa1b21816dbf98c2d6591c93d47f71b31c9e68c");
			Assert::IsTrue(key.isValid());
		}
		/*TEST_METHOD(isValid_Invalid_Test1) {
			Key key("69538810566d0cf539836b8a9c4ddf6de65d8e1ad2e92d146d6ca3f98c41fb18");
			Assert::IsFalse(key.isValid());
		}
		TEST_METHOD(isValid_Invalid_Test2) {
			Key key("5a1d78f37f5ad44dfbe54a853fa1b218b16dbf98c2d6591c93d47f71b31c9e68c");
			Assert::IsFalse(key.isValid());
		}
		TEST_METHOD(isValid_Invalid_TestEmpty) {
			Key key("");
			Assert::IsFalse(key.isValid());
		}*/
	};
}