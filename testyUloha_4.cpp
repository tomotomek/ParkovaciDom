// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace ::testing;

#include "riesenie.h"

TEST_F(Test, nulovyZoznamAut) {
	PARKOVISKO mojeParkovisko(4, 10, 15);
	ASSERT_EQ("", mojeParkovisko.zoznamAut(nullptr));
}
TEST_F(Test, nulovyZoznamAut2) {
	PARKOVISKO mojeParkovisko(-4, 0, 15);
	char *zoznam = nullptr;
	ASSERT_EQ("", mojeParkovisko.zoznamAut(zoznam));
}
TEST_F(Test, zaparkujAuto) {
	PARKOVISKO parkovisko(2, 3, 5);
	ASSERT_TRUE(parkovisko.zparkujAuto("BA500RH", "2017:01:06:12:26:57", "Vsetci"));
}
TEST_F(Test, zaparkujAuto2) {
	PARKOVISKO parkovisko(2, 3, 5);
	ASSERT_TRUE(parkovisko.zparkujAuto("BA500RH", "2017:01:06:12:26:57", "Vsetci"));
	ASSERT_TRUE(parkovisko.zparkujAuto("BA500RH", "2017:01:06:12:26:57", "Vsetci"));
}
TEST_F(Test, zoznamAut) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.zparkujAuto("BA500JK", "2017:01:06:10:26:57", "Vsetci");
	parkovisko.zparkujAuto("BB500JK", "2017:01:06:11:26:57", "Vsetci");
	parkovisko.zparkujAuto("TT500JK", "2017:01:06:12:26:57", "Vozickar");
	parkovisko.zparkujAuto("ZA500JK", "2017:01:06:13:26:57", "Vozickar");
	parkovisko.zparkujAuto("PB500JK", "2017:01:06:14:26:57", "Vsetci");
	char *zoznamSPZ = new char[256];
	std::string temp{ "TT500JK, ZA500JK, BA500JK, BB500JK, PB500JK" };
	ASSERT_EQ(temp, parkovisko.zoznamAut(zoznamSPZ));
	delete[] zoznamSPZ;
}
TEST_F(Test, zaparkujDoPlneho) {
	PARKOVISKO parkovisko(1, 2, 3);
	parkovisko.zparkujAuto("BA500JK", "2017:01:06:10:26:57", "Vsetci");
	parkovisko.zparkujAuto("BB500JK", "2017:01:06:11:26:57", "Vsetci");
	parkovisko.zparkujAuto("TT500JK", "2017:01:06:12:26:57", "Vozickar");
	parkovisko.zparkujAuto("ZA500JK", "2017:01:06:13:26:57", "Vozickar");
	parkovisko.zparkujAuto("PB500JK", "2017:01:06:14:26:57", "Vsetci");
	parkovisko.zparkujAuto("LC500JK", "2017:01:06:15:26:57", "Vsetci");
	ASSERT_FALSE(parkovisko.zparkujAuto("PD500JK", "2017:01:06:16:26:57", "Vsetci"));
}
TEST_F(Test, zoznamAutPreplnenyVozickar) {
	PARKOVISKO parkovisko(1, 2, 3);
	parkovisko.zparkujAuto("BA500JK", "2017:01:06:10:26:57", "Vsetci");
	parkovisko.zparkujAuto("BB500JK", "2017:01:06:11:26:57", "Vsetci");
	parkovisko.zparkujAuto("TT500JK", "2017:01:06:12:26:57", "Vozickar");
	parkovisko.zparkujAuto("ZA500JK", "2017:01:06:13:26:57", "Vozickar");
	parkovisko.zparkujAuto("PB500JK", "2017:01:06:14:26:57", "Vsetci");
	parkovisko.zparkujAuto("LC500JK", "2017:01:06:15:26:57", "Vozickar");
	char *zoznamSPZ = new char[256];
	std::string temp{ "TT500JK, ZA500JK, BA500JK, BB500JK, PB500JK" };
	ASSERT_EQ(temp, parkovisko.zoznamAut(zoznamSPZ));
	delete[] zoznamSPZ;
}
