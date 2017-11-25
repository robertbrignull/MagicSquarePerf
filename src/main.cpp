#include <iostream>
#include <chrono>

#include "impls/BaseImpl.h"
#include "impls/theirs/direct/direct.h"

/*
 * This generates all possible combinations
 * of 1-9 digits that may or may not
 * form a magic square
 */
static char buffer[] = "111111111";
void generate_or_check(BaseImpl *impl) {
    for (int s = 0; s < 387420489; s++) {
        if (impl->check_if_magic(buffer))
            std::cout << buffer << " ";

        buffer[8]++;
        for (int i = 8; i >= 0 && buffer[i] > '9'; i--) {
            buffer[i] = '1';
            buffer[i - 1]++;
        }
    }
}

void test(BaseImpl *impl) {
    auto start = std::chrono::system_clock::now();
    generate_or_check(impl);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double>
            difference = end - start;
    std::cout << difference.count() << "\n\n";
    delete impl;
}

int main() {
    test(new Direct());
}
