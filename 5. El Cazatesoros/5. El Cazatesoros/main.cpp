//
//  main.cpp
//  5. El Cazatesoros
//
//  Created by Diego Alejandro Rodriguez Pereira on 7/2/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int cazatesoros(int segs_botella, int n_cofres, vector<int> &v_profundidad, vector<int> &v_oro, vector<vector<int>> &matriz, int i, int j) {
    
    if (matriz[i][j]!=-1) {
        
        return matriz[i][j];
    }
    if (j == 0) {
        
        matriz[i][j]=0;
        return 0;
    }
    
    if(i==0) return -1;
    
    if(3*v_profundidad[i-1] > j) {
        
        matriz[i][j] = cazatesoros(segs_botella,n_cofres,v_profundidad,v_oro,matriz,i-1,j);
    }
    else{
        int sin,con;
        sin=cazatesoros(segs_botella,n_cofres,v_profundidad,v_oro,matriz,i-1,j);
        con=cazatesoros(segs_botella,n_cofres,v_profundidad,v_oro,matriz,i-1,j-(3*v_profundidad[i-1]));
        if(con==-1){
            matriz[i][j]=sin;
        }
        else{
            if(sin>con+v_oro[i-1]){
                matriz[i][j]=sin;
            }
            else{
                matriz[i][j]=con+v_oro[i-1];
            }
        }
    }
    
    
    return matriz[i][j];
}



bool resuelveCaso() {
    
    int segs_botella;
    int n_cofres;
    
    cin >> segs_botella;
    
    if (!cin) {
        return false;
    }
    
    cin >> n_cofres;
    
    
    vector<int> v_profundidad = vector<int>(n_cofres, 0);
    vector<int> v_oro = vector<int>(n_cofres, 0);
    
    for (int i = 0; i < n_cofres; i++) {
        
        cin >> v_profundidad[i];
        cin >> v_oro[i];
    }
    
    vector<vector<int>> matriz(n_cofres + 1, vector<int>(segs_botella + 1, -1));
    
    int maxi=-1,pos=-1;
    int actual;
    for(int i=0;i<segs_botella;i++){
        actual=cazatesoros(segs_botella, n_cofres, v_profundidad, v_oro, matriz, n_cofres, i);
        if(actual>maxi){
            maxi=actual;
            pos=i;
        }
    }
    
    vector<int> pila = vector<int>();
    
    if (maxi != 0) {
        int i = n_cofres;
        int j = pos;
        //while (matriz[i][j] != 0) {
        while (i > 0 && j > 0){
            
            int a = matriz[i][j];
            int pp = 3*v_profundidad[i-1];
            if (j - pp >= 0) {
                int b = matriz[i - 1][j - pp] + v_oro[i - 1];
                if (a == b) {
                    
                    pila.push_back(i);
                    j = j - 3*v_profundidad[i - 1];
                }
            }
            i--;
        }
    }
    
    cout << maxi <<endl;
    
    cout << pila.size() << endl;
    int i;
    while (!pila.empty()) {
        
        i = pila.at(pila.size() - 1)-1;
        pila.pop_back();
        cout << v_profundidad[i] << " " << v_oro[i] << endl;
    }
    
    cout << "---" << endl;
    
    return true;
}

int main() {
    
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
   while (resuelveCaso());
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
    return 0;
}

