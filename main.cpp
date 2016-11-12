#include "arbol.h"

int main()
{
    arbol a;
    a.jugar(5);
    a.borrar();
    if(cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        cin.get();
    }
   return 0;
}
