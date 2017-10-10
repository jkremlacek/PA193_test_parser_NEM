#pragma once

#include "stdafx.h"
#include "CppUnitTest.h"

#include "../src/cpp/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			Assert::AreEqual(1, testReturnOne());
		}

	};
}