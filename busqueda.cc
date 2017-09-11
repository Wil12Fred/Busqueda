#include <GLUT/glut.h>   
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <queue>

using namespace std;

#include "geometria.h" //Punto y propiedades basicas
#include "grafo.h"
#include "camara.h"
#include "windowControl.h"
#include "grafoInterfaz.h"
#include "xorshift.h" //semilla y función para puntos aleatorios
#include "delaunay.h" //para la triangulación del mapa
#include "grafoAlgoritmos.h" //creación del grafo y algoritmos de busqueda

Grafo grafo;

/**
*Renderizar escena
**/
void renderScene(void){
	if(CAMARA.transform){ // Si se sufrio una transformación (eg. ajuste de la ventana, movimiento, zoom)
		gluOrtho2D(-CAMARA.WIDTH/2,CAMARA.WIDTH/2,-CAMARA.HEIGHT/2,CAMARA.HEIGHT/2);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Borrar datos de la escena
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glScalef(CAMARA.rotate,CAMARA.rotate,1.0f);//Realizar transformación de escala (zoom_in(x2), zoom_out(x.5))
		graficarAristasDeGrafo(&grafo);//Graficar la escena con la traslación de camara
		if(!CAMARA.opcionHeuristica)
			graficarCaminoDeGrafoProfundidad(&grafo,0,grafo.size-1);
		else 
			graficarCaminoMejorElPrimero(&grafo,0,grafo.size-1);
		CAMARA.transform=false;//Se realizo todas las transformaciones
		glutSwapBuffers();
	}
}

int main(int argc, char **argv){
	cout << "Numero de Nodos: ";
	int n;
	cin >> n;
	SeedXorShift();
	crearGrafo(n,&grafo);
	cout << "Opcion 1: Busqueda en Profundidad" << endl;
	cout << "Opcion 2: Heuristica Mejor el Primero" << endl;
	int opcion;
	cin >> opcion;
	if(opcion==2){
		CAMARA.opcionHeuristica=true;
	}
	//Iniciando propiedades de la ventana
	glutInit(&argc, argv);  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-CAMARA.WIDTH)/2, (glutGet(GLUT_SCREEN_HEIGHT)-CAMARA.HEIGHT)/2);
	glutInitWindowSize(CAMARA.WIDTH, CAMARA.HEIGHT);
	glutCreateWindow("Busqueda");

	//Iniciando funciones de interacción
	glutDisplayFunc(renderScene);
	glutSpecialFunc(keyPress);
	glutReshapeFunc(reshapeScene);

	//start animation
	glutMainLoop();

	return 0;
}
