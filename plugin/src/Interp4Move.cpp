#include <iostream>
#include "Interp4Move.hh"
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
  const char* GetCmdName() { return "Move"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Move::CreateCmd();
}


/*!
 *
 */
Interp4Move::Interp4Move(): obj_name(""),vel_ms(0),dist_m(0)
{}


/*!
 *
 */
void Interp4Move::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << obj_name << " "<<vel_ms<<" "<< dist_m << endl;
}


/*!
 *
 */
const char* Interp4Move::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
// bool Interp4Move::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
// {
//   /*
//    *  Tu trzeba napisać odpowiedni kod.
//    */
//   return true;
// }

/*!
 *
 */
bool Interp4Move::ExecCmd( Scene  *Scena,  GuardedSocket  *Socket) const
{
  //najlepiej na wektorze
  Vector3D startPos = Scena->TakeMobileObj(obj_name)->GetPosition_m();
  double startRoll = Scena->TakeMobileObj(obj_name)->GetAng_Roll_deg();
  double startPitch = Scena->TakeMobileObj(obj_name)->GetAng_Pitch_deg();
  double startYaw = Scena->TakeMobileObj(obj_name)->GetAng_Yaw_deg();
  double delta_x_m, delta_y_m, delta_z_m;
  delta_x_m = delta_y_m = delta_z_m = 0;

  double dist_step_m = (double)dist_m/N;
  double time_step_us = (((double)this->dist_m/this->vel_ms)*1000000)/N;

  for(int i = 0; i<N; ++i)
  {
    delta_x_m += dist_step_m*cos(startPitch*M_PI/180)*cos(startYaw*M_PI/180);
    delta_y_m += dist_step_m*(cos(startRoll*M_PI/180)*sin(startYaw*M_PI/180) + cos(startYaw*M_PI/180)*sin(startPitch*M_PI/180)*sin(startRoll*M_PI/180));
    delta_z_m += dist_step_m*(sin(startRoll*M_PI/180)*sin(startYaw*M_PI/180) - cos(startRoll*M_PI/180)*cos(startYaw*M_PI/180)*sin(startPitch*M_PI/180));
    Vector3D pomocniczy;
    pomocniczy[0]=delta_x_m+startPos[0];
    pomocniczy[1]=delta_y_m+startPos[1];
    pomocniczy[2]=delta_z_m+startPos[2];
    Scena->TakeMobileObj(obj_name)->SetPosition_m(pomocniczy);

    stringstream pom;  

    pom << "UpdateObj Name=" << Scena->TakeMobileObj(obj_name)->GetName() <<" Trans_m=" << Scena->TakeMobileObj(obj_name)->GetPosition_m() <<"\n";

    const string tmp2 = pom.str();
    const char *napis = tmp2.c_str();
    Send_zwykly(Socket->GetSocket(),napis);
    usleep(time_step_us);

  }
  return true;
}


/*!
 *
 */
bool Interp4Move::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> obj_name))
  {
    std::cout << "Nie wczytano nazwy obiektu obrotu"<< endl;
    return 1;
  }

  if(!(Strm_CmdsList >> vel_ms))
  {
    std::cout << "Nie wczytano predkosci"<< endl;
    return 1;
  }

  if(!(Strm_CmdsList >> dist_m))
  {
    std::cout << "Nie wczytano odległości"<< endl;
    return 1;
  }
    
  return true;
}


/*!
 *
 */
Interp4Command* Interp4Move::CreateCmd()
{
  return new Interp4Move();
}


/*!
 *
 */
void Interp4Move::PrintSyntax() const
{
  cout << "   Move  NazwaObiektu  Szybkosc[m/s]  DlugoscDrogi[m]" << endl;
}
