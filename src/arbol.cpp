#include "arbol.h"

arbol::arbol()
{
    srand(time(0));
    ronda = 0;
    turno = fallo = false;
    raiz = actual = nullptr;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            mat[i][j] = ' ';
}

arbol::~arbol()
{

}

gato*arbol::worst(){
    gato*ultimo,*worst;
    ultimo = worst = actual = raiz;
    while(actual){
        if(actual->getDown()){
            actual = actual->getDown();
            worst = ultimo = actual;
            continue;
        }
        else if(actual->val > worst->val)
            worst = actual;
        actual = actual->getNext();
        if(actual)
            ultimo = actual;
    }
    while(ultimo){
        if(ultimo<worst)
            return ultimo;
        ultimo = ultimo->getLast();
    }
    return worst;
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

void arbol::jugar(unsigned int n){
    int row,col;
    gato*aux;
    do{
        aux = fallo?worst():best();
        if(aux){
            aux->mostrar();
            if(aux->termino){
                if(!turno)
                    cout << "La IA ha ganado" << endl;
                else
                    cout << "El jugador ha ganado" << endl;
                break;
            }
        }
        cout << "Ronda: " << ronda << endl;
        if(turno){
            fallo = (rand()%n==0);
            //if(fallo)
            //    cout << "fallo" << endl;
            insertar();
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
        if(fallo)
            actual = worst();
        else
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
        if(fallo)
            actual = worst();
        else
            actual = best();
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                mat[i][j] = actual->mat[i][j];
    }else{
        if(fallo)
            actual = worst();
        else
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
