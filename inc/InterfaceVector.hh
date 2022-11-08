#ifndef INTERFACE_VECTOR
#define INTERFACE_VECTOR

#include <map>
#include <memory>
#include "LibInterface.hh"

#define STR(x)      #x
#define LIB_Move    "libInterp4Move.so"
#define LIB_Pause   "libInterp4Pause.so"
#define LIB_Rotate  "libInterp4Rotate.so"
#define LIB_Set     "libInterp4Set.so"

#define GET_LIB(CmdName) STR(LIB_##CmdName)

class InterfaceVector
{
private:
    std::map<std::string, std::shared_ptr<LibInterface>> _LibHandlers;
public:
    InterfaceVector();
    ~InterfaceVector();
    void CreateCmd(std::string Cmd);
    std::string GetCmdName(std::string Cmd);
};

#endif