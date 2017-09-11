/**
* Interfaz para graficar un Grafo
**/

void graficarArista(Punto A, Punto B,bool obstaculo=false){
	glVertex2f(A.x+CAMARA.CENTER.x,A.y+CAMARA.CENTER.y);
	glVertex2f(B.x+CAMARA.CENTER.x,B.y+CAMARA.CENTER.y);
}

void graficarArista(Nodo* A, Nodo* B,bool obstaculo=false){
	graficarArista((*A).punto,(*B).punto, obstaculo);
}

void graficoProfundidad(Nodo* u,set<pair<int,int> >& Obstaculos,set<int>& S,int padreID=-1){
	S.insert(u->ID);
	for (auto it=(*u).aristas.begin();it!=(*u).aristas.end();it++){
		glColor3f(1.0f,1.0f,0);
		if(S.find(it->first)==S.end()){
			if(Obstaculos.find(make_pair(u->ID,it->first))!=Obstaculos.end()){
				glColor3f(1.0f,0.5f,0);
			}
			graficarArista(u,it->second);
			graficoProfundidad(it->second,Obstaculos,S,u->ID);
		} else if((it->second)->ID!=padreID){
			if(Obstaculos.find(make_pair(u->ID,it->first))!=Obstaculos.end()){
				glColor3f(1.0f,0.5f,0);
			}
			graficarArista(u,it->second);
		}
	}
}

void graficarAristasDeGrafo(Grafo* G){
	glBegin(GL_LINES);
		glColor3f(1.0f,1.0f,0);
		set<int> S;
		if(G->size){
			graficoProfundidad((G->nodos.begin())->second,G->Obstaculos,S);
		}
	glEnd();
}

void graficarCaminoDeGrafoProfundidad(Grafo* G,int begin,int end){
	vector<pair<int,int> > Camino;
	if (G->bfs(begin,end,Camino)){
		cout << "Llego" << endl;
	} else {
		cout << "No Llego" << endl;
	}
	glBegin(GL_LINES);
		glColor3f(0.0f,0.4f,1.0f);
		if(G->size){
			for (int i=0;i<Camino.size();i++){
				graficarArista((G->nodos)[Camino[i].first],(G->nodos)[Camino[i].second]);
			}
		}
	glEnd();
	glPointSize(8);
	glBegin(GL_POINTS);
		glColor4f( 0.95f, 0.207, 0.031f, 1.0f );
		glVertex2i(G->nodos[0]->punto.x+CAMARA.CENTER.x,G->nodos[0]->punto.y+CAMARA.CENTER.y);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2i(G->nodos[G->size-1]->punto.x+CAMARA.CENTER.x,G->nodos[G->size-1]->punto.y+CAMARA.CENTER.y);
	glEnd();
}

void graficarCaminoMejorElPrimero(Grafo *G,int begin,int end){
	vector<pair<int,int> > Camino;
	if(G->mejorElPrimero(begin,end,Camino)){
		cout << "Llego" << endl;
	} else {
		cout << "No Llego" << endl;
	}
	glBegin(GL_LINES);
		glColor3f(0.0f,0.4f,1.0f);
		if(G->size){
			for (int i=0;i<Camino.size();i++){
				graficarArista((G->nodos)[Camino[i].first],(G->nodos)[Camino[i].second]);
			}
		}
	glEnd();
	glPointSize(8);
	glBegin(GL_POINTS);
		glColor4f( 0.95f, 0.207, 0.031f, 1.0f );
		glVertex2i(G->nodos[0]->punto.x+CAMARA.CENTER.x,G->nodos[0]->punto.y+CAMARA.CENTER.y);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2i(G->nodos[G->size-1]->punto.x+CAMARA.CENTER.x,G->nodos[G->size-1]->punto.y+CAMARA.CENTER.y);
	glEnd();
}
