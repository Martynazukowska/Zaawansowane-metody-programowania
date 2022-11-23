#include <iostream>
#include "Interp4Move.hh"
#include "MobileObj.hh"

using std::cout;
using std::endl;


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
bool Interp4Move::ExecCmd( Scene  *Scena,  int  Socket) const
{
  /*
   *  Tu trzeba napisać odpowiedni kod.
   */
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
