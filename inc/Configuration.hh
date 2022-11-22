#ifndef CONFIGURATION_HH
#define CONFIGURATION_HH

#include "Dane.hh"
#include <vector>



class Configuration {
  private:
  /*!
  * \brief Westor ściezek wtyczek
  */
  std::vector<std::string> LibsVector;
  /*!
  * \brief Westor mobilnych objektow
  */ 
  std::vector<Dane> ObjVector;

  public:
  std::vector<std::string> &GetLibsVector() { return LibsVector; }
  std::vector<Dane> &GetObjVector() { return ObjVector; }

  /*!
  * \brief Dodaj wtyczke
  *  \param[in] path - sciezka wtyczki do dodania
  */
  void DodajLibsPaths(std::string path) { LibsVector.push_back(path); }

  /*!
  * \brief Dodaj wtyczke
  *  \param[in] path - sciezka wtyczki do dodania
  */
  void DodajObjVector(Dane obj) { ObjVector.push_back(obj); }

};


#endif
