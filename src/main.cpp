#include <iostream>
#include <chrono>
#include <algorithm>

#include "impls/BaseImpl.h"
#include "impls/theirs/direct/direct.h"
#include "impls/NullReferenceImpl.h"
#include "impls/theirs/oddity_heuristic/oddity_heuristic.h"
#include "impls/theirs/central_5/central_5.h"
#include "impls/theirs/no_shifts/no_shifts.h"
#include "impls/theirs/pre_cached/pre_cached.h"
#include "impls/theirs/odd_cached/odd_cached.h"
#include "impls/theirs/comp_uint64/comp_uint64.h"
#include "impls/mine/single_cmp/single_cmp.h"
#include "impls/mine/string_tree/string_tree.h"

/*
 * This generates all possible combinations
 * of 1-9 digits that may or may not
 * form a magic square
 * i.e. each number may appear more than once.
 */
static char comb_buffer[] = "111111111";
int allCombinations(BaseImpl *impl)
{
    int countFound = 0;
    for (int s = 0; s < 387420489; s++) {
        if (impl->check_if_magic(comb_buffer))
            countFound++;

        comb_buffer[8]++;
        for (int i = 8; i >= 0 && comb_buffer[i] > '9'; i--) {
            comb_buffer[i] = '1';
            comb_buffer[i - 1]++;
        }
    }
    return countFound;
}

/*
 * This generates all possible permutations
 * of 1-9 digits that may or may not
 * form a magic square.
 * i.e. each number will appear exactly once.
 */
static char perm_buffer[] = "123456789";
int allPermutations(BaseImpl *impl)
{
    int countFound = 0;
    do {
        if (impl->check_if_magic(perm_buffer))
            countFound++;
    } while ( std::next_permutation(perm_buffer,perm_buffer+9) );
    return countFound;
}

template <typename GenerateAndCheck>
double doNullRefTest(
        GenerateAndCheck generateAndCheck,
        int iterations)
{
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < iterations; i++)
        generateAndCheck(new NullReferenceImpl());
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> differenced = end - start;
    return differenced.count();
}

template <typename GenerateAndCheck>
double test(
        GenerateAndCheck generateAndCheck,
        int iterations,
        std::string implName,
        BaseImpl *impl,
        double nullRefTime,
        double directTime)
{
    int countFound = 0;
    auto start = std::chrono::system_clock::now();
    for (int i = 0; i < iterations; i++)
        countFound += generateAndCheck(impl);
    auto end = std::chrono::system_clock::now();
    delete impl;

    if (countFound != 8 * iterations) {
        std::cout << implName << ": found "
                  << countFound << " matches over "
                  << iterations << " iterations\n";
        return 0.0;
    }

    std::chrono::duration<double> differenced = end - start;
    double difference = differenced.count() - nullRefTime;

    if (directTime != 0.0) {
        std::cout << implName << ": "
                  << ((int) (100.0 * difference / directTime))
                  << "% of direct impl\n";
    }

    return difference;
}

template <typename GenerateAndCheck>
void doAllTests(std::string generateName, GenerateAndCheck generateAndCheck, int iterations)
{
    std::cout << "Starting " << generateName << "\n";

    double nullTime = doNullRefTest(generateAndCheck, iterations);
    double directTime = test(generateAndCheck, iterations, "Direct", new Direct(), nullTime, 0.0);

    std::cout << "\nTheirs:\n";
    test(generateAndCheck, iterations, "Oddity Heuristic", new OddityHeuristic(), nullTime, directTime);
    test(generateAndCheck, iterations, "Central 5", new Central5(), nullTime, directTime);
    test(generateAndCheck, iterations, "No Shifts", new NoShifts(), nullTime, directTime);
    test(generateAndCheck, iterations, "Pre-cached", new PreCached(), nullTime, directTime);
    test(generateAndCheck, iterations, "Odd Heuristic + Caching", new OddCached(), nullTime, directTime);
    test(generateAndCheck, iterations, "Compare with uint64", new CompUInt64(), nullTime, directTime);

    std::cout << "\nMine:\n";
    test(generateAndCheck, iterations, "Direct with single comparison", new SingleCmp(), nullTime, directTime);
    test(generateAndCheck, iterations, "String Tree", new StringTree(), nullTime, directTime);

    std::cout << "\n";
}

int main()
{
    doAllTests("All Combinations", allCombinations, 5);
    doAllTests("All Permutations", allPermutations, 500);
}
