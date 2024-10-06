#ifndef OPERADOR_H
#define OPERADOR_H
#include "bomba.h"
#include <string>
using std::string;

class Operador {
private:
    Bombas bomba;
public:
    Operador(Bombas bomba);
    Bombas getBomba() const;

    void recargarBomba(Bombas &provedor);
};

#endif //OPERADOR_H