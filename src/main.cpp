#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include "Interp4Command.hh"
#include "MobileObj.hh"

#include "LibInterface.hh"

#include "InterfaceVector.hh"

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

  LibInterface move("libInterp4Move.so", wolny);

  LibInterface rotate("libInterp4Rotate.so", wolny);

  LibInterface set("libInterp4Set.so", wolny);

  LibInterface pause("libInterp4Pause.so", wolny);
 
  
  // move.CreateCmd();
  // rotate.CreateCmd();
  // set.CreateCmd();
  // pause.CreateCmd();

  // cout<<endl;
  // cout<<"START"<<endl;

  // cout<<move.get_Cmd()->GetCmdName();
  // cout<<endl;
  // move.get_Cmd()->PrintSyntax();
  // cout<<endl;
  // move.get_Cmd()->PrintCmd();

  // cout<<rotate.get_Cmd()->GetCmdName();
  // cout<<endl;
  // rotate.get_Cmd()->PrintSyntax();
  // cout<<endl;
  // rotate.get_Cmd()->PrintCmd();

  // cout<<set.get_Cmd()->GetCmdName();
  // cout<<endl;
  // set.get_Cmd()->PrintSyntax();
  // cout<<endl;
  // set.get_Cmd()->PrintCmd();

  // cout<<pause.get_Cmd()->GetCmdName();
  // cout<<endl;
  // pause.get_Cmd()->PrintSyntax();
  // cout<<endl;
  // pause.get_Cmd()->PrintCmd();
  
  InterfaceVector Libs;
  Libs.CreateCmd("Move");
  Libs.CreateCmd("Rotate");
  Libs.CreateCmd("Pause");
  Libs.CreateCmd("Set");

  Interp4Command *wskazik=Libs["Move"]->get_Cmd();
  Interp4Command *wskazik1=Libs["Rotate"]->get_Cmd();
  Interp4Command *wskazik2=Libs["Pause"]->get_Cmd();
  Interp4Command *wskazik3=Libs["Set"]->get_Cmd();



  cout<<endl;
  cout<<Libs["Move"]->getCmdName() <<"\n";
  wskazik->PrintSyntax();
  wskazik->PrintCmd();
  cout<<endl;

  cout<<Libs["Rotate"]->getCmdName()<<"\n";
  wskazik1->PrintSyntax();
  wskazik1->PrintCmd();
  cout<<endl;
  cout<<Libs["Pause"]->getCmdName()<<"\n";
  wskazik2->PrintSyntax();
  wskazik2->PrintCmd();
  cout<<endl;
  cout<<Libs["Set"]->getCmdName()<<"\n";
  wskazik3->PrintSyntax();
  wskazik3->PrintCmd();

}
