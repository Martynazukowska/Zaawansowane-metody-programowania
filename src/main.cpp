#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"

#include "LibInterface.hh"

using namespace std;


int main()
{
  // void *pLibHnd_Move = dlopen("libInterp4Move.so",RTLD_LAZY);
  // Interp4Command *(*pCreateCmd_Move)(void);
  // void *pFun;

  // if (!pLibHnd_Move) {
  //   cerr << "!!! Brak biblioteki: Interp4Move.so" << endl;
  //   return 1;
  // }


  // pFun = dlsym(pLibHnd_Move,"CreateCmd");
  // if (!pFun) {
  //   cerr << "!!! Nie znaleziono funkcji CreateCmd" << endl;
  //   return 1;
  // }
  // pCreateCmd_Move = *reinterpret_cast<Interp4Command* (**)(void)>(&pFun);

  LibInterface pierwszy("libInterp4Move.so", wolny);
  pierwszy.CreateCmd("CreateCmd");

  // Interp4Command *pCmd = pCreateCmd_Move();

  // cout << endl;
  // cout << pCmd->GetCmdName() << endl;
  // cout << endl;
  // pCmd->PrintSyntax();
  // cout << endl;
  // pCmd->PrintCmd();
  // cout << endl;

  cout<<endl;
  cout<<"START"<<endl;
  cout<<pierwszy.get_Cmd()->GetCmdName();
  
  cout<<endl;
  pierwszy.get_Cmd()->PrintSyntax();
  cout<<endl;
  pierwszy.get_Cmd()->PrintCmd();
  
  // delete pCmd;

  // dlclose(pLibHnd_Move);

}
