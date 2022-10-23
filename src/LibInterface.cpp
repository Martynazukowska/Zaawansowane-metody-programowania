#include "LibInterface.hh"

// dlopen(nazwa_pliku,flaga)
LibInterface::LibInterface(const char *LibName, RTLD_mode mode)
{
    _LibHandler = dlopen(LibName, mode);
     void *pFun = dlsym(_LibHandler, "CreateCmd");
}

LibInterface::~LibInterface()
{
    dlclose(_LibHandler);
}