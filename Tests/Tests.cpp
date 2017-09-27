#pragma once
#include "stdafx.h"

#define CATCH_CONFIG_MAIN
#include "./catch/catch.hpp"
#include "../src/cpp/dummy.cpp"

TEST_CASE("Factorial testing", "[factorial]") {
	CHECK(1 == 1);
}

TEST_CASE("Dummy testing", "[dummy]") {
	CHECK(2 == getNumberTwo());
}