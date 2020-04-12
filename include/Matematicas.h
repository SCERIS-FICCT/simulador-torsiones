#ifndef MATEMATICAS_H
#define MATEMATICAS_H

///Librerias De GLUT
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Matematicas
{
    public:
        ///Crear Matrices
        void CrearMatricesCalc(int pY,int pZ);
        ///Llenar Matrices
        void LlenarMatricesCalc();
        ///Generar Formulas
        void GenerarFormulas();
        ///Cantidad De Ecuaciones
        int GetCantEcua();
        ///Elementos De La Matriz De Ecuaciones
        GLdouble GetSisEcua(int i,int j);
        ///Operaciones Con Matrices
        void Pivotear(int f,int c);
        void Permutar(int f1,int f2);
        void Adicion(int f1,int f2,GLdouble n);
        void Multiplicacion(int f,GLdouble n);
        ///Metodo De Gauss Jordan
        void MetodoGaussJordan();
        ///Generar F
        void GenerarF();
        ///Calcular Inercia De Torsion
        void CalcularIt();
        ///Valor De La Inercia De Torsion
        double GetIt();
        ///Constructor
        Matematicas(int pY,int pZ,double d);
        ///Destructor
        virtual ~Matematicas();
    protected:
    private:
        double delta;
        //Inercia De Torsion
        double It;
        //Matriz Para Ubicar Correctamente La Matriz De Ecuaciones
        int **MGfis;
        int pgY,pgZ; //Dimension De La Matriz
        //Matriz De Ecuaciones
        GLdouble **MEcua;
        int peY,peZ; //Dimension DE La Matriz
        //Matriz De F
        GLdouble **MF;
        int pfY,pfZ;
};

#endif // MATEMATICAS_H
