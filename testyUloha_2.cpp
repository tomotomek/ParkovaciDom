// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

using namespace ::testing;

#include "riesenie.h"

TEST_F(Test, TypIzby) {
	PARKOVACIE_MIESTO miesto;
	string tmp = { "Vsetci" };
	ASSERT_EQ(tmp, miesto.getTypMiesta());
}
TEST_F(Test, TypMiestaVozickar) {
	PARKOVACIE_MIESTO miesto;
	miesto.nastavTypMiesta("Vozickar");
	string tmp = { "Vozickar" };
	ASSERT_EQ(tmp, miesto.getTypMiesta());
}
TEST_F(Test, NastahovanieDruheho) {
	PARKOVACIE_MIESTO miesto;
	miesto.zaparkujAuto("BA478AA", "2016:02:03:10:20:38");
	miesto.vyparkujAuto();
	miesto.nastavTypMiesta("Vozickar");
	ASSERT_TRUE(miesto.zaparkujAuto("ZA478AA", "2016:02:03:10:20:38"));
}
