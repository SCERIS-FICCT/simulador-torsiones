#include "Graficos.h"

Graficos::Graficos()
{
//Datos Para Construir La Figura
 ///Pedir Datos
 printf("\nColocar Una Base: ");
 scanf("%lf",&base);
 printf("\nColocar Una Altura: ");
 scanf("%lf",&altura);
 printf("\nColocar Una Delta: ");
 scanf("%lf",&delta);
    while (!((delta <= altura/2)&&(delta <= base/2))){
    printf("\nDelta Muy Grande\n");
    printf("\nColocar Una Delta: ");
    scanf("%lf",&delta);
    }
}

void Graficos::AdaptarMalla()
{
int i,j;
double p,w;

 p = w = 0;

 for (i = 0; p < (altura/2); i++){
    p = p + delta;
    }

 for (j = 0; w < (base/2); j++){
    w = w + delta;
    }

 ///El caso del else Es Para Cuando el delta es exacto
    if (p+p > altura){
        altura = (p*2)-2*delta;
        pY = i*2-1;
    }else{
        altura = p*2;
        pY = i*2+1;
    }

    if (w+w > base){
        base = (w*2)-2*delta;
        pZ = j*2-1;
    }else{
        base = w*2;
        pZ = j*2+1;
    }
   ///*************************************************
    if ((pY-1)%4 != 0)
    {
        pY = pY-2;
        altura = altura - (delta+delta);
    }

    if ((pZ-1)%4 != 0)
    {
        pZ = pZ-2;
        base = base - (delta+delta);
    }

}

void Graficos::ConstruirMatriz()
{
int i,j;

///Matriz De Puntos Y De Fis

 puntos = new GLdouble **[pY];
 fis = new GLdouble *[pY];

 for ( i = 0; i < pY; i++) {
        puntos[i] = new GLdouble *[pZ];
        fis[i] = new GLdouble [pZ];
    }

 for ( i = 0; i < pY; i++) {
    for ( j = 0; j < pZ; j++){
        puntos[i][j] = new GLdouble[3];
        }
    }
}

void Graficos::CargarPuntos()
{
int i,j;
double p,w;

 p = (altura/2);

 for ( i = 0; i < pY; i++){
    w = (base/2)*(-1);
    for ( j = 0; j < pZ; j++){
        puntos[i][j][0] = a;
        puntos[i][j][1] = p;
        puntos[i][j][2] = w;
        w = w+delta;
    }
    p = p-delta;
 }

}

void Graficos::CrearMalla()
{
    ///Adapta La Graficos (Aproxima)
    AdaptarMalla();
    ///Crea La Matriz Dinamica
    ConstruirMatriz();
    ///Cargar Los Puntos
    CargarPuntos();
    ///Crear Objeto Matematicas
    mat = new Matematicas(pY,pZ,delta);
    ///Cargar Fis
    CargarFis();
}

GLdouble Graficos::GetValor(int i,int j,int eje)
{
    return puntos[i][j][eje];
}

int Graficos::GetPuntosY()
{
    return pY;
}

int Graficos::GetPuntosZ()
{
    return pZ;
}

GLdouble Graficos::GetSisEcua(int i,int j)
{
    return (mat->GetSisEcua(i,j));
}

int Graficos::GetCantEcua()
{
    return (mat->GetCantEcua());
}

void Graficos::CargarFis()
{
int i,j,k,cY,cZ;
///Cantidad De Puntos En Un Cuadrante
cY = ((pY-1)/2)+1;
cZ = ((pZ-1)/2)+1;
    ///Metodo Para Cargar Los Valores de Las Fis

    k = cZ;//Para Ubicarse Con Las Fi Validas

    ///Carga Primer Cuadrante (Izq-Sup)

    for (i = 0;i < cY-1;i++){
        for (j = 0;j < cZ-1;j++){
            fis[i][j] = mat->GetSisEcua(k,(mat->GetCantEcua()));
            k++;
        }
        k++;
    }

    k = 2;

    ///Carga Segundo Cuadrante (Izq-Inf)
    for (i = cY;i < pY;i++){
        for (j = 0;j < cZ-1;j++){
            fis[i][j] = (-1)*fis[i-k][j];
        }
        k = k + 2;
    }

    k = 2;

    ///Carga Tercer Cuadrante
    for (i = 0;i < cY-1;i++){
        for (j = cZ;j < pZ;j++){
            fis[i][j] = (-1)*fis[i][j-k];
            k = k + 2;
        }
        k = 2;

    }

    ///Carga Cuarto Cuadrante

    k = 2;

    for (i = cY;i < pY;i++){
        for (j = cZ;j < pZ;j++){
            fis[i][j] = (-1)*fis[i][j-k];
            k = k+2;
        }
        k = 2;
    }

    ///Ajustando Ejes

    /*for (i = 0;i < pY;i++){
        fis[cY-1][i] = 0;
    }

    for (j = 0;i < pZ;j++){
        fis[j][cZ-1] = 0;
    }*/
}

double Graficos::GetInerciaTorsion()
{
    return (mat->GetIt());
}

GLdouble Graficos::GetValorFis(int i,int j)
{
    return (fis[i][j]);
}

double Graficos::GetDelta()
{
    return (delta);
}

Graficos::~Graficos()
{
    ///Destructor
}
