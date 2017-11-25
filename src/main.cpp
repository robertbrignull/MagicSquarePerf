#include <iostream>
#include <chrono>

#include "impls/BaseImpl.h"
#include "impls/theirs/direct/direct.h"

/*
 * This generates all possible combinations
 * of 1-9 digits that may or may not
 * form a magic square
 */
static std::string buffer = "000000000";
void generate_or_check(BaseImpl *impl, int index_or_check = 8) {
    if(index_or_check == -1){
        if(impl->check_if_magic(buffer))
            std::cout << buffer << " ";
        return;
    }

    for(char i = 1; i < 10; ++i) {
        buffer[index_or_check] = '0' + i;
        generate_or_check(impl, index_or_check-1);
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
