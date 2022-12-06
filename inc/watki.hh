#ifndef WATKI_HH
#define WATKI_HH

#include <mutex>

/*!
 * \file
 * \brief Contains the definition of a class AccessControl
 */


/*!
 * \brief Containst info about changes
 *
 */
class GuardedSocket {
   /*!
    * \brief Mutex to lock access to the object
    */
    std::mutex  Guard;

    int socket=0;
   
 public:
   GuardedSocket(){socket=0;}
   GuardedSocket(int Socket): socket(Socket) {}
   int GetSocket() const { return socket; }
   void SetSocket(int Nowy_socket){ socket=Nowy_socket; }

   void LockAccess() { Guard.lock(); }
  /*!
   * \brief Unlock access to the scene
   */
   void UnlockAccess() { Guard.unlock(); } 
};


#endif 