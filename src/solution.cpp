#include "solution.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

RegInfo::RegInfo(int size): isEpsRecognized(false), size(size) {
    subwordsInfo.resize(size, std::vector<bool>(size + 1, false));
    maxCommonSuffix.resize(size, 0);
}

int RegInfo::getAns() const {
    return maxCommonSuffix[size - 1];
}

RegInfo MakeBaseReg(char symbol, const std::string& word) {
    RegInfo result(word.size());
    if (symbol == '1') {
        result.isEpsRecognized = true;
    } else {
        for (int i = 0; i < word.size(); ++i) {
            if (word[i] == symbol) {
                result.subwordsInfo[i][i + 1] = true;
                result.maxCommonSuffix[i] = 1;
            }
        }
    }
    return result;
}

RegInfo PlusRegs(const RegInfo& alpha, const RegInfo& beta) {
    RegInfo result(alpha.size);
    result.isEpsRecognized = alpha.isEpsRecognized || beta.isEpsRecognized;
    for (int l = 0; l < alpha.size; ++l) {
        for (int r = l + 1; r <= alpha.size; ++r) {
            result.subwordsInfo[l][r] = alpha.subwordsInfo[l][r] || beta.subwordsInfo[l][r];
        }
        result.maxCommonSuffix[l] = std::max(alpha.maxCommonSuffix[l], beta.maxCommonSuffix[l]);
    }
    return result;
}

RegInfo MulRegs(const RegInfo& alpha, const RegInfo& beta) {
    RegInfo result(alpha.size);
    result.isEpsRecognized = (alpha.isEpsRecognized && beta.isEpsRecognized);
    for (int l = 0; l < alpha.size; ++l) {
        for (int r = l + 1; r <= alpha.size; ++r) {
            if (alpha.isEpsRecognized && beta.subwordsInfo[l][r]) {
                result.subwordsInfo[l][r] = true;
            } else if (beta.isEpsRecognized && alpha.subwordsInfo[l][r]) {
                result.subwordsInfo[l][r] = true;
            } else {
                for (int k = l + 1; k < r; ++k) {
                    if (alpha.subwordsInfo[l][k] && beta.subwordsInfo[k][r]) {
                        result.subwordsInfo[l][r] = true;
                    }
                }
            }
        }
    }
    for (int l = 0; l < alpha.size; ++l) {
        result.maxCommonSuffix[l] = beta.maxCommonSuffix[l];
        if (beta.isEpsRecognized) {
            result.maxCommonSuffix[l] = std::max(result.maxCommonSuffix[l], alpha.maxCommonSuffix[l]);
        }
        for (int i = 1; i <= l; ++i) {
            if (beta.subwordsInfo[i][l + 1]) {
                result.maxCommonSuffix[l] = std::max(result.maxCommonSuffix[l], l - i + 1 + alpha.maxCommonSuffix[i - 1]);
            }
        }
    }
    return result;
}

RegInfo KleeneStar(const RegInfo& alpha) {
    std::vector<RegInfo> degs(alpha.size + 1);
    degs[0] = RegInfo(alpha.size);
    degs[0].isEpsRecognized = true;
    degs[1] = alpha;
    for (int i = 2; i <= alpha.size; ++i) {
        degs[i] = MulRegs(degs[i - 1], alpha);
    }
    RegInfo result = degs[0];
    for (int i = 1; i < degs.size(); ++i) {
        result = PlusRegs(result, degs[i]);
    }
    return result;
}

bool isSimpleReg(char c) {
    return c == '1' || (c >= 'a' && c <= 'z');
}

std::pair<RegInfo, RegInfo> getTwoArgs(std::stack<RegInfo> &regStack) {
    if (regStack.size() < 2) {
        throw std::invalid_argument("Invalid regular format");
    }
    auto reg2 = regStack.top();
    regStack.pop();
    auto reg1 = regStack.top();
    regStack.pop();
    return {reg1, reg2};
}

inputData getInput() {
    inputData result;
    std::cin >> result.regEx >> result.word;
    return result;
}

int solve(const inputData &input) {
    std::stack<RegInfo> regStack;

    for (char c : input.regEx) {
        if (isSimpleReg(c)) {
            regStack.push(MakeBaseReg(c, input.word));
        } else {
            if (regStack.empty()) {
                throw std::invalid_argument("Invalid regular format");
            }
            if (c == '*') {
                RegInfo reg = regStack.top();
                regStack.pop();
                regStack.push(KleeneStar(reg));
            } else {
                auto [reg1, reg2] = getTwoArgs(regStack);
                if (c == '+') {
                    regStack.push(PlusRegs(reg1, reg2));
                } else {
                    regStack.push(MulRegs(reg1, reg2));
                }
            }
        }
    }
    if (regStack.size() != 1) {
        throw std::invalid_argument("Invalid regular format");
    }
    return regStack.top().getAns();
}