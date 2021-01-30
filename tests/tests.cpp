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

TEST(RegInfoTest, getAnsTest) {
    RegInfo reg1(10);
    EXPECT_EQ(reg1.getAns(), 0);
    RegInfo reg2(6);
    EXPECT_FALSE(reg2.getAns() != 0);
}

TEST(RegOperations, MakeBaseRegTest) {
    RegInfo reg1 = MakeBaseReg('a', "babc");
    EXPECT_EQ(reg1.isEpsRecognized, false);
    EXPECT_EQ(reg1.subwordsInfo[0][2], false);
    EXPECT_EQ(reg1.subwordsInfo[1][2], true);
    EXPECT_EQ(reg1.subwordsInfo[2][3], false);
    EXPECT_EQ(reg1.maxCommonSuffix[0], 0);
    EXPECT_EQ(reg1.maxCommonSuffix[1], 1);

    RegInfo reg2 = MakeBaseReg('1', "bbbac");
    EXPECT_EQ(reg2.isEpsRecognized, true);
    EXPECT_EQ(reg2.subwordsInfo[1][3], false);
    EXPECT_EQ(reg2.subwordsInfo[2][4], false);
    EXPECT_EQ(reg2.maxCommonSuffix[3], 0);
}

TEST(RegOperations, MulPlusStarTest) {
    RegInfo reg1 = MakeBaseReg('a', "acb");
    RegInfo reg2 = MakeBaseReg('b', "acb");
    RegInfo reg3 = MakeBaseReg('c', "acb");
    RegInfo reg4 = PlusRegs(reg2, reg3);

    EXPECT_EQ(reg4.isEpsRecognized, false);
    EXPECT_EQ(reg4.subwordsInfo[1][3], false);
    EXPECT_EQ(reg4.subwordsInfo[1][2], true);
    EXPECT_EQ(reg4.maxCommonSuffix[0], 0);
    EXPECT_EQ(reg4.maxCommonSuffix[1], 1);

    RegInfo reg5 = KleeneStar(reg4);
    EXPECT_EQ(reg5.isEpsRecognized, true);
    EXPECT_EQ(reg5.subwordsInfo[1][3], true);
    EXPECT_EQ(reg5.subwordsInfo[0][2], false);
    EXPECT_EQ(reg5.maxCommonSuffix[2], 2);
    EXPECT_EQ(reg5.maxCommonSuffix[0], 0);

    RegInfo reg6 = MulRegs(reg1, reg5);
    EXPECT_EQ(reg6.isEpsRecognized, false);
    EXPECT_EQ(reg6.subwordsInfo[0][1], true);
    EXPECT_EQ(reg6.subwordsInfo[0][2], true);
    EXPECT_EQ(reg6.maxCommonSuffix[1], 2);
    EXPECT_EQ(reg6.maxCommonSuffix[2], 3);

    RegInfo reg7 = MulRegs(reg6, reg2);
    EXPECT_EQ(reg7.isEpsRecognized, false);
    EXPECT_EQ(reg7.subwordsInfo[0][3], true);
    EXPECT_EQ(reg7.subwordsInfo[0][1], false);
    EXPECT_EQ(reg7.maxCommonSuffix[1], 0);
    EXPECT_EQ(reg7.maxCommonSuffix[2], 3);
}