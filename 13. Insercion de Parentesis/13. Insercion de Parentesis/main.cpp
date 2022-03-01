
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

/**
 * 0 - 000 ninguna
 * 1 - 001 contiene a
 * 2 - 010 contiene b
 * 3 - 011 contiene a y b
 * 4 - 100 contiene c
 * 5 - 101 contiene c y a
 * 6 - 110 contiene c y b
 * 7 - 111 contiene c, b, a
 */

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct octal {
    bool resuelta;
    bool a;
    bool b;
    bool c;
};

octal suma_octales(octal uno, octal dos) {
    
    octal res = {true, false, false, false};
    res.a = uno.a || dos.a;
    res.b = uno.b || dos.b;
    res.c = uno.c || dos.c;
    
    return res;
}

octal multiplica_octales(octal uno, octal dos) {
    
    octal res = {true, false, false, false};
    
    if (uno.a) {
        if (dos.a) res.b = true;
        if (dos.b) res.b = true;
        if (dos.c) res.a = true;
    }
    if (uno.b) {
        if (dos.a) res.c = true;
        if (dos.b) res.b = true;
        if (dos.c) res.a = true;
    }
    if (uno.c) {
        if (dos.a) res.a = true;
        if (dos.b) res.c = true;
        if (dos.c) res.c = true;
    }
    
    return res;
}

octal calcula_octal(char s) {
    
    if (s == 'a') return {true, true, false, false};
    if (s == 'b') return {true, false, true, false};
    if (s == 'c') return {true, false, false, true};
    return {false, false, false, false};
}

octal contiene_a(vector<vector<octal>> &matriz, string cadena, int i, int j) {
    
    if (matriz[i][j].resuelta) return matriz[i][j];
    //casos base
    if (i == j) matriz[i][j] = calcula_octal(cadena[i]);
    if (i + 1 == j) matriz[i][j] = multiplica_octales(calcula_octal(cadena[i]), calcula_octal(cadena[j]));
    else {
        //casos recurisvos
        for (int k = i; k < j; k++) {
            
            octal uno = contiene_a(matriz, cadena, i, k);
            octal dos = contiene_a(matriz, cadena, k + 1, j);
            octal aux = multiplica_octales(uno, dos);
            matriz[i][j] = suma_octales(matriz[i][j], aux);
        }
    }
    
    return matriz[i][j];
}

/*octal contiene_a(const vector<vector<int>> &tabla, vector<vector<octal>> &matriz, string cadena, int tam_cadena) {
    
    for (int d = 1; d <= tam_cadena - 2; d++) {
        for (int i = 1; i <= tam_cadena - d - 1; i++) {
            
            int j = i + d;
            matriz[i][j] = {false, false, false, false};
            for (int k = i; k <= j - 1; k++) {
                matriz[i][j] = suma_octales(matriz[i][k], matriz[k + 1][j]);
            }
        }
    }
    
    return matriz[1][tam_cadena - 1];
}*/

bool resuelveCaso() {

    //leer entrada
    string cadena;
    cin >> cadena;
   
    if (!std::cin)  // fin de la entrada
      return false;
    
    int tam_cadena = (int) cadena.length();
    octal valor = {false, false, false, false};
    vector<vector<octal>> matriz(tam_cadena + 1, vector<octal>(tam_cadena + 1, valor));
    
    octal res = {false, false, false, false};
    res = contiene_a(matriz, cadena, 0, tam_cadena - 1);
    
    if (res.a) {
        cout << "SI" << endl;
    }
    else {
        cout << "NO" << endl;
    }
    //escribir resultado
   
    return true;
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
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
