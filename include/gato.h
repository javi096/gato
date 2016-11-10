#ifndef GATO_H
#define GATO_H
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class gato
{
    public:
        char mat[3][3];
        int val, fila, columna;
        gato(char[3][3],int,int);
        gato(char[3][3]);
        void jugar();
        bool perder();
        void mostrar();
        gato*getDown();
        gato*getUp();
        gato*getNext();
        gato*getLast();
        void setDown(gato*);
        void setUp(gato*);
        void setNext(gato*);
        void setLast(gato*);
        virtual ~gato();
        bool termino;
        gato*sig,*las,*up,*down;
};

#endif // GATO_H
