#pragma once

#include <iostream>
#include <chrono>

#include "../../BaseImpl.h"

class OddCached : public BaseImpl {
    bool check_if_magic(const char *square);
};
