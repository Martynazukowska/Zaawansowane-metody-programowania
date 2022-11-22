#ifndef PROGRAMINTERPRETER_HH
#define PROGRAMINTERPRETER_HH
#define PORT 2877
#include "Scene.hh"
#include "InterfaceVector.hh"
#include "Configuration.hh"
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

using namespace std;



class ProgramInterpreter 
{
    private:
        int socket_manager;
    public:
        Scene Scena;
        InterfaceVector Lib;
        Configuration conf;
        ProgramInterpreter();
        bool SendScene();
        
        // ~ProgramInterpreter(){Send("Close\n"); close(socket_manager);}


        // std::string CreateMessage(Dane mob);

        // /*!
        // * \brief Sends a text message to the server
        // *
        // * Sends a text message to the server
        // * 
        // * \param[in] sMesg - text message to be send
        // * \retval true - Sending successful
        // * \retval false - Otherwise
        // */
        // bool Send(const char *sMesg);

};


#endif