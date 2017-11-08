#pragma once

#include "CppUnitTest.h"

#include "../src/h/model/Signature.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(SignatureUnitTest) {

public:
		TEST_METHOD(isValid_Valid_Test1) {
			Signature signature("082585ed0aff1d6bfd4581d0eddcc9feeb4101488a4f79e1e849df2be12e25947b383ae7b741b17addffe95614a6328ce49bcbb660c070face5d37b81129ad0a");
			Assert::IsTrue(signature.isValid());
		}
		TEST_METHOD(isValid_Valid_Test2) {
			Signature signature("adb8af4498b8ecf0efa6f7bdd04b53ad39bc194ae358e6704547e1ed7c1189642fbf90734b346cb33cf08c10b9e720adf37f681bf729421e1e47e4b8fd30d90f");
			Assert::IsTrue(signature.isValid());
		}
		TEST_METHOD(isValid_Invalid_Test1) {
			Signature signature("082585ed0aff1d6bfd4581d0eddcc9feeb4101488a4f79e1e8a9df2be12e25947b383ae7b741b17addffe95614a6328ce49bcbb660c070face5d37b81129ad0a");
			Assert::IsFalse(signature.isValid());
		}
		TEST_METHOD(isValid_Invalid_Test2) {
			Signature signature("adb8af4498b8ecf0efa6f7bdd04b53ad39bc194ae358e6704547e1ed7c11e89642fbf90734b346cb33cf08c10b9e720adf37f681bf729421e1e47e4b8fd30d90f");
			Assert::IsFalse(signature.isValid());
		}
		TEST_METHOD(isValid_Invalid_TestEmpty) {
			Signature signature("");
			Assert::IsFalse(signature.isValid());
		}
	};
}