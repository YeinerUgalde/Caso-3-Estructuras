#include <iostream>
#include "Flight.h"
#include <time.h>
#include "List.h"
#include <cstdlib>
#include "Stack.h"

using namespace std;

List<Flight>* fillFlights(int pCantidad, int pStartHour, int pEndHour) {
    List<Flight>* vuelos = new List<Flight>();
    for (int i = 0 ; i<pCantidad ;i++){
        int hora = pStartHour + rand() % (pEndHour-pStartHour);
        int minutos = rand() % 60;
        vuelos->add(new Flight(hora,minutos,i));
    }
    return vuelos;
} 

List<List<Flight>>* pistas(int pCantidadPistas){ 
    List<List<Flight>>* pistas = new List<List<Flight>>();
    for (int i = 0; i<pCantidadPistas; i++){
        pistas->add(new List<Flight>());
    }
    return pistas;
}

List<List<Flight>>* addVuelos(List<List<Flight>>* pPistas, List<Flight>* pVuelos){
    int j = 0;
    while (j < pVuelos->getSize()){
        for (int i = 0; i<pPistas->getSize(); i++){
            if (pPistas->find(i)->isEmpty() && j < pVuelos->getSize()){
                pPistas->find(i)->add(pVuelos->find(j++));  
            }else{
                for(int m = 0;m< pPistas->find(i)->getSize();m++){
                    float time = pVuelos->find(j)->getIntTimeValue();
                    float time2 = pPistas->find(i)->find(m)->getIntTimeValue();
                    if (time <= time2){
                        if (time == time2){
                            if (m+1 < pPistas->find(i)->getSize()){
                                continue;
                            }else{
                                pVuelos->find(j)->setInMantenimiento(); // En casos extremos donde todas las pistas esten ocupadas a la misma hora
                                cout << "Se atraso un vuelo debido a que tenian la misma hora" << endl;
                            }
                        }
                        pPistas->find(i)->insert(m,pVuelos->find(j++));
                        if (j >= pVuelos->getSize()){
                            return pPistas;
                        }
                        break;
                    }
                    else if (m+1>=pPistas->find(i)->getSize()){
                        pPistas->find(i)->add(pVuelos->find(j++));
                        break;
                    }
                }
            } 
        }
    }
    return pPistas;
}

int main() {
    int cantidadDeVuelos;
    int HoraInicio;
    int HoraFin;
    int CantidadDePistas;
    cout << "\nDigite la cantidad de vuelos: " << endl;;
    cin >> cantidadDeVuelos;
    cout << "Digite la hora en que los vuelos iniciaran: " << endl;;
    cin >> HoraInicio;
    cout << "Digite la hora en que los vuelos finalizaran: " << endl;;
    cin >> HoraFin;
    cout << "Digite la cantidad de pistas en el aeropuerto: " << endl;;
    cin >> CantidadDePistas;

    List<Flight>* vuelos = fillFlights(cantidadDeVuelos,HoraInicio,HoraFin);
    cout << "\n______________________________________________________________________" << endl;
    cout << "VUELOS CREADOS: \n\n" ;
    for (int i = 0; i<vuelos->getSize();i++){
        vuelos->find(i)->setInMantenimiento();
        cout <<"Numero de vuelo "<< i << ": " << vuelos->find(i)->flightTimeString();
    }
    cout << "______________________________________________________________________" << endl;

    List<List<Flight>>* lPistas = pistas(CantidadDePistas);
    addVuelos(lPistas,vuelos);
    cout << "\nLos vuelos con menor numero son los primeros en salir...\n\n";
    for (int i = 0 ; i<lPistas->getSize();i++){
        cout << "Pista ["<<i+1 << "]: "<< endl;
        for (int j = 0; j<lPistas->find(i)->getSize(); j++){
            cout <<"        ("<<j<<")"<<" Vuelo numero " << lPistas->find(i)->find(j)->getNumVuelo()<<": " << lPistas->find(i)->find(j)->getIntTimeValue() << endl;
        }
        cout << endl;
    }
    return 0;
}