#pragma once

#include "CppUnitTest.h"

#include "../src/h/model/Block.h"
#include "../src/h/serialization/JsonSerializer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//JsonSerializer jss;

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
		/*TEST_METHOD(isValid_Valid_Test1) {
			Block block;
			block.setVersion(atof("1744830465"));
			block.setTimestamp(atof("82506976"));
			block.setHarversterKey(Key("69538810566d0cf539836b8a9c4ddf0de65d8e1ad2e92d146d6ca3f98c41fb18"));
			block.setSignature(Signature("082585ed0aff1d6bfd4581d0eddcc9feeb4101488a4f79e1e849df2be12e25947b383ae7b741b17addffe95614a6328ce49bcbb660c070face5d37b81129ad0a"));
			block.setPrevBlockHash(Hash("55bf6da9a1f5fe5baabc8d07dcacc9a9e52abd0fb6081097845952a7e7706ada"));
			block.setType(atof("1"));
			block.setHeight(atof("1362645"));
			Assert::IsTrue(block.isValid());
		}
		TEST_METHOD(isValid_Valid_Test2) {
			Block block;
			block.setVersion(atof("1744830465"));
			block.setTimestamp(atof("82507057"));
			block.setHarversterKey(Key("5a1d78f37f5ad44dfbe54a853fa1b21816dbf98c2d6591c93d47f71b31c9e68c"));
			block.setSignature(Signature("adb8af4498b8ecf0efa6f7bdd04b53ad39bc194ae358e6704547e1ed7c1189642fbf90734b346cb33cf08c10b9e720adf37f681bf729421e1e47e4b8fd30d90f"));
			block.setPrevBlockHash(Hash("0ac445c0eae1324850b4e8c4bb564c7c259b4919f53bba3053c53f649ef97c3e"));
			block.setType(atof("1"));
			block.setHeight(atof("1362646"));
			Assert::IsTrue(block.isValid());
		}*/
	};
}
