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
    class Dane
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

            std::string Nazwa;

            Vector3D Rotacja;

            Vector3D pozycja;

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
            // Dane(std::string name, Vector3D rot_deg, Vector3D pos_m, Vector3D skala, Vector3D color, Vector3D shift)
            //                             MobileObj(name, rot_deg, pos_m), scale(skala), colorRGB(color), _Shift(shift) {};

            Dane(std::string name, Vector3D rot_deg, Vector3D pos_m, Vector3D skala, Vector3D color, Vector3D shift)
            {
                                            pozycja=pos_m;
                                            Rotacja=rot_deg;
                                            scale=skala;
                                            colorRGB=color;
                                            _Shift=shift;
                                            Nazwa=name;
                                            //, scale(skala), colorRGB(color), _Shift(shift) {};
            }
            Dane(){
                MobileObj();
                for (int i = 0; i < 3; i++)
                {
                    scale[i]=1;
                    colorRGB[i]=0;
                    _Shift[i]=0;
                    pozycja[i]=0;
                    Rotacja[i]=0;
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
            const Vector3D & GetColor(){return colorRGB;}
            const Vector3D & GetShift(){return _Shift;}
            const Vector3D & GetPosition_m(){return pozycja;}
            const std::string & GetName(){return Nazwa;}

            const double & GetAng_Roll_deg(){return Rotacja[0];}
            const double & GetAng_Pitch_deg(){return Rotacja[1];}
            const double & GetAng_Yaw_deg(){return Rotacja[2];}
            

            void SetShift(Vector3D shift) { _Shift = shift; }		
            void SetScale(Vector3D skala) { scale = skala; }
            void SetRGB(Vector3D rgb) { colorRGB = rgb; }
            void SetPosition_m(Vector3D pozycja2) { pozycja = pozycja2; }
            void SetAng_Roll_deg(double rotacja) { Rotacja[0] = rotacja; }
            void SetAng_Pitch_deg(double rotacja) { Rotacja[1] = rotacja; }
            void SetAng_Yaw_deg(double rotacja) { Rotacja[2] = rotacja; }
            
            void SetName(std::string nazwa2) { Nazwa = nazwa2; }
    };


#endif