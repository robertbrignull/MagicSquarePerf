#pragma once

#include <iostream>
#include <chrono>

#include "../../BaseImpl.h"

class PreCached : public BaseImpl {
    bool check_if_magic(const char *square);
};
