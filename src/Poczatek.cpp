#include "Poczatek.hh"

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool Poczatek::PoczatekXML()
{
   const char * sFileName = this->xmlFile.c_str();
   try {
            XMLPlatformUtils::Initialize();
   }
   catch (const XMLException& toCatch) {
            char* message = XMLString::transcode(toCatch.getMessage());
            cerr << "Error during initialization! :\n";
            cerr << "Exception message is: \n"
                 << message << "\n";
            XMLString::release(&message);
            return 1;
   }

   SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

   pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
   pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
   pParser->setFeature(XMLUni::fgXercesDynamic, false);
   pParser->setFeature(XMLUni::fgXercesSchema, true);
   pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
   pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);
   DefaultHandler* pHandler = new XMLInterp4Config(&conf);
   pParser->setContentHandler(pHandler);
   pParser->setErrorHandler(pHandler);

   try {

     if (!pParser->loadGrammar("config/config.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
       cerr << "!!! Plik grammar/actions.xsd, '" << endl
            << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
            << endl;
       return false;
     }
     pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
     pParser->parse(sFileName);
   }
   catch (const XMLException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            cerr << "Informacja o wyjatku: \n"
                 << "   " << sMessage << "\n";
            XMLString::release(&sMessage);
            return false;
   }
   catch (const SAXParseException& Exception) {
            char* sMessage = XMLString::transcode(Exception.getMessage());
            char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

            cerr << "Blad! " << endl
                 << "    Plik:  " << sSystemId << endl
                 << "   Linia: " << Exception.getLineNumber() << endl
                 << " Kolumna: " << Exception.getColumnNumber() << endl
                 << " Informacja: " << sMessage 
                 << endl;

            XMLString::release(&sMessage);
            XMLString::release(&sSystemId);
            return false;
   }
   catch (...) {
            cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
            return false;
   }

   delete pParser;
   delete pHandler;
   return true;
}

bool Poczatek::PoczatekCmd(std::istringstream & IStrm4Cmds)
{
    std::string Cmd4Preproc = "cpp -P ";
    char Line[LINESIZE];
    std::ostringstream OTmpStrm;
    Cmd4Preproc += cmdFile.c_str();

    FILE * pProc = popen(Cmd4Preproc.c_str(),"r");
    if(!pProc)
        return false;
    while(fgets(Line,LINESIZE,pProc))
    {
        OTmpStrm<<Line;
    }
    IStrm4Cmds.str(OTmpStrm.str());

    return pclose(pProc) == 0;
}

bool Poczatek::SendScene() 
{
  for (int i = 0; i < conf.GetObjVector().size(); ++i)
  {
    stringstream pom;  
    //Dane tmp = conf.GetObjVector()[i];
    Dane tmp=conf.GetObjVector()[i];
    Vector3D rotacja;
    rotacja[0]=tmp.GetAng_Roll_deg();
    rotacja[1]=tmp.GetAng_Pitch_deg();
    rotacja[2]=tmp.GetAng_Yaw_deg();
    pom << "AddObj Name=" << tmp.GetName() << " RGB="  << tmp.GetColor() << "  Scale=" << tmp.GetScale() <<
      " Shift=" << tmp.GetShift() << " RotXYZ_deg=" << rotacja << " Trans_m=" << tmp.GetPosition_m() <<"\n";

    const string tmp2 = pom.str();
    const char *napis = tmp2.c_str();
    Send_zwykly(socket.GetSocket(),napis);


    
  }
  
}

bool Poczatek::ExecProgram(const char* NazwaPliku) 
{
  string Cmd4Preproc = "cpp -P ";
  char Line[LINESIZE];
  ostringstream OTmpStrm;
  istringstream Strumien;


  Cmd4Preproc += NazwaPliku;
  FILE* pProc = popen(Cmd4Preproc.c_str(),"r");

  if (!pProc)
    return false;

  while (fgets(Line,LINESIZE,pProc)) 
  {
    OTmpStrm << Line;
  }

  Strumien.str(OTmpStrm.str());
  //vector<Interp4Command*> CmdCollection;
  queue<Interp4Command*> Cmd;
  queue<std::thread> ThreadCollection;

  string Name;
  while(!Strumien.eof()) 
  {
    Strumien >> Name;
    // if(Name.length() > 0)
    // {
    //   CmdCollection.push_back(Lib[Name]->get_Cmd());
    //   CmdCollection.back()->ReadParams(Strumien);
    // }
    if(Name == "Begin_Actions") 
    {
    
    }

    else if(Name == "End_Actions") 
    { 
      while(!Cmd.empty())
      {
	      ThreadCollection.push(thread(&Interp4Command::ExecCmd,Cmd.front(),&Scena,&socket));
	      Cmd.pop();
      }
      while(!ThreadCollection.empty())
      {
	      ThreadCollection.front().join();	
	      ThreadCollection.pop();
      }
    }

    else if(Name== "Move" || Name== "Rotate" || Name== "Pause" || Name== "Set")
    {	
      Cmd.push(Lib[Name]->get_Cmd());
      Cmd.back()->ReadParams(Strumien);
    }
  }

  // for(int i=0; i<CmdCollection.size()-1;i++)
  // {
  //   //CmdCollection[i]->ExecCmd(&Scena,&socket);
  //   //CmdCollection[i]->PrintCmd();
  // }

  return 1;



}


// int Poczatek::Send(const char *sMesg)
// {
//      ssize_t  IlWyslanych;
//      ssize_t  IlDoWyslania = (ssize_t) strlen(sMesg);

//      while ((IlWyslanych = write(socket_manager,sMesg,IlDoWyslania)) > 0) 
//      {
//           IlDoWyslania -= IlWyslanych;
//           sMesg += IlWyslanych;
//      }
//      if (IlWyslanych < 0) 
//      {
//           cerr << "*** Blad przeslania napisu." << endl;
//      }
//      return 0;
// }
