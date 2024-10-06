#include <iostream>
#include <vector>
#include <cstdio>
#include "bomba.h"
#include "operador.h"
#include "cliente.h"
using namespace std;

void play (Cliente &cliente, Bombas &bomba, Bombas &provedor) {
    string tipG;
    int gal, gasto;
    float dineroInicial;
    bool quit = true, ret;
    dineroInicial = cliente.getDinero();
    while (quit)
    {    
    cout << "\n\nQue tipo de gasolina deseas tanquear" << endl;
    cin >> tipG;
    cout << "Cuanto deseas tanquear?" << endl;
    //Aqui agregar exepciones para que no ingrese un valor por encima de la capacidad maxima de la bomba
    do {
        try {
            if (ret) {
                cout << "Intenta de nuevo: " << endl;
            }
            cin >> gal;
            if (gal<=0) {
                throw "Negativo o nulo";
            } 
            else if ((tipG=="corriente"||tipG=="Corriente")&&(gal > bomba.getCapacidadCorr())) {
                throw "Por encima de la capacidad máxima de la bomba";
            } else if ((tipG=="extra"||tipG=="Extra")&&(gal > bomba.getCapacidadExt())) {
                throw "Por encima de la capacidad máxima de la bomba";
            } else {
                ret = false;
            }
        } catch (const char *e) {
            cout << "Valor ingresado fuera del rango: " << e << endl;
            ret = true;
        }
    }while (ret);
    cliente.comprarGasolina(tipG,gal,bomba,provedor); 
    cliente.mostrarDatos();
    bomba.mostrarDatos();
    cout <<"\n\nDeseas volver a tanquear en la misma bomba con el mismo usuario? (1 para si, 0 para no)\n";
    cin >> quit;
    quit = quit == 1;
    }
    system("cls");
    
}

int main()
{
    bool quit = true;
    int count = 1;
    vector<Bombas> bombas;
    vector<Cliente> clientes;
    //Objeto de clase bomba proveedor de combustible
    Bombas provedor("Proveedor",10000,10000,10000,10000);
  while (quit) {
        string nombre;
        int corriente, extra;
        float dinero;
        printf("Ingresa el nombre del usuario %d: ", count);
        getline(cin, nombre);
        printf("Ingresa el dinero del usuario %d: ", count);
        cin >> dinero;
        cin.ignore(); 
        printf("Ingresa su cantidad de gasolina corriente: ");
        cin >> corriente;
        cin.ignore();
        printf("Ingresa su cantidad de gasolina extra: ");
        cin >> extra;
        cin.ignore();

        Cliente Cliente(nombre, dinero, corriente, extra);
        clientes.push_back(Cliente);

        printf("Cliente agregado: %s\n", Cliente.getNombre().c_str());
        printf("¿Desea agregar otro cliente? (1 para sí, 0 para no): ");
        cin >> quit;
        cin.ignore();
        count++;
    } 
    system("cls");

    quit = true;
    while (quit) {
        string marca;
        int capacidadCorr, capacidadExt, cantidadCorr, cantidadExt;
        printf("Ingresa la marca de la bomba: ");
        cin >> marca;
        cin.ignore();
        printf("Ingresa la capacidad máxima de almacenamiento del tanque de gasolina corriente: ");
        cin >> capacidadCorr;
        printf("Ingresa la capacidad máxima de almacenamiento del tanque de gasolina extra: ");
        cin >> capacidadExt;
        printf("Ingresa la cantidad de gasolina corriente: ");
        cin >> cantidadCorr;
        printf("Ingresa la cantidad de gasolina extra: ");
        cin >> cantidadExt;

        Bombas Bomba(marca, capacidadCorr, capacidadExt, cantidadCorr, cantidadExt);
        bombas.push_back(Bomba);

        printf("Bomba agregada: Capacidad Corriente: %d, Capacidad Extra: %d, Cantidad Corriente: %d, Cantidad Extra: %d\n",
               capacidadCorr, capacidadExt, cantidadCorr, cantidadExt);

        printf("¿Desea agregar otra bomba? (1 para sí, 0 para no): ");
        cin >> quit;
        quit = quit == 1;
    }
    system("cls");
    //Parte de selección de objetos a utilizar e implementacion de la bomba
    quit = true;
    while (quit)
    {
        int opCl, opBm;
        cout << "Selecciona un cliente: \n";
        for (int i = 0; i < clientes.size(); i++) {
            printf("%d) %s.\n", i+1, clientes[i].getNombre().c_str());
        }
        cin >> opCl;
        opCl--;
        cout << "Cliente seleccionado: ";
        clientes[opCl].mostrarDatos();
        cout << "\nSelecciona una bomba \n";
        for (int i = 0; i < bombas.size(); i++) {
            printf("%d)%s-> Capacidad Corriente: %d, Capacidad Extra: %d, Cantidad Corriente: %d, Cantidad Extra: %d\n",
                i + 1,bombas[i].getMarca().c_str(), bombas[i].getCapacidadCorr(), bombas[i].getCapacidadExt(),
                bombas[i].getCantidadCorr(), bombas[i].getCantidadExt());
        }
        cin >> opBm;
        opBm--;
        cout << "Bomba seleccionada: ";
        bombas[opBm].mostrarDatos();

        play(clientes[opCl],bombas[opBm],provedor);

        clientes[opCl].mostrarDatos();
        bombas[opBm].mostrarDatos();
        system("cls");
        cout << "Gracias por utilizar nuestro servicio.\nDeseas seguir en el programa? (1 para si, 0 para no)" <<endl;
        cin >> quit;
        quit = quit == 1;
        system("cls");
    }
    //Muestra la bomba con mayor ventas
    int mayor=0;
    for (int i = 0; i<bombas.size(); i++) {
        if(bombas[i]>bombas[i-1]) {
            mayor = i;
            break;
        }
    }
    cout << "\n\nBomba con mayor ventas: "<< endl;
    bombas[mayor].mostrarDatos();

    return 0;
}
//Mostrar m+as datos (verificación de funcionamiento)