#include <array>

#include "no_shifts.h"

static auto magic_number = '5' * 3;
static auto not_so_magic_number = '5' * 2;
static const std::array<uint16_t, 58> bit_shifts {
        0, 0, 0, 0,   0, 0, 0, 0,
        0, 0, 0, 0,   0, 0, 0, 0,
        0, 0, 0, 0,   0, 0, 0, 0,
        0, 0, 0, 0,   0, 0, 0, 0,

        0, 0, 0, 0,   0, 0, 0, 0,
        0, 0, 0, 0,   0, 0, 0, 0,
        0, 1, 2, 4,   8, 16, 32, 64,
        128, 256
};

bool NoShifts::check_if_magic(const char *sq) {
    if ((sq[0] + sq[1] + sq[2] != magic_number)
        || (sq[3] + sq[5] != not_so_magic_number)
        || (sq[6] + sq[7] + sq[8] != magic_number)

        || (sq[0] + sq[3] + sq[6] != magic_number)
        || (sq[1] + sq[7] != not_so_magic_number)
        || (sq[2] + sq[5] + sq[8] != magic_number)

        || (sq[0] + sq[4] + sq[8] != magic_number)
        || (sq[2] + sq[4] + sq[6] != magic_number))
        return false;

    auto char_map = 0u;
    for(auto i = 0u; i < 9; ++i)
        char_map ^= bit_shifts[sq[i]];
    return char_map == 511;
}
