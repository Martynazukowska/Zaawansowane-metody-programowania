#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


/*!
 * \brief Wysyła napis do poprzez gniazdo sieciowe.
 *
 * Wysyła napis do poprzez gniazdo sieciowe.
 * \param[in] Sk2Server - deskryptor gniazda sieciowego, poprzez które 
 *                        ma zostać wysłany napis w sensie języka C.
 * \param[in] sMesg - zawiera napis, który ma zostać wysłany poprzez
 *                    gniazdo sieciowe.
 */
int Send_zwykly(int Sk2Server, const char *sMesg)
{
  ssize_t  IlWyslanych;
  ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

  while ((IlWyslanych = write(Sk2Server,sMesg,IlDoWyslania)) > 0) {
    IlDoWyslania -= IlWyslanych;
    sMesg += IlWyslanych;
  }
  if (IlWyslanych < 0) {
    cerr << "*** Blad przeslania napisu." << endl;
  }
  return 0;
}

extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): obj_name(""),pos_x_m(0),pos_y_m(0),angle_z_deg(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << obj_name << " "<< " " << pos_x_m << " " << pos_y_m << " " << angle_z_deg << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


// /*!
//  *
//  */
// bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
// {
//   /*
//    *  Tu trzeba napisać odpowiedni kod.
//    */
//   return true;
// }

/*!
 *
 */
bool Interp4Set::ExecCmd( Scene  *Scena,  GuardedSocket  *Socket) const
{
  Vector3D pom;
  pom[0]=pos_x_m;
  pom[1]=pos_y_m;
  pom[2]=Scena->TakeMobileObj(obj_name)->GetPosition_m()[2];
  Scena->TakeMobileObj(obj_name)->SetPosition_m(pom);
  Scena->TakeMobileObj(obj_name)->SetAng_Yaw_deg(angle_z_deg);
  stringstream pom2;
  Vector3D rotacja;
  rotacja[0]=Scena->TakeMobileObj(obj_name)->GetAng_Roll_deg();
  rotacja[1]=Scena->TakeMobileObj(obj_name)->GetAng_Pitch_deg();
  rotacja[2]=Scena->TakeMobileObj(obj_name)->GetAng_Yaw_deg();  

  pom2 << "UpdateObj Name=" << Scena->TakeMobileObj(obj_name)->GetName() <<" Trans_m=" << Scena->TakeMobileObj(obj_name)->GetPosition_m() << " RotXYZ_deg=" << rotacja <<"\n";

  const string tmp2 = pom2.str();
  const char *napis = tmp2.c_str();
  Send_zwykly(Socket->GetSocket(),napis);
  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> obj_name))
  {
    std::cout << "Nie wczytano nazwy obiektu ktorego mam ustawic"<< endl;
    return 1;
  }

  if(!(Strm_CmdsList >> pos_x_m))
  {
    std::cout << "Nie wczytano pozycji x"<< endl;
    return 1;
  }

  if(!(Strm_CmdsList >> pos_y_m))
  {
    std::cout << "Nie wczytano pozycji y"<< endl;
    return 1;
  }

  if(!(Strm_CmdsList >> angle_z_deg))
  {
    std::cout << "Nie wczytano kata obrotu"<< endl;
    return 1;
  }
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  X[m]  Y[m]  Rotacja[deg]" << endl;
}
