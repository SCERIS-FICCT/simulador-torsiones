#include "Matematicas.h"

void Matematicas::CrearMatricesCalc(int pY,int pZ)
{
int i;

///Matriz DE Posiciones De Las Ecuaciones

 pgY = ((pY-1)/2)+1;
 pgZ = ((pZ-1)/2)+1;

 MGfis = new int *[pgY];

 for ( i = 0; i < pgY; i++) {
        MGfis[i] = new int [pgZ];
    }

///Matriz De Ecuaciones

 peY = (pgY*pgZ)-1;
 peZ = (pgY*pgZ);

 MEcua = new GLdouble *[peY];

 for ( i = 0; i < peY; i++) {
        MEcua[i] = new GLdouble [peZ];
    }

    ///Matriz De F

 pfY = pgY;
 pfZ = pgZ;

 MF = new GLdouble *[pfY];

 for ( i = 0; i < pfY; i++) {
        MF[i] = new GLdouble [pfZ];
    }
}

void Matematicas::LlenarMatricesCalc()
{
int i,j,k;

 ///Matriz De Ecuaciones
 for (i = 0;i < peY;i++){
    for (j = 0;j < peZ;j++){
        MEcua[i][j] = 0;
    }
 }

 ///Matriz De Posiciones

 k = -1;

 for (i = 0;i < pgY;i++){
    for (j = 0;j < pgZ;j++){
        MGfis[i][j] = k;
        k++;
    }
 }
}

void Matematicas::GenerarFormulas()
{
 int i,j,k;

 ///Numero De Ecuaciones

 k = 0;

 ///Ecuaciones Finitas
 for (i = 1;i < pgY;i++){
    for (j = 1;j < pgZ;j++){
        MEcua[k][MGfis[i][j]] = -4;
        MEcua[k][MGfis[i][j-1]] = 1;
        if (j != (pgZ-1)){
            MEcua[k][MGfis[i][j+1]] = 1;
        }
        if (i != (pgY-1)){
            MEcua[k][MGfis[i+1][j]] = 1;
        }
        MEcua[k][MGfis[i-1][j]] = 1;
        k++;
    }
 }

 ///Ecuaciones De Contorno
 for (j = 1;j < pgZ;j++){
    MEcua[k][MGfis[0][j]] = 1;
    MEcua[k][MGfis[2][j]] = -1;
    MEcua[k][peZ-1] = (2*delta)*(delta*(pgZ-j));
    k++;
 }

 for (i = 1;i < pgY;i++){
    MEcua[k][MGfis[i][0]] = 1;
    MEcua[k][MGfis[i][2]] = -1;
    MEcua[k][peZ-1] = (-2*delta)*(delta*(pgY-i));
    k++;
 }

///Si Todo Es Correcto El Valor De K sera El numero De Ec.
}

int Matematicas::GetCantEcua()
{
    return peY;
}

GLdouble Matematicas::GetSisEcua(int i,int j)
{
    return (MEcua[i][j]);
}

void Matematicas::Pivotear(int f,int c)
{
    int i = f;
    int x = f+1;
    while (x<peY)
    {
        if((MEcua[x][c])>(MEcua[f][c]))
        {
            f = x;
        }
        x++;
    }
    Permutar(i,f);
}

void Matematicas::Permutar(int f1,int f2)
{
    GLdouble aux;
    for (int j = 0;j < peZ;j++){
       aux =  MEcua[f1][j];
       MEcua[f1][j] = MEcua[f2][j];
       MEcua[f2][j] = aux;
    }
}

void Matematicas::Adicion(int f1,int f2,GLdouble n)
{
    for (int j = 0;j < peZ;j++){
        MEcua[f1][j] = MEcua[f1][j] + ((MEcua[f2][j])*n);
    }
}
void Matematicas::Multiplicacion(int f,GLdouble n)
{
    for (int j = 0;j < peZ;j++){
        MEcua[f][j] = ((MEcua[f][j])*n);
    }
}

void Matematicas::MetodoGaussJordan()
{
    for (int i = 0;i < peY;i++){
        Pivotear(i,i);
            Multiplicacion(i,(1/(MEcua[i][i])));
            for (int j = 0;j < peY;j++){
                if (j != i){
                    Adicion(j,i,((-1)*(MEcua[j][i])));
                }
            }
    }
}

void Matematicas::GenerarF()
{
 int i,j;

 ///Generar F

 for (i = 0;i < pfY-2;i++){
    for (j = 0;j < pfZ-1;j++){
        if (j == pfZ-2)
        {
            MF[i][j] = (((pfY-i-1)*delta)*((pfY-i-1)*delta))+(((pfZ-j-1)*delta)*((pfZ-j-1)*delta))+(((MEcua[MGfis[i+1][j]][peY]))*((pfY-i-1)/2))-(((MEcua[MGfis[i][j+1]][peY])-(MEcua[MGfis[i+2][j+1]][peY]))*((pfZ-j-1)/2));
        }else{
            MF[i][j] = (((pfY-i-1)*delta)*((pfY-i-1)*delta))+(((pfZ-j-1)*delta)*((pfZ-j-1)*delta))+(((MEcua[MGfis[i+1][j]][peY])-(MEcua[MGfis[i+1][j+2]][peY]))*((pfY-i-1)/2))-(((MEcua[MGfis[i][j+1]][peY])-(MEcua[MGfis[i+2][j+1]][peY]))*((pfZ-j-1)/2));
        }
    }
 }

 ///Casos De Los Ejes y La Penultima Fila

 //Penultima Fila

 i = pfY-2;

 for (j = 0;j < pfZ-1;j++)
 {
    if (j == pfZ-2){
        MF[i][j] = (((pfY-i-1)*delta)*((pfY-i-1)*delta))+(((pfZ-j-1)*delta)*((pfZ-j-1)*delta))+((MEcua[MGfis[i+1][j]][peY])*((pfY-i-1)/2))-((MEcua[MGfis[i][j+1]][peY])*((pfZ-j-1)/2));
    }else{
        MF[i][j] = (((pfY-i-1)*delta)*((pfY-i-1)*delta))+(((pfZ-j-1)*delta)*((pfZ-j-1)*delta))+(((MEcua[MGfis[i+1][j]][peY])-(MEcua[MGfis[i+1][j+2]][peY]))*((pfY-i-1)/2))-((MEcua[MGfis[i][j+1]][peY])*((pfZ-j-1)/2));
    }
 }

 //Eje Y

 j = pfZ-1;

 for (i = 0;i < pfY-1;i++)
 {
    MF[i][j] = (((pfY-i-1)*delta)*((pfY-i-1)*delta))+((2*(MEcua[MGfis[i+1][j-1]][peY]))*(((pfY-i-1))/2));
 }

 //Eje Z

 i = pfY-1;

 for (j = 0;j < pfZ-1;j++)
 {
    MF[i][j] = (((pfZ-j-1)*delta)*((pfZ-j-1)*delta))-((2*(MEcua[MGfis[i-1][j+1]][peY]))*(((pfZ-j-1))/2));
 }

 //Ultimo Elemento

MF[pfY-1][pfZ-1] = 0;

}

void Matematicas::CalcularIt()
{
 int i,j;

 It = 0;

 ///Haciendo El Analisis A la Matriz De F

    for (i = 1;i < pfY;i = i + 2){
        for (j = 1;j < pfZ;j = j + 2){
            It = It + (((delta*delta)/9)*((16*(MF[i][j]))+(4*(MF[i-1][j]))+(4*(MF[i+1][j]))+(4*(MF[i][j-1]))+(4*(MF[i][j+1]))+(MF[i-1][j-1])+(MF[i-1][j+1])+(MF[i+1][j-1])+(MF[i+1][j+1])));
        }
    }

    ///Multiplicar Por Los 4 Cuadrantes

    It = It*4;

}

double Matematicas::GetIt()
{
    return (It);
}

Matematicas::Matematicas(int pY,int pZ,double d)
{
    delta = d;
    ///Generar Matrices Para El Calculo Matematico
    CrearMatricesCalc(pY,pZ);
    ///Llenar Las Matrices
    LlenarMatricesCalc();
    ///Generar Formulas
    GenerarFormulas();
    ///Resolver Ecuaciones
    MetodoGaussJordan();
    ///Generar F
    GenerarF();
    ///Calcular Inercia De Torsion
    CalcularIt();
}

Matematicas::~Matematicas()
{
    //dtor
}
