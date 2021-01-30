#include <iostream>
#include "solution.h"

int main() {
    inputData input = getInput();
    std::cout << solve(input) << "\n";
    return 0;
}

/*
ab+c.aba.*.bac.+.+* babc

acb..bab.c.*.ab.ba.+.+*a. cbaa
 */
