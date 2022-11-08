#ifndef LIBINTERFACE
#define LIBINTERFACE

#include <string>
#include <dlfcn.h>
#include <map>

#include "Interp4Command.hh"
#include "MobileObj.hh"

//dodatkowe do łatwiejszego inicjowania
enum RTLD_mode {wolny=RTLD_LAZY, teraz=RTLD_NOW, maska=RTLD_BINDING_MASK, noload=RTLD_NOLOAD, deep=RTLD_DEEPBIND};

class LibInterface
{
private:
    void *_LibHandler;
    std::string _CmdName;
    
    Interp4Command *(*_pCreateCmd)(void);
    Interp4Command *_pCmd=nullptr;
public:
    LibInterface(std::string LibName, RTLD_mode mode);
    ~LibInterface();
    void CreateCmd();
    std::string getCmdName();
    Interp4Command* get_Cmd() const;
};


#endif