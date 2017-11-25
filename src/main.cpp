#include <iostream>
#include <chrono>

#include "impls/BaseImpl.h"
#include "impls/theirs/direct/direct.h"
#include "impls/NullReferenceImpl.h"
#include "impls/theirs/oddity_heuristic/oddity_heuristic.h"
#include "impls/theirs/central_5/central_5.h"
#include "impls/theirs/no_shifts/no_shifts.h"
#include "impls/theirs/pre_cached/pre_cached.h"
#include "impls/theirs/odd_cached/odd_cached.h"

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

double test(
        std::string implName,
        BaseImpl *impl,
        double nullRefTime,
        double directTime)
{
    auto start = std::chrono::system_clock::now();
    int countFound = generate_or_check(impl);
    auto end = std::chrono::system_clock::now();
    delete impl;

    if (countFound != 8) {
        std::cout << implName << ": found " << countFound << " matches\n";
        return 0.0;
    }

    std::chrono::duration<double> differenced = end - start;
    double difference = differenced.count() - nullRefTime;

    std::cout << implName << ": " << difference << "s";

    if (directTime != 0.0) {
        std::cout << " (" << ((int) (100.0 * difference / directTime))
                  << "% of direct impl)";
    }

    std::cout << "\n";
    return difference;
}

int main()
{
    std::chrono::duration<double> nullTimed = doNullRefTest();
    double nullTime = nullTimed.count();
    std::cout << "Reference time: " << nullTime << "s\n";

    double directTime = test("Direct", new Direct(), nullTime, 0.0);

    test("Oddity Heuristic", new OddityHeuristic(), nullTime, directTime);
    test("Central 5", new Central5(), nullTime, directTime);
    test("No Shifts", new NoShifts(), nullTime, directTime);
    test("Pre-cached", new PreCached(), nullTime, directTime);
    test("Odd Heuristic + Caching", new OddCached(), nullTime, directTime);
}
