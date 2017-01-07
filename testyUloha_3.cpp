// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

using namespace ::testing;

#include "riesenie.h"

TEST_F(Test, PARKOVISKO) {
	PARKOVISKO mojeParkovisko(4, 10, 15);
	ASSERT_EQ(600, mojeParkovisko.pocetVsetkychMiest());
}
TEST_F(Test, PrazdneParkovisko) {
	PARKOVISKO mojeParkovisko(4, -4, 5);
	ASSERT_EQ(0, mojeParkovisko.pocetVsetkychMiest());
}
TEST_F(Test, PrazdneParkoivsko0) {
	PARKOVISKO mojeParkovisko(0, 3, 5);
	ASSERT_EQ(0, mojeParkovisko.pocetVsetkychMiest());
}
TEST_F(Test, PocetParkovacichMiest) {
	PARKOVISKO mojeParkovisko(4, 10, 15);
	ASSERT_EQ(560, mojeParkovisko.pocetMiest("Vsetci"));
}
TEST_F(Test, PocetMiestPreVozickarov) {
	PARKOVISKO mojeParkovisko(4, 10, 15);
	ASSERT_EQ(40, mojeParkovisko.pocetMiest("Vozickar"));
}
TEST_F(Test, PocetVolnychMiestPreVozickarov) {
	PARKOVISKO mojeParkovisko(4, 10, 15);
	ASSERT_EQ(40, mojeParkovisko.pocetVolnychMiest("Vozickar"));
}
TEST_F(Test, PocetVolnychApartmanov2) {
	PARKOVISKO mojeParkovisko(1, 10, 15);
	ASSERT_EQ(10,mojeParkovisko.pocetVolnychMiest("Vozickar"));
	PARKOVISKO maleParkovisko(1, 4, 5);
	ASSERT_EQ(4, maleParkovisko.pocetVolnychMiest("Vozickar"));
}
TEST_F(Test, prazdneParkovisko1) {
	PARKOVISKO mojeParkovisko(0, -1, 0);
	ASSERT_EQ(0, mojeParkovisko.pocetVolnychMiest("Vozickar"));
}
