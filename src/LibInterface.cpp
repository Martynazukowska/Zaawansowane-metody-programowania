#include "LibInterface.hh"

// dlopen(nazwa_pliku,flaga)
LibInterface::LibInterface(const char *LibName, RTLD_mode mode)
{
    _LibHandler = dlopen(LibName, mode);
    if(!_LibHandler)
    {
        std::cerr<<"Błąd: nieznaleziona biblioteka "<<LibName<<std::endl;
        exit(1);
    }
     void *pFun = dlsym(_LibHandler, "CreateCmd");
}

LibInterface::~LibInterface()
{
    dlclose(_LibHandler);
}

void LibInterface::CreateCmd(const char *CmdName)
{
    void *pFun = dlsym(_LibHandler, CmdName);
    if (!pFun)
    {
        std::cerr << "Błąd funkcja nie znaleziona " << CmdName << std::endl;
        exit(1);
    }
    _pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
    _pCmd = _pCreateCmd();
}

const Interp4Command* LibInterface::get_Cmd() const
{
    return _pCmd;
}