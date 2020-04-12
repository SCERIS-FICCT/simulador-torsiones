#ifndef GRAFICOS_H
#define GRAFICOS_H

#include <stdio.h>
///Clase Matematica
#include "Matematicas.h"
#include <math.h>
///Librerias De GLUT
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
///Constante Para X
const double a = 0;

class Graficos
{
    public:
        ///Constructor
        Graficos();
        ///Aproximador
        void AdaptarMalla();
        ///Construir Matriz
        void ConstruirMatriz();
        ///Cargar Puntos
        void CargarPuntos();
        ///Crear Malla
        void CrearMalla();
        ///Obtener Valor
        GLdouble GetValor(int i,int j,int eje);
        ///Obtener Puntos
        int GetPuntosY();
        int GetPuntosZ();
        ///Valores De Matematicas
        GLdouble GetSisEcua(int i,int j);
        ///Cantidad DE Ecuaciones
        int GetCantEcua();
        ///Cargar Fis
        void CargarFis();
        ///Obtener Valor De Las Fis
        GLdouble GetValorFis(int i,int j);
        ///Obtener Inercia De Torsion
        double GetInerciaTorsion();
        ///Get Delta
        double GetDelta();
        ///Destructor
        virtual ~Graficos();

    protected:
    private:
        ///Matriz De Puntos
        GLdouble ***puntos;
        ///Dimensiones
        double base,altura,delta;
        ///Cantidad De Puntos
        int pY,pZ;
        ///Objeto De La Clase Matemeticas
        Matematicas *mat;
        ///Matriz De fis
        /*Solo Para Cambiar Los Valores En X
        Por tal Motivo Tendra La Misma Dimension
        Que La Matriz DE Puntos*/
        GLdouble **fis;
};

#endif // GRAFICOS_H
