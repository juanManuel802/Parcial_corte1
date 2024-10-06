#include "bomba.h"
#include <iostream>
using namespace std;
#include <string>

Bombas::Bombas() : marca(""), capacidadCorr(500), capacidadExt(500), cantidadCorr(500), cantidadExt(500), registroCorr(0), registroExt(0) {}
Bombas::Bombas(string marca, int capacidadCorr, int capacidadExt, int cantidadCorr, int cantidadExt) {
    this->marca = marca;
    this->capacidadCorr = capacidadCorr;
    this->capacidadExt = capacidadExt;
    this->cantidadCorr = cantidadCorr;
    this->cantidadExt = cantidadExt;
    registroCorr = 0;
    registroExt = 0;
}

string Bombas::getMarca() const { return marca; }
int Bombas::getCapacidadCorr() const { return capacidadCorr; }
int Bombas::getCapacidadExt() const { return capacidadExt; }
int Bombas::getCantidadCorr() const { return cantidadCorr; }
int Bombas::getCantidadExt() const { return cantidadExt; }
void Bombas::setMarca(string marca) { this->marca = marca; }
void Bombas::setCapacidad(int capacidadCorr, int capacidadExtra) { this->capacidadCorr = capacidadCorr; this->capacidadExt = capacidadExtra; }
void Bombas::setCantidad(int cantidadCorr, int cantidadExtra) { this->cantidadCorr = cantidadCorr; this->cantidadExt = cantidadExtra; }
void Bombas::setCantidadCorr(int corr) { cantidadCorr = corr; }
void Bombas::setCantidadExt(int ext) { cantidadExt = ext; }

bool Bombas::verificarCantidad(int Demanda, bool tipoGasolina) {
    if (tipoGasolina) {
        return Demanda <= getCantidadCorr();
    } else {
        return Demanda <= getCantidadExt();
    }
}

int Bombas::calcularPrecios(bool tipoGasolina, int cantidad) {
    if (tipoGasolina) {
        return 2000 * cantidad;
    } else {
        return 3500 * cantidad;
    }
}

void Bombas::registrarCorr(int corr) {
    registroCorr += corr;
}
void Bombas::registrarExt(int ext) {
    registroExt += ext;
}

bool Bombas::operator >(const Bombas &bomba2) {
    int registroMiBomba = this->registroCorr + this->registroExt;
    return registroMiBomba > (bomba2.registroCorr + bomba2.registroExt);
}

void Bombas::mostrarDatos() {
    cout << getMarca() << ": Combustible-> Corriente: " << getCantidadCorr()<< " /" << getCapacidadCorr()<< " Vendida(" << registroCorr << ") - Extra: " << cantidadExt << " /" << capacidadExt << " Vendida(" << registroExt << ")\n";
}

void Bombas::llenarAlMaximo() {
    setCantidad(getCapacidadCorr(), getCapacidadExt());
}