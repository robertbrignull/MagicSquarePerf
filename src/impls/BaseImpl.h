#pragma once

#include <iostream>

class BaseImpl
{
public:
    virtual bool check_if_magic(const char *square) = 0;
};
