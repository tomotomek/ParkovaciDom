// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace std;
using namespace ::testing;

#include "riesenie.h"

TEST_F(Test, nacitajParkoviskoZoSuboru) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.nacitajZoSuboru("park.txt");
	char *zoznamSPZ = new char[256];
	std::string temp{ "TT500JK, ZA500JK, BA500JK, BB500JK, PB500JK" };
	ASSERT_EQ(temp, parkovisko.zoznamAut(zoznamSPZ));
	delete[] zoznamSPZ;
}
TEST_F(Test, nacitajParkoviskoZoSuboruAZaparkuj) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.nacitajZoSuboru("park.txt");
	parkovisko.zparkujAuto("LC970GH", "2016:05:07:17:12:06", "Vozickar");
	char *zoznamSPZ = new char[256];
	std::string temp{ "TT500JK, ZA500JK, LC970GH, BA500JK, BB500JK, PB500JK" };
	ASSERT_EQ(temp, parkovisko.zoznamAut(zoznamSPZ));
	delete[] zoznamSPZ;
}
