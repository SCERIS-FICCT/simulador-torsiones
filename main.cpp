///Librerias De GLUT
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
///Libreria Matematica
#include <math.h>
///Libreria Estandar De C
#include <stdio.h>
///Libreria String
#include <string.h>
///Clase Para La Malla
#include "Graficos.h"

///Objeto Malla
Graficos *m;
///Parte Del Zoom
double z=-12;
///Variables Para El Mouse
double alpha, beta;
int xo;
int yo;
///***************
bool deformar = false;

//angulos de rotacion
GLdouble rotx = 0.0;
GLdouble roty = 0.0;
GLdouble rotz = 0.0;

///Variables Para El Menu
bool mostrar = false;  //Visibilidad de los Puntos
bool mover = true;
int iFondo = 0;
typedef enum {FONDO1,FONDO2,FONDO3,MOSTRARPUNTO,OCULTARPUNTO,MOVER,NOMOVER}
opcionesMenu;

static char label[100];

void inline drawString (char *s)
{
 unsigned int i;
 for (i = 0; i<strlen(s); i++)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
}

void onMenu(int opcion) {
 switch(opcion) {
    case FONDO1:
    iFondo = 0;
    break;
    case FONDO2:
    iFondo = 1;
    break;
    case FONDO3:
    iFondo = 2;
    break;
    case MOSTRARPUNTO:
    mostrar=true;/////aqui la funcion mostrar punto.
    break;
    case OCULTARPUNTO:
    mostrar=false;
    break;
    case MOVER:
    mover = true;
    break;
    case NOMOVER:
    mover = false;
    break;
 }
 glutPostRedisplay();
}

 //SubMenu
 void CrearSubMenu(void) {
 int menuFondo, menuPrincipal,menuPuntos,menuMovimiento;

 menuFondo = glutCreateMenu(onMenu);
  glutAddMenuEntry("Negro", FONDO1);
  glutAddMenuEntry("Verde Oscuro", FONDO2);
  glutAddMenuEntry("Blanco", FONDO3);

 menuPuntos = glutCreateMenu(onMenu);
  glutAddMenuEntry("Mostrar", MOSTRARPUNTO);
  glutAddMenuEntry("Ocultar", OCULTARPUNTO);

 menuMovimiento = glutCreateMenu(onMenu);
  glutAddMenuEntry("Mover", MOVER);
  glutAddMenuEntry("No Mover", NOMOVER);

 menuPrincipal = glutCreateMenu(onMenu);
  glutAddSubMenu("Color de Fondo",menuFondo);
  glutAddSubMenu("Puntos",menuPuntos);
  glutAddSubMenu("Movimiento",menuMovimiento);


 glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//dibuja los puntos de control de la superficie
void DrawPoints(void)
{
 int i,j;

 double EjeY,EjeZ;

 //Tamanho De Los Ejes

 EjeY = (m->GetValor(0,0,1))+m->GetDelta();
 EjeZ = (m->GetValor(m->GetPuntosY()-1,m->GetPuntosZ()-1,2))+m->GetDelta();

 glPushAttrib( GL_LIGHTING_BIT );
 glDisable( GL_LIGHTING );

 //cambio el tamaño del pixels para hacerlo mas visible
 glPointSize(4.0f);

 //dibujo todos los puntos de control de la superficie
 glColor3d( 1.0, 0.0, 0.0);
 glBegin(GL_POINTS);
 for(i = 0; i < m->GetPuntosY(); i++){
    for (j = 0; j < m->GetPuntosZ(); j++)
        if (deformar == false){
            glVertex3d(m->GetValor(i,j,0),m->GetValor(i,j,1),m->GetValor(i,j,2));
       }else{
            glVertex3d(m->GetValorFis(i,j),m->GetValor(i,j,1),m->GetValor(i,j,2));
       }
       }
 glEnd();

 if(mostrar==true){ ///Para Mostrar O No Las Coordenadas
    for(i = 0; i < m->GetPuntosY(); i++){
        for (j = 0; j < m->GetPuntosZ(); j++){
            if (deformar == false){
            glRasterPos3d(m->GetValor(i,j,0),m->GetValor(i,j,1),m->GetValor(i,j,2)); //el lugar donde se va a escribir el punto
            sprintf(label,"%0.1f,%0.1f,%0.1f",m->GetValor(i,j,0),m->GetValor(i,j,1),m->GetValor(i,j,2)); //deberia de dibujar el punto
            drawString(label);
            }else{
            glRasterPos3d(m->GetValorFis(i,j),m->GetValor(i,j,1),m->GetValor(i,j,2)); //el lugar donde se va a escribir el punto
            sprintf(label,"%0.1f,%0.1f,%0.1f",m->GetValorFis(i,j),m->GetValor(i,j,1),m->GetValor(i,j,2)); //deberia de dibujar el punto
            drawString(label);
            }

        }
    }

 }


 glColor3f( 0.0, 1.0, 1.0);
 glBegin(GL_LINES);
 for (i = 0; i < m->GetPuntosY(); i++)
     for (j = 0; j < (m->GetPuntosZ())-1; j++)
         {
         if (deformar == false){
         glVertex3d(m->GetValor(i,j,0),m->GetValor(i,j,1),m->GetValor(i,j,2));
         glVertex3d(m->GetValor(i,j+1,0),m->GetValor(i,j+1,1),m->GetValor(i,j+1,2));
         }else{
         glVertex3d(m->GetValorFis(i,j),m->GetValor(i,j,1),m->GetValor(i,j,2));
         glVertex3d(m->GetValorFis(i,j+1),m->GetValor(i,j+1,1),m->GetValor(i,j+1,2));
         }
         }
  for (i = 0; i < m->GetPuntosZ(); i++)
     for (j = 0; j < (m->GetPuntosY())-1; j++)
         {
         if (deformar == false){
         glVertex3d(m->GetValor(j,i,0),m->GetValor(j,i,1),m->GetValor(j,i,2));
         glVertex3d(m->GetValor(j+1,i,0),m->GetValor(j+1,i,1),m->GetValor(j+1,i,2));
         }else{
         glVertex3d(m->GetValorFis(j,i),m->GetValor(j,i,1),m->GetValor(j,i,2));
         glVertex3d(m->GetValorFis(j+1,i),m->GetValor(j+1,i,1),m->GetValor(j+1,i,2));
         }
         }
 glEnd();

                //creamos la linea respecto al plano z(es el vector z)
                glColor3f(2.0f, 0.0f, 0.0f);
                glBegin(GL_LINE_LOOP);
                glVertex3d(0.0, 0.0, EjeZ);
                glVertex3d(0.0, 0.0, (-1)*EjeZ);
                glEnd();

                sprintf(label,"Z");
                glRasterPos3d(0,0,EjeZ+m->GetDelta());
                drawString(label);
                glFlush();
                glutSwapBuffers();

                sprintf(label,"-Z");
                glRasterPos3d(0,0,(-1)*(EjeZ+m->GetDelta()));
                drawString(label);
                glFlush();
                glutSwapBuffers();
                //***********************************
                 //creamos la linea respecto al plano y(es el vector y)
                glColor3f(0.0f, 2.0f, 0.0f);
                glBegin(GL_LINE_LOOP);
                glVertex3d(0.0, EjeY, 0.0);
                glVertex3d(0.0, (-1)*EjeY, 0);
                glEnd();

                sprintf(label,"Y");
                glRasterPos3d(0,EjeY+m->GetDelta(),0);
                drawString(label);
                glFlush();
                glutSwapBuffers();

                sprintf(label,"-Y");
                glRasterPos3d(0,(-1)*(EjeY+m->GetDelta()),0);
                drawString(label);
                glFlush();
                glutSwapBuffers();
                //***********************************

                 //creamos la linea respecto al plano x(es el vector x)
                 glColor3f(0.0f, 0.0f, 2.0f);
                 glBegin(GL_LINE_LOOP);
                 glVertex3d(-4.5, 0.0, 0.0);
                 glVertex3d(4.5, 0.0, 0);
                 glEnd();

                sprintf(label,"X");
                glRasterPos3d(5,0,0);
                drawString(label);
                glFlush();
                glutSwapBuffers();

                sprintf(label,"-X");
                glRasterPos3d(-5,0,0);
                drawString(label);
                glFlush();
                glutSwapBuffers();
                //***********************************

  glFlush();
 glPopAttrib();

}


//dibuja la superficie
void display(void)
{
 glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode( GL_MODELVIEW_MATRIX );

 glLoadIdentity();

 glTranslated(0.0, 0.0, z);
 glRotatef(rotx, 1.0, 0.0, 0.0);
 glRotatef(roty, 0.0, 1.0, 0.0);
 glRotatef(rotz, 0.0, 0.0, 1.0);

 ///Rotar Mouse
  glRotatef(alpha, 1.0f, 0.0f, 0.0f);
  glRotatef(beta, 0.0f, 1.0f, 0.0f);

 double colores[3][3] = {
 { 0.00f, 0.00f, 0.00f}, // 0 - negro
 { 0.06f, 0.25f, 0.13f}, // 1 - verde oscuro
 { 1.00f, 1.00f, 1.00f}  // 2 - Blanco
 };
 glClearColor(colores[iFondo][0],colores[iFondo][1],colores[iFondo][2],1);
 glClear(GL_COLOR_BUFFER_BIT);

 glutSwapBuffers();

 DrawPoints();

 glFlush();
}

///Mover Con El Mouse
void onMouse(int button, int state, int x, int y) {

    if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) {
    xo = x;
    yo = y;
    }
 }

void onMotion(int x, int y) {
    if (mover == true){
    alpha = (alpha + (y - yo));
    beta = (beta + (x - xo));
    xo = x;
    yo = y;
    glutPostRedisplay();
    }
}
///**********************

void reshape(int w, int h)
{
 glViewport (0, 0, (GLsizei) w, (GLsizei) h);
 glMatrixMode (GL_PROJECTION);
 glLoadIdentity ();
 gluPerspective(100, (GLdouble) w/(GLdouble) h, 0.5, 50.0);
 glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {

   case 27:
      exit(0);
      break;
   case '+':
      z = z + 1.0f;
      glutPostRedisplay();
      break;
   case '-':
      z = z - 1.0f;
      glutPostRedisplay();
      break;
      ///Redibujado de la Malla
   case 'r':
    printf("\nIntroducir Nuevos Valores\n");
    m = new Graficos();
    m->CrearMalla();
     ///Print Inercia De Torsion
    printf("\nIt = %lf\n",m->GetInerciaTorsion());
     ///Angulo Torsor
    printf("\n0 = %lf rad\n",(2707246/(980*m->GetInerciaTorsion())));
    printf("\nCantidad De Ecuaciones = %d\n",m->GetCantEcua());
    ///Limpiar Buffer
    glClearAccum(0,0,0,0);
    glClearColor(0,0,0,0);
    glClearDepth(0);
    glClearIndex(0);
    glClearStencil(0);
    glEnd();
    glutPostRedisplay();
      break;
    case 'n':
    deformar = true;
    ///Limpiar Buffer
    glClearAccum(0,0,0,0);
    glClearColor(0,0,0,0);
    glClearDepth(0);
    glClearIndex(0);
    glClearStencil(0);
    glEnd();
    glutPostRedisplay();
      break;
    case 'm':
    deformar = false;
    ///Limpiar Buffer
    glClearAccum(0,0,0,0);
    glClearColor(0,0,0,0);
    glClearDepth(0);
    glClearIndex(0);
    glClearStencil(0);
    glEnd();
    glutPostRedisplay();
      break;
   }
}

int main(int argc, char** argv)
{
 ///Contruccion Del Objeto

 m = new Graficos();

 ///Crear Malla

 m->CrearMalla();

 ///Cantidad DE Ecuaciones

 printf("\nCantidad De Ecuaciones = %d\n",m->GetCantEcua());

 ///Print Inercia De Torsion

 printf("\nIt = %lf\n",m->GetInerciaTorsion());

 ///Angulo Torsor

 printf("\n0 = %lf rad\n",(2707246/(980*m->GetInerciaTorsion())));

//Construccion De La Figura
 glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
 glutInit(&argc, argv);
 glutInitWindowSize (800, 800);
 glutInitWindowPosition (400, 150);
 glutCreateWindow ("Simulador VMNB2C3");
 ///************
 CrearSubMenu();
 ///************
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 glutDisplayFunc(display);
 ///Mover Mouse
 glutMouseFunc(onMouse);
 glutMotionFunc(onMotion);
 ///******importante no borrar*****
 glutMainLoop();
 return 0;
}
