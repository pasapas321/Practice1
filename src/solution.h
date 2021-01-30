#ifndef SOLUTION_H
#define SOLUTION_H

#include <stack>
#include <string>
#include <vector>

struct RegInfo {
    std::vector<std::vector<bool>> subwordsInfo; //для каждого подотрезка слова u храним информацию о том, распознается ли он регулярным выражением
    std::vector<int> maxCommonSuffix;
    bool isEpsRecognized;
    int size;

    RegInfo() = default;
    RegInfo(int size);

    int getAns() const;
};

RegInfo MulRegs(const RegInfo& alpha, const RegInfo& beta);
RegInfo PlusRegs(const RegInfo& alpha, const RegInfo& beta);
RegInfo KleeneStar(const RegInfo& alpha);
RegInfo MakeBaseReg(char symbol, const std::string& word);

bool isSimpleReg(char c);

struct inputData {
    std::string regEx, word;
};

inputData getInput();

int solve(const inputData &);

#endif
