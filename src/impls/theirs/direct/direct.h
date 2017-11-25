#pragma once

#include <iostream>
#include <chrono>

#include "../../BaseImpl.h"

class Direct : public BaseImpl {
    bool check_if_magic(const std::string& square);
};
