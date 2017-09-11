void generarPuntos(set<Punto>& P,int n){
	while(P.size()<n){
		double x=XorShift((long long)CAMARA.WIDTH);
		double y=XorShift((long long)CAMARA.HEIGHT);
		P.insert(Punto(x,y));
	}
}

void crearGrafo(int n, Grafo* G){
	set<Punto> P;
	generarPuntos(P,n);
	vector<Punto> V;
	for (auto it=P.begin();it!=P.end();it++){
		V.push_back(Punto(it->x-CAMARA.WIDTH/2,it->y-CAMARA.HEIGHT/2));
	}
	delaunayTriangulation(V,G);
}
