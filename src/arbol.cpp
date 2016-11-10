#include "arbol.h"

arbol::arbol()
{
    ronda = 0;
    turno = false;
    raiz = actual = nullptr;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            mat[i][j] = ' ';
}

arbol::~arbol()
{

}

gato*arbol::best(){
    gato*best = actual = raiz;
    while(actual){
        if(actual->getDown()){
            actual = actual->getDown();
            best = actual;
            continue;
        }
        else if(actual->val > best->val)
            best = actual;
        actual = actual->getNext();
    }
    return best;
}

void arbol::jugar(){
    int row,col;
    do{
        cout << "Ronda: " << ronda << endl;
        if(turno){
            insertar();
            best()->mostrar();
            continue;
        }
        row = col = 0;
        if( cout << "Row: " && cin>>row ){
            if( cout << "Col: " && cin>>col ){
                if( row<0 || row>2 || col<0 || col>2){
                    cerr << "Digita un numero base 10 menor que 2 y mayor que 0" << endl;
                    continue;
                }
                if(mat[row][col]!=' '){
                    cerr << "Espacio ocupado, selecciona un espacio valido" << endl;
                    continue;
                }
                mat[row][col] = 'X';
                insertar();
                continue;
            }
        }
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }while(ronda<9);
}

void arbol::insertar(){
    if(!raiz)
        raiz = new gato(mat);
    else if(turno){
        bool first = true;
        actual = best();
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(mat[i][j]==' '){
                    gato*nuevo = new gato(mat,i,j);
                    if(first){
                        nuevo->setUp(actual);
                        actual->setDown(nuevo);
                        actual = actual->getDown();
                        first = false;
                    }
                    else{
                        nuevo->setLast(actual);
                        actual->setNext(nuevo);
                        actual = actual->getNext();
                    }
                }
        actual = best();
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                mat[i][j] = actual->mat[i][j];
    }else{
        actual = best();
        gato*nuevo = new gato(mat);
        nuevo->setUp(actual);
        actual->setDown(nuevo);
    }
    turno = !turno;
    ronda++;
}

void arbol::borrar(){
    gato*last = nullptr;
    actual = best();
    while(actual){
        if(actual==raiz){
            delete raiz;
            raiz = nullptr;
            break;
        }
        while(actual->getNext()){
            actual = actual->getNext();
        }
        while(actual){
            if(actual->getUp())
                last = actual->getUp();
            gato*aux = actual;
            actual = actual->getLast();
            delete aux;
        }
        actual = last;
    }
}

void arbol::mostrar(){
    if(!raiz)
        cout << "El arbol esta vacio" << endl;
    int n = 0;
    gato*last = nullptr;
    actual = best();
    while(actual){
        if(actual==raiz){
            raiz->mostrar();
            break;
        }
        while(actual->getNext()){
            actual = actual->getNext();
        }
        while(actual){
            actual->mostrar();
            if(actual->getUp())
                last = actual->getUp();
            actual = actual->getLast();
            n++;
        }
        actual = last;
    }
    cout << "Total: " << n << endl;
}
