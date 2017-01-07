// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

using namespace std;
using namespace ::testing;

#include "riesenie.h"

TEST_F(Test, vyparkujAutoVcas) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.zparkujAuto("BA500RH", "2017:01:06:12:26:57", "Vsetci");
	ASSERT_EQ(0, parkovisko.vyparkujAuto("BA500RH", "2017:01:06:13:26:57"));
}
TEST_F(Test, vyparkujAutoNeskoroVDen) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.zparkujAuto("BA500RH", "2017:01:06:12:26:57", "Vsetci");
	ASSERT_EQ(3 , parkovisko.vyparkujAuto("BA500RH", "2017:01:06:15:26:57"));
}
TEST_F(Test, vyparkujAutoNeskoroDruhyDen) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.zparkujAuto("BA500RH", "2017:01:06:21:26:57", "Vsetci");
	ASSERT_EQ(3, parkovisko.vyparkujAuto("BA500RH", "2017:01:07:00:26:57"));
}
TEST_F(Test, vyparkujAutoNeskoroDruhyMesiacDen) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.zparkujAuto("BA500RH", "2017:01:31:21:26:57", "Vsetci");
	ASSERT_EQ(3, parkovisko.vyparkujAuto("BA500RH", "2017:02:01:00:26:57"));
}
TEST_F(Test, vyparkujAutoNeskoroDruhyRokMesiacDen) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.zparkujAuto("BA500RH", "2016:12:31:21:26:57", "Vsetci");
	ASSERT_EQ(3, parkovisko.vyparkujAuto("BA500RH", "2017:01:01:00:26:57"));
}
TEST_F(Test, vyparkujAutoORok) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.zparkujAuto("BA500RH", "2016:12:31:21:26:57", "Vsetci");
	ASSERT_EQ(26271, parkovisko.vyparkujAuto("BA500RH", "2017:12:31:21:26:56"));
}
TEST_F(Test, doplatDveZacateHodiny) {
	PARKOVISKO parkovisko(2, 3, 5);
	parkovisko.zparkujAuto("BA500RH", "2016:12:22:10:26:57", "Vsetci");
	ASSERT_EQ(6, parkovisko.vyparkujAuto("BA500RH", "2016:12:22:14:26:58"));
}
