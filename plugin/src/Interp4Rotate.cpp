#include <iostream>
#include "Interp4Rotate.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


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
bool Interp4Rotate::ExecCmd( Scene  *Scena,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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
