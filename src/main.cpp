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

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <iostream>
#include <list>

using namespace std;
using namespace xercesc;
#define LINE 500

/*!
 * Czyta z pliku opis poleceń i dodaje je do listy komend,
 * które robot musi wykonać.
 * \param sFileName - (\b we.) nazwa pliku z opisem poleceń.
 * \param CmdList - (\b we.) zarządca listy poleceń dla robota.
 * \retval true - jeśli wczytanie zostało zrealizowane poprawnie,
 * \retval false - w przeciwnym przypadku.
 */
bool ReadFile(const char* sFileName, Configuration &rConfig)
{
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

   DefaultHandler* pHandler = new XMLInterp4Config(rConfig);
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

bool ExecProcesor(const char *NazwaPliku,istringstream &IStrm4Cmds)
{
  string Cmd4Preproc="cpp -P ";
  char Line[LINE];
  ostringstream OTmpStrm;

  Cmd4Preproc+=NazwaPliku;
  FILE*pProc=popen(Cmd4Preproc.c_str(),"r");

  if(!pProc)return false;

  while(fgets(Line,LINE,pProc))
  {
    OTmpStrm<<Line;
  }
  IStrm4Cmds.str(OTmpStrm.str());
  return pclose(pProc)==0;
}



int main(int argc, char *argv[])
{
  if (argc <= 1)
  {
    cerr << "Za mało argumentów \n";
    exit(-1);
  }

  istringstream file;
  if ( !ExecProcesor(argv[1], file)) {
      cerr << "Niepoprawny plik do wczytania..." << endl;
      exit(-1);
  }

  std::vector<Interp4Command *> wskaznikiCmd;
 
  
  InterfaceVector Libs;
  Libs.CreateCmd("Move");
  Libs.CreateCmd("Rotate");
  Libs.CreateCmd("Pause");
  Libs.CreateCmd("Set");

  Testy test;
  test.Czytwanie_wartości_wtyczek();
  test.Wskazniki_i_wartosci();

  
  string name;
  while (!file.eof())
  {
    file >> name;
    if (name.length() > 0)
    {
      wskaznikiCmd.push_back(Libs[name]->get_Cmd());
      wskaznikiCmd.back()->ReadParams(file);
    }
  }

    int i = 1;
  for (Interp4Command *cmd : wskaznikiCmd)
  {
    cout << i++ << ". ";
    cmd->PrintCmd();
  }  

}
