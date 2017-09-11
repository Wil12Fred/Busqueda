struct triple {
    int i, j, k;
    triple() {}
    triple(int i, int j, int k) : i(i), j(j), k(k) {}
};

void delaunayTriangulation(vector<Punto>& P,Grafo* G) {
	int n = P.size();
	vector<double> z(n);
	for (int i = 0; i < n; i++)
		z[i] = P[i].x*P[i].x + P[i].y * P[i].y;

	for (int i = 0; i < n-2; i++) {
		for (int j = i+1; j < n; j++) {
			for (int k = i+1; k < n; k++) {
				if(j==k) continue;
				double xn = (P[j].y-P[i].y)*(z[k]-z[i]) - (P[k].y-P[i].y)*(z[j]-z[i]);
				double yn = (P[k].x-P[i].x)*(z[j]-z[i]) - (P[j].x-P[i].x)*(z[k]-z[i]);
				double zn = (P[j].x-P[i].x)*(P[k].y-P[i].y) - (P[k].x-P[i].x)*(P[j].y-P[i].y);
				bool flag = zn < 0;
				for (int m = 0; flag && m < n; m++)
					flag = flag && ((P[m].x-P[i].x)*xn +
							 (P[m].y-P[i].y)*yn +
							 (z[m]-z[i])*zn <= 0);
				if (flag){
					if(!((*G).aristasNodo(P[i])>3 || (*G).aristasNodo(P[j])>3)){
						(*G).insertarArista(P[i],P[j],XorShift(10)==9);
					} else if(XorShift(10)==9){
						(*G).insertarArista(P[i],P[j],1);
					}
					if(!((*G).aristasNodo(P[i])>3 || (*G).aristasNodo(P[k])>3)){
						(*G).insertarArista(P[i],P[k],XorShift(10)==9);
					} else if(XorShift(10)==9){
						(*G).insertarArista(P[i],P[k],1);
					}
					if(!((*G).aristasNodo(P[j])>3 || (*G).aristasNodo(P[k])>3)){
						(*G).insertarArista(P[j],P[k],XorShift(10)==9);
					} else if(XorShift(10)==9){
						(*G).insertarArista(P[j],P[k],1);
					}
				}
			}
		}
	}
	for (auto it=(*G).nodos.begin();it!=(*G).nodos.end();it++){
		if((*G).aristasNodo((it->second)->punto) >5){
			cout << it->first  << " " << (*G).aristasNodo((it->second)->punto)<< endl;
		}
	}
}
