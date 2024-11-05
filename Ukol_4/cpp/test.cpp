#include "gtest/gtest.h"
#include "advent_lod.cpp"

TEST(AdventLod, Naviguj_1)
{
    Lod lod1(0, 0, 'E', 10, 1);
    ASSERT_EQ(379, lod1.naviguj("vstup_1.txt", false));
    Lod lod2(0, 0, 'E', 10, 1);
    ASSERT_EQ(41, lod2.naviguj("vstup_2.txt", false));
    Lod lod3(0, 0, 'E', 10, 1);
    ASSERT_EQ(707, lod3.naviguj("vstup_3.txt", false));
}

TEST(AdventLod, Naviguj_2)
{
    Lod lod1(0, 0, 'E', 10, 1);
    ASSERT_EQ(7085, lod1.naviguj("vstup_1.txt", true));
    Lod lod2(0, 0, 'E', 10, 1);
    ASSERT_EQ(587, lod2.naviguj("vstup_2.txt", true));
    Lod lod3(0, 0, 'E', 10, 1);
    ASSERT_EQ(27542, lod3.naviguj("vstup_3.txt", true));
}