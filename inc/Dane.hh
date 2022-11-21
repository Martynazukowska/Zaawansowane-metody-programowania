#ifndef DANE_HH
#define DANE_HH
#include "MobileObj.hh"

/*!
 * \file
 * \brief Definicja klasy Dane.
 */

    /*! 
    *   \brief Klasa Dane reprezentuje dodatkowe dane potrzebne do zasymolowania objektu
    */
    class Dane: public MobileObj
    {   
        private:
            /*!
            * \brief 3D vector Skali
            */
            Vector3D scale;
            /*!
            * \brief kolor RGB
            */
            Vector3D colorRGB;
            /*!
            * \brief 3D vector Środka objektu
            */
            Vector3D _Shift;

        public:
            // /*!
            // * \brief Dane konstructor
            // * \param[in] name - nazwa
            // * \param[in] rot_deg - rotacja
            // * \param[in] pos_m - pozycja Vector3D (x, y, z)
            // */

            // Dane(std::string in_name, Vector3D in_rot_deg, Vector3D in_pos_m):
            //                             MobileObj(in_name, in_rot_deg, in_pos_m) {};

            /*!
            * \brief Dane konstructor
            * \param[in] name - nazwa
            * \param[in] rot_deg - rotacja
            * \param[in] pos_m - pozycjaVector3D (x, y, z)
            * \param[in] skala - skala jako Vector3D (x, y, z).
            * \param[in] color - color red [0, 255] color green [0, 255] color blue [0, 255]
            */
            Dane(std::string name, Vector3D rot_deg, Vector3D pos_m, Vector3D skala, Vector3D color, Vector3D shift):
                                        MobileObj(name, rot_deg, pos_m), scale(skala), colorRGB(color), _Shift(shift) {};
            Dane(){
                MobileObj();
                for (int i = 0; i < 3; i++)
                {
                    scale[i]=0;
                    colorRGB[i]=0;
                    _Shift[i]=0;
                }
                
            };

            /*!
            * \brief  Udostępnia skale obiektu
            * \return Zwraca skale
            * 
            */
            const Vector3D & GetScale(){return scale;}; 
            /*!
            * \brief Udostepnia kolor w jakim ma byc namalowany obiekt
            * \return Zwraca Vektor3D [red,green,blue]
            * 
            */
            const Vector3D & GetColorR(){return colorRGB;}
    };


#endif