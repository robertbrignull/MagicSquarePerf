#include <cstring>
#include "single_cmp.h"

static int c15 = '5' * 3;
static const int expectedTotals[8] {
        c15, c15, c15, c15, c15, c15, c15, c15
};

static uint_fast64_t ideal_char_map =
        static_cast<uint_fast64_t>(0x1FF) << 49;
static uint_fast64_t char_map_one = 1u;

bool SingleCmp::check_if_magic(const char *sq) {
    int totals[8];

    totals[0] = sq[0] + sq[1] + sq[2];
    totals[1] = sq[3] + sq[4] + sq[5];
    totals[2] = sq[6] + sq[7] + sq[8];

    totals[3] = sq[0] + sq[3] + sq[6];
    totals[4] = sq[1] + sq[4] + sq[7];
    totals[5] = sq[2] + sq[5] + sq[8];

    totals[6] = sq[0] + sq[4] + sq[8];
    totals[7] = sq[2] + sq[4] + sq[6];

    if (memcmp(totals, expectedTotals, sizeof(int) * 8) != 0)
        return false;

    auto char_map = ideal_char_map;
    for(auto i = 0u; i < 9; ++i)
        char_map ^= char_map_one << sq[i];
    return char_map == 0;
}
