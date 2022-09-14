#include <iostream>
#include <string>
#include <ctime>


using namespace std;


class Flight {

    private: 
        struct tm t;
        time_t flightTime;

        int numVuelo;
        int canPasajeros = 320; //Por defecto
        string aerolinea = "Sin especificar"; //Por defecto
        int atraso = 0;
        bool mantenimiento;
        
    public: 
        Flight(int pHour, int pMinutes, int pNumVuelo) {
            t.tm_year = 2022-1900;
            t.tm_mon = 8;
            t.tm_mday = 1;
            t.tm_hour = pHour;
            t.tm_min = pMinutes;
            t.tm_sec = 0;
            t.tm_isdst = 0;

            this->numVuelo = pNumVuelo;
        }

        //Funciones de get en set-->

        char* flightTimeString() {
            this->flightTime = mktime(&t);
            char* result = ctime(&flightTime);
            return result;
        }
        float getIntTimeValue() {
            float result = 0;
            float min = (float)t.tm_min;
            result += (t.tm_hour+(min/100));
            return result;
        }

        int getNumVuelo(){
            return numVuelo;
        }

        void setCanPasajeros(int pCantidad){
            this->canPasajeros = pCantidad;
        }

        int getCanPasajeros(){
            return canPasajeros;
        }

        void setAerolinea(string pAerolinea){
            this->aerolinea = pAerolinea;
        }

        string getAerolinea(){
            return aerolinea;
        }

        void setAtraso(int pAtraso){ // tomando el ctime lo transforma automaticamente sin nececidad de este codigo pero lo hice por hacerlo.
            t.tm_min-=atraso;
            if (atraso+pAtraso < 17 && atraso+pAtraso>0){
                this->atraso+=pAtraso;
            }else if(atraso+pAtraso > 0){  
                this->atraso = 17;
            }
            if (t.tm_min+atraso < 60){
                t.tm_min+=this->atraso;
            }else{
                t.tm_hour+=1; // Para usar el codigo de abajo se debe de comentar esta linea...
                // Si se quiere aumentar la hora y está en 23:00, se debe de igualar a 00:00 y cambiar el dia, pero no se pide...
                /*if (t.tm_hour+1=24){
                    t.tm_hour=0 
                    t.tm_daym+=1
                }else{
                    t.tm_hour+=1;
                }
                */
                t.tm_min = t.tm_min+atraso-60;
            }
        }

        int getAtraso(){
            return atraso;
        }  

        void setInMantenimiento(){
            this->mantenimiento = true;
            int numR = rand()%18;
            this->setAtraso(numR); // Si se selecciona en mantenimiento se retrasa la cantidad de minutos fija en retraso...
        }   

        bool getMantenimiento(){
            return mantenimiento;
        }

};  