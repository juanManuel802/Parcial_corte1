#include "operador.h"
#include "bomba.h"
#include <iostream>
#include <string>
using namespace std;
Operador::Operador(Bombas bomba) {this->bomba = bomba;}
Bombas Operador::getBomba() const {return bomba;}

void Operador::recargarBomba(Bombas &provedor) {
    int op;
    cout << "\nHola, soy el operador. Qué desea hacer?:\n1)Recargar la bomba desde el proveedor principal.\n2)Recargar el proveedor\n";
    cin >> op;
    if (op==1) {
        int cant,otherCant, op;
        bool comp;
        provedor.mostrarDatos();
        cout << "Qué tipo de combustible deseas transferir desde el provedor hasta la bomba " << this->bomba.getMarca() << "?\n1)Corriente\n2)Extra\n3)Ambas" << endl;
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "Cuanto deseas transferir de gasolina corriente desde el proveedor hasta la bomba?" << endl;
            do {
                if (comp) {cout<<"Intenta de nuevo\n";}
                cin >> cant;
                //bomba.getCapacidadCorr()-bomba.getCantidadCorr()  Esto es lo que le falta a la bomba de combustible que se quiere proveer para llegar a su capacidad máxima
                if (cant < (bomba.getCapacidadCorr()-bomba.getCantidadCorr())) {
                    comp = false;
                    bomba.setCantidadCorr(bomba.getCantidadCorr()+cant);
                    provedor.setCantidadCorr(bomba.getCantidadCorr()-cant);
                } else if (cant > (bomba.getCapacidadCorr()-bomba.getCantidadCorr())) {
                    cout << "Intente con valores menores a "<<bomba.getCapacidadCorr()-bomba.getCantidadCorr()<<"\n";
                    comp = true;
                } else if (cant == 0) {
                    comp = true;
                    //Aquí agragar el uso de exepciones
                    cout << "Ingresa un valor valido" << endl;
                }                    
            } while (comp);
            bomba.mostrarDatos();
            break;
        case 2:
            cout << "Cuanto deseas transferir de gasolina extra desde el proveedor hasta la bomba?" << endl;
            do {
                cin >> cant;
                //bomba.getCapacidadExt()-bomba.getCantidadExt()  Esto es lo que le falta a la bomba de combustible que se quiere proveer para llegar a su capacidad máxima
                if (cant <= (bomba.getCapacidadExt()-bomba.getCantidadExt())) {
                    bomba.setCantidadExt(bomba.getCantidadExt()+cant);
                    provedor.setCantidadCorr(bomba.getCantidadCorr()-cant);
                    comp = false;
                } else if (cant >= (bomba.getCapacidadExt()-bomba.getCantidadExt())) {
                    cout << "Intente con valores menores a "<<bomba.getCapacidadExt()-bomba.getCantidadExt()<<"\n";
                    comp = true;
                } else if (cant == 0) {
                    comp = true;
                    //Aquí agragar el uso de exepciones
                    cout << "Ingresa un valor valido" << endl;
                }
            } while (comp);
            bomba.mostrarDatos();
            break;
        case 3:
            cout << "Cuanto deseas transferir de gasolina corriente desde el proveedor hasta la bomba?" << endl;
            do {
                if (comp) {cout<<"Intenta de nuevo\n";}
                cin >> cant;
                if (cant < (bomba.getCapacidadCorr()-bomba.getCantidadCorr())) {
                    comp = false;
                } else if (cant > (bomba.getCapacidadCorr()-bomba.getCantidadCorr())) {
                    cout << "Intente con valores menores a "<<bomba.getCapacidadCorr()-bomba.getCantidadCorr()<<"\n";
                    comp = true;
                } else if (cant == 0) {
                    comp = true;
                    //Aquí agragar el uso de exepciones
                    cout << "Ingresa un valor valido" << endl;
                }                    
            } while (comp);
            cout << "Cuanto deseas transferir de gasolina extra desde el proveedor hasta la bomba?" << endl;
            do {
                if (comp) {cout<<"Intenta de nuevo\n";}
                cin >> otherCant;
                if (otherCant < (bomba.getCapacidadExt()-bomba.getCantidadExt())) {
                    comp = false;
                } else if (otherCant > (bomba.getCapacidadExt()-bomba.getCantidadExt())) {
                    cout << "Intente con valores menores a "<<bomba.getCapacidadExt()-bomba.getCantidadExt()<<"\n";
                    comp = true;
                } else if (cant == 0) {
                    comp = true;
                    //Aquí agragar el uso de exepciones
                    cout << "Ingresa un valor valido" << endl;
                }                    
            } while (comp);
            bomba.setCantidad(bomba.getCantidadCorr()+cant,bomba.getCantidadExt()+otherCant);
            provedor.setCantidad(provedor.getCantidadCorr()-cant,provedor.getCantidadExt()-otherCant);
            break;
        default:
            break;
        }
        //bomba = this->bomba; 
    } else if (op==2) {
        provedor.llenarAlMaximo();
    }
}

