#pragma once

#include <iostream>
#include <chrono>

#include "../../BaseImpl.h"

class CompUInt64 : public BaseImpl {
    bool check_if_magic(const char *square);
};
