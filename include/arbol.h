#ifndef ARBOL_H
#define ARBOL_H
#include "gato.h"
#include <limits>

class arbol
{
    public:
        int ronda;
        bool turno, fallo;
        char mat[3][3];
        gato*raiz, *actual;
        gato*best();
        gato*worst();
        void jugar(unsigned int);
        void insertar();
        void borrar();
        void mostrar();
        arbol();
        virtual ~arbol();
};

#endif // ARBOL_H
