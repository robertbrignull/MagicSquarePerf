#include "central_5.h"

static auto magic_number = '5' * 3;
static auto not_so_magic_number = '5' * 2;
static uint_fast64_t ideal_char_map =
        static_cast<uint_fast64_t>(0x1FF) << 49;
static uint_fast64_t char_map_one = 1u;

bool Central5::check_if_magic(const char *sq) {
    if(sq[4] != '5')
        return false;

    if ((sq[0] + sq[1] + sq[2] != magic_number)
        || (sq[3] + sq[5] != not_so_magic_number)
        || (sq[6] + sq[7] + sq[8] != magic_number)

        || (sq[0] + sq[3] + sq[6] != magic_number)
        || (sq[1] + sq[7] != not_so_magic_number)
        || (sq[2] + sq[5] + sq[8] != magic_number)

        || (sq[0] + sq[8] != not_so_magic_number)
        || (sq[2] + sq[6] != not_so_magic_number))
        return false;

    auto char_map = ideal_char_map;
    for(auto i = 0u; i < 9; ++i)
        char_map ^= char_map_one << sq[i];
    return char_map == 0;
}
