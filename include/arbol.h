#ifndef ARBOL_H
#define ARBOL_H
#include "gato.h"
#include <limits>

class arbol
{
    public:
        int ronda;
        bool turno;
        char mat[3][3];
        gato*raiz, *actual;
        gato*best();
        void jugar();
        void insertar();
        void borrar();
        void mostrar();
        arbol();
        virtual ~arbol();
};

#endif // ARBOL_H
