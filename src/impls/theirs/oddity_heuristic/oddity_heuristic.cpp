#include "oddity_heuristic.h"

static auto c15 = '5' * 3;
static uint_fast64_t ideal_char_map =
        static_cast<uint_fast64_t>(0x1FF) << 49;
static uint_fast64_t char_map_one = 1u;

bool OddityHeuristic::check_if_magic(const char *sq) {
    if ( (sq[0] & 1) != 0 || (sq[1] & 1) == 0
         || (sq[2] & 1) != 0 || (sq[3] & 1) == 0
         || (sq[4] & 1) == 0
         || (sq[5] & 1) == 0 || (sq[6] & 1) != 0
         || (sq[7] & 1) == 0 || (sq[8] & 1) != 0)
        return false;

    if ((sq[0] + sq[1] + sq[2] != c15)
        || (sq[3] + sq[4] + sq[5] != c15)
        || (sq[6] + sq[7] + sq[8] != c15)

        || (sq[0] + sq[3] + sq[6] != c15)
        || (sq[1] + sq[4] + sq[7] != c15)
        || (sq[2] + sq[5] + sq[8] != c15)

        || (sq[0] + sq[4] + sq[8] != c15)
        || (sq[2] + sq[4] + sq[6] != c15))
        return false;

    auto char_map = ideal_char_map;
    for(auto i = 0u; i < 9; ++i)
        char_map ^= char_map_one << sq[i];
    return char_map == 0;
}
