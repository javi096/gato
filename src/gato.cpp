#include "gato.h"

gato::gato(char mat[3][3],int row,int col)
{
    sig = las = up = down = nullptr;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            this->mat[i][j] = mat[i][j];
    this->fila = (row>2||row<0)?0:row;
    this->columna = (col>2||col<0)?0:col;
    val = 0;
    termino = false;
    jugar();
}

gato::gato(char mat[3][3])
{
    sig = las = up = down = nullptr;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            this->mat[i][j] = mat[i][j];
    this->fila = 0;
    this->columna = 0;
    val = 0;
    termino = perder();
}

gato::~gato()
{

}

gato*gato::getDown(){
    return down;
}

gato*gato::getUp(){
    return up;
}

gato*gato::getNext(){
    return sig;
}

gato*gato::getLast(){
    return las;
}

void gato::setDown(gato*down){
    this->down = down;
}

void gato::setUp(gato*up){
    this->up = up;
}

void gato::setNext(gato*sig){
    this->sig = sig;
}

void gato::setLast(gato*las){
    this->las = las;
}

bool gato::perder(){
    int row[3] = {0}, col[3] = {0}, dia[2] = {0};
    for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(mat[i][j]=='X')
				row[i]++;
			if(row[i]==3)
				return true;
		}
	}

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(mat[j][i]=='X')
				col[i]++;
			if(col[i]==3)
				return true;
		}
	}

    for(int i=0;i<3;i++){
        if(mat[i][i]=='X')
            dia[0]++;
        if(dia[0]==3)
            return true;
    }

    for(int i=2;i>=0;i--){
        if(mat[2-i][i]=='X')
            dia[1]++;
        if(dia[1]==3)
            return true;
    }
    return false;
}

void gato::jugar(){
    int esquinas = 0, row[3] = {0}, col[3] = {0}, dia[2] = {0};
    mat[0][0]==' '?esquinas++:0;
    mat[0][2]==' '?esquinas++:0;
    mat[2][0]==' '?esquinas++:0;
    mat[2][2]==' '?esquinas++:0;
    mat[fila][columna] = 'O';
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(mat[i][j]=='O')
				row[i]++;
			if(row[i]==3 && fila==i){
				val = 5;
				termino = true;
				return;
			}
		}
	}

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(mat[j][i]=='O')
				col[i]++;
			if(col[i]==3 && columna==i){
				val = 5;
				termino = true;
				return;
			}
		}
	}

    for(int i=0;i<3;i++){
        if(mat[i][i]=='O')
            dia[0]++;
        if(dia[0]==3 && fila == columna){
            val = 5;
            termino = true;
            return;
        }
    }

    for(int i=2;i>=0;i--){
        if(mat[2-i][i]=='O')
            dia[1]++;
        if(dia[1]==3 && (fila+columna)==2 ){
            val = 5;
            termino = true;
            return;
        }
    }

    for(int i=0;i<3;i++)
         row[i] = col[i] = dia[i] = 0;

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(mat[i][j]=='X')
				row[i]++;
			if(row[i]==2 && fila==i){
				val = 4;
				return;
			}
		}
	}

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(mat[j][i]=='X')
				col[i]++;
			if(col[i]==2 && columna==i){
				val = 4;
				return;
			}
		}
	}

    for(int i=0;i<3;i++){
        if(mat[i][i]=='X')
            dia[0]++;
        if(dia[0]==2 && fila == columna){
            val = 4;
            return;
        }
    }

    for(int i=2;i>=0;i--){
        if(mat[2-i][i]=='X')
            dia[1]++;
        if(dia[1]==2 && (fila+columna)==2 ){
            val = 4;
            return;
        }
    }
	if(fila == 1 && columna == 1){
        val = 3;
        return;
	}

    if( esquinas>2 && (fila == 0 || fila == 2) && (columna == 0 || columna == 2) ){
        val = 2;
        return;
    }

    if( (fila==0&&columna==1) || (fila==1&&columna==0) || (fila==1&&columna==2) || (fila==2&&columna==1) ){
        val = 1;
        return;
    }
}

void gato::mostrar(){
    cout << "--------------\n";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
    cout << "--------------\n";
    //cout << "Val: " << val << endl;
}
