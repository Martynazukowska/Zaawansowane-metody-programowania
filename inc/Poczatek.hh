#ifndef POCZATEK_HH
#define POCZATEK_HH

#include <map>
#include <memory>
#include "Scene.hh"
#include "InterfaceVector.hh"

#include <string>
#include <sstream>
#include <cassert>
#include <cstdio>
#include <iostream>
#include "xmlinterp.hh"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#define LINESIZE 500

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xmlinterp.hh"
#include <list>
#include "klient.hh"
#include "watki.hh"


using namespace std;
using namespace xercesc;



class Poczatek {
    private:
        std::string cmdFile;
        std::string xmlFile;
        /*! \brief Configuration read from a xml file */
        Configuration conf;
        
public:
/*!
    * \brief KONSTRUKTOR
    * \param[in] cmd - nazwa pliku cmd
    * \param[in] xml - nazwa pliku xml
    */
    Poczatek(std::string cmd, std::string xml): cmdFile(cmd), xmlFile(xml) {} 
    /*!
    * \brief Czytaj z pliku cmd
    * \param[out] IStrm4Cmds - output stream 
    * \retval true - czytanie powiodlo sie
    * \retval false - porazka
    */
    bool PoczatekCmd(std::istringstream & IStrm4Cmds);
    /*!
    * \brief Czy taj z xml
    * \retval true - czytanie powiodlo sie
    * \retval false - niepowiodlo sie
    */
    bool PoczatekXML();
    /*!
    * \brief zwróć terazniejsza conf
    */
    Configuration & GetConf(){return conf; }

    //int socket_manager;
    GuardedSocket socket;
    Scene Scena;
    InterfaceVector Lib;
    bool SendScene();

    //int Send(const char *sMesg);
    bool ExecProgram(const char* FileName);


};


#endif