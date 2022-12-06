#include <iostream>
#include <dlfcn.h>
#include <cassert>
#include <fstream>
#include <vector>
#include "Interp4Command.hh"
#include "MobileObj.hh"

#include "LibInterface.hh"

#include "InterfaceVector.hh"

#include "testy.hh"

#include <cstdio>
#include <sstream>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>


#define PORT 6217
#include "Scene.hh"
#include "Dane.hh"
#include "Poczatek.hh"
#include "klient.hh"


using namespace std;
using namespace xercesc;
#define LINE 500

/*!
 * Otwiera połączenie sieciowe
 * \param[out]  rSocket - deskryptor gniazda, poprzez które może być
 *                        realizowana komunikacja sieciowa.
 */
bool OpenConnection(int &rSocket)
{
  struct sockaddr_in  DaneAdSerw;

  bzero((char *)&DaneAdSerw,sizeof(DaneAdSerw));

  DaneAdSerw.sin_family = AF_INET;
  DaneAdSerw.sin_addr.s_addr = inet_addr("127.0.0.1");
  DaneAdSerw.sin_port = htons(PORT);


  rSocket = socket(AF_INET,SOCK_STREAM,0);

  if (rSocket < 0) {
     cerr << "*** Blad otwarcia gniazda." << endl;
     return false;
  }

  if (connect(rSocket,(struct sockaddr*)&DaneAdSerw,sizeof(DaneAdSerw)) < 0)
   {
     cerr << "*** Brak mozliwosci polaczenia do portu: " << PORT << endl;
     return false;
   }
  return true;
}





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

  
  //Parserl.ExecProgram(argv[1]);
  
  std::vector<Interp4Command *> wskaznikiCmd;
  
  
  // InterfaceVector Libs;
  // Libs.CreateCmd("Move");
  // Libs.CreateCmd("Rotate");
  // Libs.CreateCmd("Pause");
  // Libs.CreateCmd("Set");

  //ProgramInterpreter Szef;
  

  for(unsigned long int i = 0; i < Parserl.GetConf().GetLibsVector().size(); ++i) 
  {
    
    Parserl.Lib.CreateCmd(Parserl.GetConf().GetLibsVector()[i]);
   
  }
  
  Parserl.Scena.AddMobileObject(&Parserl.GetConf());
  std::cerr << endl << Parserl.Scena["Ob_A"]->GetPosition_m() << endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetName()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetAng_Roll_deg()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetAng_Pitch_deg()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetAng_Yaw_deg()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetPosition_m()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetScale()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetShift()<<endl;
  std::cerr << Parserl.GetConf().GetObjVector()[0].GetColor()<<endl;

  int pomocna;
  if (!OpenConnection(pomocna)) 
  {
    return 1;
  }

  Parserl.socket.SetSocket(pomocna);


  Send_zwykly(Parserl.socket.GetSocket(),"Clear\n");
  Parserl.SendScene();

  // Testy test;
  // test.Czytwanie_wartości_wtyczek();
  // test.Wskazniki_i_wartosci();

  
  string name;
  while (!file.eof())
  {
    file >> name;
    if (name.length() > 0)
    {
      wskaznikiCmd.push_back(Parserl.Lib[name]->get_Cmd());
      wskaznikiCmd.back()->ReadParams(file);
    }
  }

  wskaznikiCmd.pop_back();

    int i = 1;
  for (Interp4Command *cmd : wskaznikiCmd)
  {
    cmd->ExecCmd(&Parserl.Scena,&Parserl.socket);
  }  
  Send_zwykly(Parserl.socket.GetSocket(),"Close\n");
  close(Parserl.socket.GetSocket());
}
