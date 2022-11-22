#include "InterfaceVector.hh"


InterfaceVector::InterfaceVector(/* args */)
{
}

InterfaceVector::~InterfaceVector()
{
}

void InterfaceVector::CreateCmd(std::string Cmd)
{
    if (Cmd == "Move")
    {
        std::shared_ptr<LibInterface> LibPlugin = std::make_shared<LibInterface>(LIB_Move, wolny);
        _LibHandlers[Cmd] = LibPlugin;
        _LibHandlers[Cmd]->CreateCmd();
    }
    if (Cmd == "Rotate")
    {
        std::shared_ptr<LibInterface> LibPlugin = std::make_shared<LibInterface>(LIB_Rotate, wolny);
        _LibHandlers[Cmd] = LibPlugin;
        _LibHandlers[Cmd]->CreateCmd();
    }
    if (Cmd == "Pause")
    {
        std::shared_ptr<LibInterface> LibPlugin = std::make_shared<LibInterface>(LIB_Pause, wolny);
        _LibHandlers[Cmd] = LibPlugin;
        _LibHandlers[Cmd]->CreateCmd();
    }
    if (Cmd == "Set")
    {
        std::shared_ptr<LibInterface> LibPlugin = std::make_shared<LibInterface>(LIB_Set, wolny);
        _LibHandlers[Cmd] = LibPlugin;
        _LibHandlers[Cmd]->CreateCmd();
    }
    const char* name = Cmd.c_str();
    std::shared_ptr<LibInterface> tmp = std::make_shared<LibInterface>(name,wolny);
    _LibHandlers[tmp->getCmdName()] = tmp;

}


std::shared_ptr<LibInterface> InterfaceVector::operator [] (std::string Cmd)
{
    return _LibHandlers[Cmd];
}