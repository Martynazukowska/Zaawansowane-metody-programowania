#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <fstream>
#include <vector>
#include "Interp4Command.hh"
#include "MobileObj.hh"

#include "LibInterface.hh"

#include "InterfaceVector.hh"
#include "ProgramInterpreter.hh"

#include "testy.hh"

#include <cstdio>
#include <sstream>

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>
#include <list>
#include "Scene.hh"
#include "Dane.hh"
#include "Poczatek.hh"


using namespace std;
using namespace xercesc;
#define LINE 500



int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    cerr << "Za mało argumentów \n";
    exit(-1);
  }

  Poczatek Parserl(argv[1],"config/config.xml");

  if(!Parserl.PoczatekXML())
  {
    return 1;
  }

  istringstream file;
  if(!Parserl.PoczatekCmd(file))
  {
    return 1;
  }


  std::vector<Interp4Command *> wskaznikiCmd;
 
  
  // InterfaceVector Libs;
  // Libs.CreateCmd("Move");
  // Libs.CreateCmd("Rotate");
  // Libs.CreateCmd("Pause");
  // Libs.CreateCmd("Set");

  ProgramInterpreter Szef;

  for(unsigned long int i = 0; i < Parserl.GetConf().GetLibsVector().size(); ++i) 
  {
    Szef.Lib.CreateCmd(Parserl.GetConf().GetLibsVector()[i]);
  }


  Szef.Scena.AddMobileObject(&Parserl.GetConf());

  std::cout << endl << Szef.Scena["Podstawa"]->GetPosition_m() << endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetName()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetAng_Roll_deg()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetAng_Pitch_deg()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetAng_Yaw_deg()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetPosition_m()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetScale()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetShift()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetColor()<<endl;
  // Testy test;
  // test.Czytwanie_wartości_wtyczek();
  // test.Wskazniki_i_wartosci();

  
  // string name;
  // while (!file.eof())
  // {
  //   file >> name;
  //   if (name.length() > 0)
  //   {
  //     wskaznikiCmd.push_back(Libs[name]->get_Cmd());
  //     wskaznikiCmd.back()->ReadParams(file);
  //   }
  // }

  //   int i = 1;
  // for (Interp4Command *cmd : wskaznikiCmd)
  // {
  //   cout << i++ << ". ";
  //   cmd->PrintCmd();
  // }  

}
