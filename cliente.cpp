#include "cliente.h"
#include "bomba.h"
#include "operador.h"

#include <iostream>
using namespace std;

Cliente::Cliente(): nombre("Luk"),dinero(30000), corriente(0), extra(0) {}
Cliente::Cliente(string nombre, float dinero, int corriente, int extra) {
    this->nombre = nombre;
    this->dinero = dinero;
    this->corriente = corriente;
    this->extra = extra;
}
string Cliente::getNombre() const {return nombre;}
float Cliente::getDinero() const {return dinero;}
int Cliente::getCorriente() const {return corriente;}
int Cliente::getExtra()const {return extra;}
void Cliente::setDinero(int dinero) {this->dinero = dinero;}
void Cliente::setCorriente(int corriente) {this->corriente = corriente;}
void Cliente::setExtra(int extra) {this->extra = extra;}

void Cliente::comprarGasolina (string tipoGasolina, int cantidad, Bombas &bomba, Bombas &provedor) {
    bool gasolina = true;
    int consumo;
    consumo = getDinero() - bomba.calcularPrecios(gasolina, cantidad);
    if (tipoGasolina == "Extra" || tipoGasolina == "extra") { //Establece el tipo de gasolina de compra
        gasolina = false;
    }
    if (bomba.verificarCantidad(cantidad,gasolina)) { //Primero verifica la bomba tiene suficiente cantidad de la gasolina que se quiere comprar


        if (consumo>=0) { //Luego verifica si al cliente le alcanza la plata
            setDinero(consumo);
            cout << "Compra exitosa " << getNombre() << "!!!" << endl;
            cout << "Dinero (- " << bomba.calcularPrecios(gasolina, cantidad)<<"): " << endl;
            if (gasolina) { //Hace la compra según la gasolina elegida
                bomba.setCantidadCorr(bomba.getCantidadCorr()-cantidad);
                setCorriente(getCorriente()+cantidad);
                bomba.registrarCorr(cantidad);
            } else {
                bomba.setCantidadExt(bomba.getCantidadExt()-cantidad);
                setExtra(getExtra()+cantidad);
                bomba.registrarExt(cantidad);
            }
        } else {
            cout << "Saldo insuficiente para " << getNombre() << endl;
        }
    } else { //Si no hay suficiente cantidad de gasolina en la bomba
        //Podria crear otro objeto bomba para igualarlo a mi bomba?? - Funciona, pero es buena práctica?
        Operador oper (bomba);
        cout << "\nInsuficiente combustible, redirigiendo con el operador..." << endl;
        oper.recargarBomba(provedor);
        bomba = oper.getBomba(); //Si no es bueno hacer esto, podría cambiarse por un método de la clase bomba que haga esto.
        cout << "\nIntentando de nuevo la compra ...\n\n";
        comprarGasolina(tipoGasolina, cantidad, bomba, provedor);
    }
}
void Cliente::mostrarDatos() {
cout << nombre << "-> Dinero: " << dinero << " || cantidad de gasolina que posee-> Corriente: " << corriente << " Extra: " << extra << endl;
}
