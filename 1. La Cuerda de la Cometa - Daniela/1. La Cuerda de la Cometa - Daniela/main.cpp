//
//  main.cpp
//  1. La Cuerda de la Cometa - Daniela
//
//  Created by Diego Alejandro Rodriguez Pereira on 7/2/22.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "Matriz.h"

using namespace std;


// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta



long long int matematico(int l, int n, vector<int> longi) {
    vector<long long int> mates = vector<long long int>(l+1, 0);
    
    mates[0] = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = l; j >= longi[i]; j--) {
            mates[j] += mates[j - longi[i]];
        }
        //mates[longi[i]] ++;
    }
    return mates[l];
   
}

long long int ingeniero(int l, int n, vector<int> longi){
    vector<long long int> inge = vector<long long int>(l + 1, 9223372036854775807);
    inge[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = l; j >= longi[i]; j--) {
            if (inge[j - longi[i]] != 9223372036854775807 && inge[j] > (inge[j - longi[i]] + 1)) {
                inge[j] = inge[j - longi[i]] + 1;
            }
        }
    }
    return inge[l];

}

long long int economista(int l, int n, vector<int> longi, vector<int> preci) {
    vector<long long int> inge = vector<long long int>(l + 1, 9223372036854775807);
    inge[0] = 0;
    for (int i = 0; i < n; i++) {
        for (int j = l; j >= longi[i]; j--) {
            if(inge[j - longi[i]]!= 9223372036854775807 && inge[j] > (inge[j - longi[i]] + preci[i])) {
                inge[j] = inge[j - longi[i]] + preci[i];
            }
        }
    }
    return inge[l];

}


bool leerdatos() {
    int n, l;
    cin >> n;

    if (!std::cin) {
        return false;
    }
    cin >> l;

    vector <int> longi(n);
    vector<int> precio(n);
    for (int i = 0; i < n; i++) {
       
        cin >> longi[i];//longitud
        cin >> precio[i];//precio
       
    }

    long long int mates = matematico(l, n, longi);
   
    if (mates == 0) {
        cout << "NO" << endl;
    }
    else {
        long long int inge = ingeniero(l, n, longi);
        long long int eco = economista(l, n, longi, precio);
        cout << "SI " << mates << " " << inge << " " << eco << endl;
    }

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (leerdatos());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
