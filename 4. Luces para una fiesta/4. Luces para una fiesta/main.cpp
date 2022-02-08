
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int MAX_INT = 99999;

void resuelve(int num_bombillas, int max_potencia, int min_potencia, vector<int> v_potencia, vector<int> v_coste, vector<int> matriz) {
    
    matriz[0] = 0;
    
    for (int i = 0; i < num_bombillas; i++) {
        
        for (int j = v_potencia[i]; j <= max_potencia; j++) {
            
            if (matriz[j - v_potencia[i]] != MAX_INT && matriz[j] > matriz[j - v_potencia[i]] + v_coste[i]) {
                
                matriz[j] = matriz[j - v_potencia[i]] + v_coste[i];
            }
        }
    }
    
    int min = matriz[min_potencia];
    int pos = min_potencia;
    
    for (int i = min_potencia; i <= max_potencia; i++) {
        
        if (matriz[i] < min) {
            
            min = matriz[i];
            pos = i;
        }
    }
    
    if (matriz[pos] != MAX_INT) {
        
        cout << min << " " << pos << endl;
    }
    else {
        
        cout << "IMPOSIBLE" << endl;
    }
    
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
   
   // leer los datos de la entrada
    
    int num_bombillas;
    int max_potencia;
    int min_potencia;
    
    cin >> num_bombillas;
    cin >> max_potencia;
    cin >> min_potencia;
   
   if (!cin)  // fin de la entrada
      return false;
    
    
    vector<int> v_potencia = vector<int>(num_bombillas, 0);
    vector<int> v_coste = vector<int>(num_bombillas, 0);
    
    for (int i = 0; i < num_bombillas; i++) {
        
        cin >> v_potencia[i];
    }
    
    for (int i = 0; i < num_bombillas; i++) {
        
        cin >> v_coste[i];
    }
    
    
    vector<int> matriz(max_potencia + 1, MAX_INT);
    
    resuelve(num_bombillas, max_potencia, min_potencia, v_potencia, v_coste, matriz);
   
   // escribir sol
   
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
