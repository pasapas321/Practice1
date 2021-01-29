#include <gtest/gtest.h>
#include "solution.h"
#include <vector>

TEST(FunctionsTest, SimpleRegTest) {
    EXPECT_EQ(isSimpleReg('a'), true);
    EXPECT_EQ(isSimpleReg('1'), true);
    EXPECT_EQ(isSimpleReg('2'), false);
    EXPECT_EQ(isSimpleReg('F'), false);
    EXPECT_EQ(isSimpleReg('$'), false);
}

TEST(RegInfoTest, ConstructorTest) {
    RegInfo regular(5);
    EXPECT_EQ(regular.subwordsInfo.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(regular.subwordsInfo[i].size(), 6);
        for (int j = 0; j < 6; ++j) {
            EXPECT_FALSE(regular.subwordsInfo[i][j]);
        }
    }
    EXPECT_EQ(regular.maxCommonSuffix.size(), 5);
}

TEST