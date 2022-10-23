#ifndef LIBINTERFACE
#define LIBINTERFACE

#include <string>
#include <dlfcn.h>

#include "Interp4Command.hh"
#include "MobileObj.hh"

//dodatkowe do łatwiejszego inicjowania
enum RTLD_mode {lazy=RTLD_LAZY, now=RTLD_NOW, binding_mask=RTLD_BINDING_MASK, noload=RTLD_NOLOAD, deepbind=RTLD_DEEPBIND};

class LibInterface
{
private:
    void *_LibHandler;
    //cala sciezka gdzie jest
    std::string _CmdName;
    
    Interp4Command *(*_pCreateCmd)(void);
    Interp4Command *_pCmd;
public:
    LibInterface(const char *LibName, RTLD_mode mode);
    ~LibInterface();
    void CreateCmd(const char *CmdName);
    const Interp4Command* get_Cmd() const;
};


#endif