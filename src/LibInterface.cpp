#include "LibInterface.hh"

LibInterface::LibInterface(const char *LibName, RTLD_mode mode)
{
    _LibHandler = dlopen(LibName, mode);
}

LibInterface::~LibInterface()
{
}