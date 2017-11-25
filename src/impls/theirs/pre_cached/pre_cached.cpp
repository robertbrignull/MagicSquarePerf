#include <cstring>

#include "pre_cached.h"

static const char all_magic_squares[8][10] = {
        "816357492", "492357816",
        "618753294", "294753618",
        "834159672", "672159834",
        "438951276", "276951438"
};

bool PreCached::check_if_magic(const char *sq) {
    for (int i = 0; i < 8; ++i)
        if (memcmp(sq, all_magic_squares[i], 9) == 0)
            return true;

    return false;
}
