#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include "bomba.h"
using std::string;
class Cliente {
    private:
    string nombre;
    float dinero;
    int corriente;
    int extra;

    public:
    Cliente();
    Cliente(string nombre, float dinero, int corriente, int extra);
    string getNombre() const;
    float getDinero() const;
    int getCorriente() const;
    int getExtra() const;
    void setDinero(int dinero);
    void setCorriente(int corriente);
    void setExtra(int extra);

    void comprarGasolina (string tipoGasolina, int cantidad, Bombas &bomba, Bombas &provedor);
    void mostrarDatos();
};
#endif //CLIENTE_H