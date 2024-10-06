#ifndef BOMBA_H
#define BOMBA_H
#include <string>
using std::string;

class Bombas {
private:
    string marca;
    int capacidadCorr, capacidadExt, cantidadCorr, cantidadExt;
    int registroCorr;
    int registroExt;
    public:
    Bombas();
    Bombas(string marca, int capacidadCorr, int capacidadExt, int cantidadCorr, int cantidadExt);
    string getMarca() const;
    int getCapacidadCorr() const;
    int getCapacidadExt() const;
    int getCantidadCorr() const;
    int getCantidadExt() const;
    void setMarca(string marca);
    void setCapacidad(int capacidadCorr, int capacidadExtra);
    void setCantidad(int cantidadCorr, int cantidadExtra);
    void setCantidadCorr(int corr);
    void setCantidadExt(int ext);

    

    bool verificarCantidad(int Demanda, bool tipoGasolina);
    int calcularPrecios(bool tipoGasolina, int cantidad);

    void registrarCorr(int corr);
    void registrarExt(int ext);
        
    bool operator >(const Bombas &bomba2);
    void mostrarDatos();
    void llenarAlMaximo();
};

#endif //BOMBA_H