#include <iostream>
#include <chrono>

#include "impls/BaseImpl.h"
#include "impls/theirs/direct/direct.h"
#include "impls/NullReferenceImpl.h"

/*
 * This generates all possible combinations
 * of 1-9 digits that may or may not
 * form a magic square
 */
static char buffer[] = "111111111";
int generate_or_check(BaseImpl *impl)
{
    int countFound = 0;
    for (int s = 0; s < 387420489; s++) {
        if (impl->check_if_magic(buffer))
            countFound++;

        buffer[8]++;
        for (int i = 8; i >= 0 && buffer[i] > '9'; i--) {
            buffer[i] = '1';
            buffer[i - 1]++;
        }
    }
    return countFound;
}

std::chrono::duration<double> doNullRefTest() {
    auto start = std::chrono::system_clock::now();
    generate_or_check(new NullReferenceImpl());
    auto end = std::chrono::system_clock::now();
    return end - start;
}

void test(
        std::string implName,
        BaseImpl *impl,
        std::chrono::duration<double> nullRefTime)
{
    auto start = std::chrono::system_clock::now();
    int countFound = generate_or_check(impl);
    auto end = std::chrono::system_clock::now();
    delete impl;

    std::chrono::duration<double> difference = end - start;

    std::cout << implName << ": "
              <<(difference.count() - nullRefTime.count()) << "s "
              << "found " << countFound << " matches\n";
}

int main()
{
    std::chrono::duration<double> nullTime = doNullRefTest();
    std::cout << "Reference time: " << nullTime.count() << "s\n";

    test("Direct", new Direct(), nullTime);
}
