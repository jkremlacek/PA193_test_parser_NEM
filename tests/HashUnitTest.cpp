#pragma once

#include "CppUnitTest.h"

#include "../src/h/model/Hash.h"
#include "../src/h/serialization/JsonSerializer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

std::string validBlock1("{\"timeStamp\":82506976,\"signature\":\"082585ed0aff1d6bfd4581d0eddcc9feeb4101488a4f79e1e849df2be12e25947b383ae7b741b17addffe95614a6328ce49bcbb660c070face5d37b81129ad0a\",\"prevBlockHash\":{\"data\":\"55bf6da9a1f5fe5baabc8d07dcacc9a9e52abd0fb6081097845952a7e7706ada\"},\"type\":1,\"transactions\":[{\"timeStamp\":82506941,\"amount\":282000000,\"signature\":\"74220ed037f16fe2acf3e46aca2c8659a783e7cacff0f12c1532528ad8e389b78657dee6033664898bf817846c51e3d9793cf0102b63e6f021dd364aeacfab09\",\"fee\":150000,\"recipient\":\"NBZODY74DU26ZBCAICHIFTXJDGPKKGH7NKJAADVU\",\"mosaics\":[],\"type\":257,\"deadline\":82510541,\"message\":{\"payload\":\"4e6f64652072657761726473207061796f75743a20726f756e6420323732392d32373332\",\"type\":1},\"version\":1744830466,\"signer\":\"d96366cdd47325e816ff86039a6477ef42772a455023ccddae4a0bd5d27b8d23\"}],\"version\":1744830465,\"signer\":\"69538810566d0cf539836b8a9c4ddf0de65d8e1ad2e92d146d6ca3f98c41fb18\",\"height\":1362645}");
std::string validBlock2("{\"timeStamp\":82507057,\"signature\":\"adb8af4498b8ecf0efa6f7bdd04b53ad39bc194ae358e6704547e1ed7c1189642fbf90734b346cb33cf08c10b9e720adf37f681bf729421e1e47e4b8fd30d90f\",\"prevBlockHash\":{\"data\":\"0ac445c0eae1324850b4e8c4bb564c7c259b4919f53bba3053c53f649ef97c3e\"},\"type\":1,\"transactions\":[{\"timeStamp\":82506985,\"amount\":10000000000,\"signature\":\"24ec5d2962d46434f013703aae9946b7909149fd73e1b122147497feb3ca318c799bf42079ffa1331673dc235935f1a71515ee773b5d05c3b3ff52b3f7e9f10a\",\"fee\":150000,\"recipient\":\"NAGJG3QFWYZ37LMI7IQPSGQNYADGSJZGJRD2DIYA\",\"type\":257,\"deadline\":82510585,\"message\":{\"payload\":\"61366237313532623439616434633133\",\"type\":1},\"version\":1744830465,\"signer\":\"e40d7a1c74f173cde9a1d19369da59d53017e799143f969a4e788a6f972016af\"}],\"version\":1744830465,\"signer\":\"5a1d78f37f5ad44dfbe54a853fa1b21816dbf98c2d6591c93d47f71b31c9e68c\",\"height\":1362646}");
std::string invalidBlock1("{\"timeStamp\":82506976,\"signature\":\"082585ed0aff1d6bfd4581d0eddcc9feeb4101488a4f79e1e849df2be12e25947b383ae7b7c1b17addffe95614a6328ce49bcbb660c070face5d37b81129ad0a\",\"prevBlockHash\":{\"data\":\"55bf6da9a1f5fe5baabc8d07dcacc9a9e52abd0fb6081097845952a7e7706ada\"},\"type\":1,\"transactions\":[{\"timeStamp\":82506941,\"amount\":282000000,\"signature\":\"74220ed037f16fe2acf3e46aca2c8659a783e7cacff0f12c1532528ad8e389b78657dee6033664898bf817846c51e3d9793cf0102b63e6f021dd364aeacfab09\",\"fee\":150000,\"recipient\":\"NBZODY74DU26ZBCAICHIFTXJDGPKKGH7NKJAADVU\",\"mosaics\":[],\"type\":257,\"deadline\":82510541,\"message\":{\"payload\":\"4e6f64652072657761726473207061796f75743a20726f756e6420323732392d32373332\",\"type\":1},\"version\":1744830466,\"signer\":\"d96366cdd47325e816ff86039a6477ef42772a455023ccddae4a0bd5d27b8d23\"}],\"version\":1744830465,\"signer\":\"69538810566d0cf539836b8a9c4ddf0de65d8e1ad2e92d146d6ca3f98c41fb18\",\"height\":1362645}");
std::string invalidBlock2("{\"timeStamp\":82507057,\"signature\":\"adb8af4498b8ecf0efa6f7bdd04b53ad39bc194ae358e6704547e1ed7c1189642fbf90b734b346cb33cf08c10b9e720adf37f681bf729421e1e47e4b8fd30d90f\",\"prevBlockHash\":{\"data\":\"0ac445c0eae1324850b4e8c4bb564c7c259b4919f53bba3053c53f649ef97c3e\"},\"type\":1,\"transactions\":[{\"timeStamp\":82506985,\"amount\":10000000000,\"signature\":\"24ec5d2962d46434f013703aae9946b7909149fd73e1b122147497feb3ca318c799bf42079ffa1331673dc235935f1a71515ee773b5d05c3b3ff52b3f7e9f10a\",\"fee\":150000,\"recipient\":\"NAGJG3QFWYZ37LMI7IQPSGQNYADGSJZGJRD2DIYA\",\"type\":257,\"deadline\":82510585,\"message\":{\"payload\":\"61366237313532623439616434633133\",\"type\":1},\"version\":1744830465,\"signer\":\"e40d7a1c74f173cde9a1d19369da59d53017e799143f969a4e788a6f972016af\"}],\"version\":1744830465,\"signer\":\"5a1d78f37f5ad44dfbe54a853fa1b21816dbf98c2d6591c93d47f71b31c9e68c\",\"height\":1362646}");
JsonSerializer jss;

namespace tests
{
	TEST_CLASS(HashUnitTest) {

public:
		TEST_METHOD(isValid_Valid_Test1) {
			JsonObject* jo = jss.fromString(validBlock1).second;
			JsonObject* prevBlockHashJO = jss.getJsonObjectWithId(jo->getAttributeWithId("prevBlockHash").getJsonValueAt(0));
			Hash hash(prevBlockHashJO->getAttributeWithId("data").getTextValue());
			Assert::IsTrue(hash.isValid());
		}
		TEST_METHOD(isValid_Valid_Test2) {
			JsonObject* jo = jss.fromString(validBlock2).second;
			JsonObject* prevBlockHashJO = jss.getJsonObjectWithId(jo->getAttributeWithId("prevBlockHash").getJsonValueAt(0));
			Hash hash(prevBlockHashJO->getAttributeWithId("data").getTextValue());
			Assert::IsTrue(hash.isValid());
		}
		TEST_METHOD(isValid_Invalid_Test1) {
			JsonObject* jo = jss.fromString(invalidBlock1).second;
			JsonObject* prevBlockHashJO = jss.getJsonObjectWithId(jo->getAttributeWithId("prevBlockHash").getJsonValueAt(0));
			Hash hash(prevBlockHashJO->getAttributeWithId("data").getTextValue());
			Assert::IsFalse(hash.isValid());
		}
		TEST_METHOD(isValid_Invalid_Test2) {
			JsonObject* jo = jss.fromString(invalidBlock2).second;
			JsonObject* prevBlockHashJO = jss.getJsonObjectWithId(jo->getAttributeWithId("prevBlockHash").getJsonValueAt(0));
			Hash hash(prevBlockHashJO->getAttributeWithId("data").getTextValue());
			Assert::IsFalse(hash.isValid());
		}
	};
}