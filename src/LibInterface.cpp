#include "LibInterface.hh"

LibInterface::LibInterface(std::string LibName, RTLD_mode mode)
{
    _LibHandler = dlopen(LibName.c_str(), mode);

    if(!_LibHandler)
    {
        std::cerr<<"Błąd: nieznaleziona biblioteka "<<LibName<<std::endl;
        exit(1);
    }
     void *pFun = dlsym(_LibHandler, "CreateCmd");
     if (!pFun)
    {
        std::cerr << "Błąd funkcja nie znaleziona: CmdName" << std::endl;
        exit(1);
    }
    _pCreateCmd = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);
    _pCmd = _pCreateCmd();
    _CmdName=_pCmd->GetCmdName();
}

LibInterface::~LibInterface()
{
    dlclose(_LibHandler);

}

void LibInterface::CreateCmd(/*std::string &cmd_name*/)
{

}

std::string LibInterface::getCmdName()
{
    return _CmdName;
}
Interp4Command* LibInterface::get_Cmd() const 
{
    return _pCmd;
}