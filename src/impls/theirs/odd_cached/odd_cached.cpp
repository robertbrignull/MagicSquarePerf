#include <cstring>

#include "odd_cached.h"

static const char all_magic_squares[8][10] = {
        "816357492", "492357816",
        "618753294", "294753618",
        "834159672", "672159834",
        "438951276", "276951438"
};

bool OddCached::check_if_magic(const char *sq) {
    if ( (sq[0] & 1) != 0 || (sq[1] & 1) == 0
         || (sq[2] & 1) != 0 || (sq[3] & 1) == 0
         || (sq[4] & 1) == 0
         || (sq[5] & 1) == 0 || (sq[6] & 1) != 0
         || (sq[7] & 1) == 0 || (sq[8] & 1) != 0)
        return false;

    for (int i = 0; i < 8; ++i)
        if (memcmp(sq, all_magic_squares[i], 9) == 0)
            return true;

    return false;
}
