#ifndef RANGO_H
#define RANGO_H

#include <exception>
using namespace std;

class rango: public exception {
public:
    const char* what() const throw();
};

#endif
