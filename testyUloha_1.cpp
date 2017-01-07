// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace std;

#include "riesenie.h"

using namespace ::testing;

//Uloha 1.
TEST_F(Test, JednoducheAutoSpz) {
	AUTO car("BA025CC", "2016:12:30:18:55:32");
	string temp{ "BA025CC" };
	ASSERT_EQ(temp, car.spz());
}
TEST_F(Test, JednoducheAutoCas) {
	AUTO car("BA025OC", "2016:12:30:18:55:32");
	string temp{ "2016:12:30:18:55:32" };
	ASSERT_EQ(temp, car.cas());
}
TEST_F(Test, PrazdneParkovacieMiesto) {
	PARKOVACIE_MIESTO miesto;
	ASSERT_FALSE(miesto.getObsadeneMiesto());
}
TEST_F(Test, VyparkujPrazdneParkovacieMiesto) {
	PARKOVACIE_MIESTO miesto;
	ASSERT_FALSE(miesto.vyparkujAuto());
}
TEST_F(Test, PrazdnaSPZ) {
	PARKOVACIE_MIESTO miesto;
	ASSERT_EQ("", miesto.spzAuta());
}
TEST_F(Test, ZaparkujAuto) {
	PARKOVACIE_MIESTO miesto;
	ASSERT_TRUE(miesto.zaparkujAuto("BB843JK", "2016:10:2:51:36:20"));
}
TEST_F(Test, ObsadeneMiesto) {
	PARKOVACIE_MIESTO miesto;
	miesto.zaparkujAuto("BA990KL", "0000:00:00:00:00:00");
	ASSERT_TRUE(miesto.getObsadeneMiesto());
}
TEST_F(Test, VyparkujAuto) {
	PARKOVACIE_MIESTO miesto;
	miesto.zaparkujAuto("BA990KL", "0000:00:00:00:00:00");
	ASSERT_TRUE(miesto.vyparkujAuto());
}
TEST_F(Test, SPZVyparkovanehoAuta) {
	PARKOVACIE_MIESTO miesto;
	miesto.zaparkujAuto("BA990KL", "0000:00:00:00:00:00");
	miesto.vyparkujAuto();
	ASSERT_EQ("", miesto.spzAuta());
}
TEST_F(Test, ObsadenostVyparkovanhoMiesta) {
	PARKOVACIE_MIESTO miesto;
	miesto.zaparkujAuto("BA990KL", "0000:00:00:00:00:00");
	miesto.vyparkujAuto();
	ASSERT_FALSE(miesto.getObsadeneMiesto());
}
TEST_F(Test, CasPrijazdu) {
	PARKOVACIE_MIESTO miesto;
	miesto.zaparkujAuto("BA990KL", "0000:00:00:00:00:00");
	string temp{ "0000:00:00:00:00:00" };
	ASSERT_EQ(temp, miesto.casPrijazdu());
}
