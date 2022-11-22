#include "ProgramInterpreter.hh"

ProgramInterpreter::ProgramInterpreter() {
}



bool ProgramInterpreter::SendScene() 
{
  for (int i = 0; i < conf.GetObjVector().size(); ++i)
  {
    stringstream pom;  
    pom << "AddObj Name=" << conf.GetObjVector()[i].GetName() << "\n";
    cout << pom.str();  
    
  }
  
}




// std::string ProgramInterpreter::CreateMessage(Dane mob)
// {
//     std::string temp = "";
//     temp += "Cube ";
//     temp += std::to_string(mob.GetScale()[0]) + " ";
//     temp += std::to_string(mob.GetScale()[1]) + " ";
//     temp += std::to_string(mob.GetScale()[2]) + " ";
//     temp += std::to_string(mob.GetPositoin_m()[0]) + " ";
//     temp += std::to_string(mob.GetPositoin_m()[1]) + " ";
//     temp += std::to_string(mob.GetPositoin_m()[2]) + " ";
//     temp += std::to_string(mob.GetAng_Roll_deg()) + " ";
//     temp += std::to_string(mob.GetAng_Pitch_deg()) + " ";
//     temp += std::to_string(mob.GetAng_Yaw_deg()) + " ";
//     // temp += std::to_string(mob.GetColorR[0]) + " ";
//     // temp += std::to_string(mob.GetColorR[1]) + " ";
//     // temp += std::to_string(mob.GetColorR[2]) + "\n";

//     return temp;
// }



// bool ProgramInterpreter::Send(const char *sMesg)
// {
//     ssize_t  IlWyslanych;
//     ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

//     while ((IlWyslanych = write(socket_manager,sMesg,IlDoWyslania)) > 0) 
//     {
//         IlDoWyslania -= IlWyslanych;
//         sMesg += IlWyslanych;
//     }
//     if (IlWyslanych < 0) 
//     {
//         std::cerr << "*** Blad przeslania napisu." << std::endl;
//         return false;
//     }
//     return true;
// }