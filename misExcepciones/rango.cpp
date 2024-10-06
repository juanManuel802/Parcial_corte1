#include <iostream>
#include <exception>
#include "rango.h"
using namespace std;


const char* rango::what() const throw() {
    return "Valor fuera del rango";
}