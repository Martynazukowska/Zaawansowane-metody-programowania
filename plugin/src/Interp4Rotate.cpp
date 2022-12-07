#include <iostream>
#include "Interp4Rotate.hh"
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
  const char* GetCmdName() { return "Rotate"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


/*!
 *
 */
Interp4Rotate::Interp4Rotate(): obj_name("") ,rot_speed_degs(0),rot_deg(0)
{}


/*!
 *
 */
void Interp4Rotate::PrintCmd() const
{
  /*
   *  Tu trzeba napisać odpowiednio zmodyfikować kod poniżej.
   */
  cout << GetCmdName() << " " << obj_name <<" "<<rot_speed_degs << " " <<rot_deg<<" "<<endl;
}


/*!
 *
 */
const char* Interp4Rotate::GetCmdName() const
{
  return ::GetCmdName();
}


// /*!
//  *
//  */
// bool Interp4Rotate::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
// {
//   /*
//    *  Tu trzeba napisać odpowiedni kod.
//    */
//   return true;
// }
/*!
 *
 */
bool Interp4Rotate::ExecCmd( Scene  *Scena,  GuardedSocket  *Socket) const
{
  double startYaw = Scena->TakeMobileObj(obj_name)->GetAng_Yaw_deg();
  double delta_yaw_deg = 0;
    double dist_step_deg = (double)rot_deg/N;
    double time_step_us = (((double)this->rot_deg/this->rot_speed_degs)*1000000)/N;

    for(int i = 0; i<N; ++i)
    {
        delta_yaw_deg += dist_step_deg;
        Scena->TakeMobileObj(obj_name)->SetAng_Yaw_deg(delta_yaw_deg + startYaw);
        stringstream pom;
        Vector3D rotacja;
        rotacja[0]=Scena->TakeMobileObj(obj_name)->GetAng_Roll_deg();
        rotacja[1]=Scena->TakeMobileObj(obj_name)->GetAng_Pitch_deg();
        rotacja[2]=Scena->TakeMobileObj(obj_name)->GetAng_Yaw_deg();  

      pom << "UpdateObj Name=" << Scena->TakeMobileObj(obj_name)->GetName() << " RotXYZ_deg=" << rotacja <<"\n";

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
bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  if(!(Strm_CmdsList >> obj_name))
  {
    std::cout << "Nie wczytano nazwy obiektu obrotu"<< endl;
    return 1;
  }

  if(!(Strm_CmdsList >> rot_speed_degs))
  {
    std::cout << "Nie wczytano predkosci obrotowej"<< endl;
    return 1;
  }

  if(!(Strm_CmdsList >> rot_deg))
  {
    std::cout << "Nie wczytano kata obrotu"<< endl;
    return 1;
  }
    

  return true;
}


/*!
 *
 */
Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


/*!
 *
 */
void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate  NazwaObiektu  Prędkość[deg/s]  Rotacja[deg]" << endl;
}
