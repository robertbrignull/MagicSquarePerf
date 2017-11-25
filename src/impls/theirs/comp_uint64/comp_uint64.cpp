#include "comp_uint64.h"

static const uint64_t magic_numbers[] {
        3545515123101087289, 3690191062107239479,
        3544956562637535289, 3978984379655991859,
        3689073941180135479, 4123101758198592049,
        3977867258728887859, 4122543197735040049
};

bool CompUInt64::check_if_magic(const char *sq) {
    if(sq[4] != '5')
        return false;

    uint64_t magic_number = *((uint32_t*) (sq));
    magic_number <<= 32;
    magic_number += *((uint32_t*) (sq+5));

    for(auto i = 0u; i < 8; ++i)
        if(magic_number == magic_numbers[i])
            return true;
    return false;
}
