#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"

#include "LibInterface.hh"

#include <cstdio>
#include <sstream>
#define LINE 500

using namespace std;

bool ExecProcesor(const char *NazwaPliku,istringstream &IStrm4Cmds)
{
  string Cmd4Preproc="cpp -P";
  char Line[LINE];
  ostringstream OTmpStrm;

  Cmd4Preproc+=NazwaPliku;
  FILE*pProc=popen(Cmd4Preproc.c_str(),"r");

  if(!pProc)return false;

  while(fgets(Line,LINE,pProc))
  {
    OTmpStrm<<Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc)==0;
}



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

  LibInterface move("libInterp4Move.so", wolny);

  LibInterface rotate("libInterp4Rotate.so", wolny);

  LibInterface set("libInterp4Set.so", wolny);

  LibInterface pause("libInterp4Pause.so", wolny);
 
  
  move.CreateCmd();
  rotate.CreateCmd();
  set.CreateCmd();
  pause.CreateCmd();




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

  cout<<move.get_Cmd()->GetCmdName();
  cout<<endl;
  move.get_Cmd()->PrintSyntax();
  cout<<endl;
  move.get_Cmd()->PrintCmd();

  cout<<rotate.get_Cmd()->GetCmdName();
  cout<<endl;
  rotate.get_Cmd()->PrintSyntax();
  cout<<endl;
  rotate.get_Cmd()->PrintCmd();

  cout<<set.get_Cmd()->GetCmdName();
  cout<<endl;
  set.get_Cmd()->PrintSyntax();
  cout<<endl;
  set.get_Cmd()->PrintCmd();

  cout<<pause.get_Cmd()->GetCmdName();
  cout<<endl;
  pause.get_Cmd()->PrintSyntax();
  cout<<endl;
  pause.get_Cmd()->PrintCmd();
  
  // delete pCmd;

  // dlclose(pLibHnd_Move);

}
