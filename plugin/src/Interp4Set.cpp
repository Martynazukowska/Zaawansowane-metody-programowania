#include <iostream>
#include "Interp4Set.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


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


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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
