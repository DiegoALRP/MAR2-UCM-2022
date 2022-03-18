
// Nombre y Apellidos
// Diego Alejandro
// Rodriguez Pereira

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int MIN_DISTANCIA = 2;

struct Nodo {
	
	vector<int> sol; //sol[i] contiene la persona i que se ha sentado en la silla j
	//vector<bool> marcas; //marcas[i] dice si la persona i se ha sentado ya o no
	int k_persona;
	int parejas;
	int parejas_estimado;
	bool operator<(Nodo const& otro) const {
		return otro.parejas_estimado > parejas_estimado;
	}
};

bool es_valido(const int &n, const int &m, const vector<vector<double>> &distancias, const vector<vector<int>> &allegados, Nodo &X) {
	
	bool is_valid = true;
	int persona_actual = X.k_persona;
	for (int i = 0; i < persona_actual; i++) {
		
		int silla_actual = X.sol[persona_actual];
		int silla_otro = X.sol[i];
		
		if (silla_actual == silla_otro) return false;
		
		if (allegados[persona_actual][i] == 0) {
			if (distancias[silla_actual][silla_otro] < MIN_DISTANCIA) {
				return false;
			}
		}
		
		if (allegados[persona_actual][i] == 1) {
			if (distancias[silla_actual][silla_otro] < MIN_DISTANCIA) {
				X.parejas++;
			}
		}
	}
	
	return is_valid;
}

void restaurante_rp(const int &n, const int &m, const vector<vector<double>> &distancias, const vector<vector<int>> &allegados, vector<int> &mejor_sol, int &max_parejas) {
	
	Nodo Y;
	Y.sol = vector<int>(n, -1);
	Y.k_persona = -1;
	Y.parejas = 0;
	Y.parejas_estimado = 0;
	priority_queue<Nodo> cola;
	cola.push(Y);
	max_parejas = -1;
	
	while (!cola.empty() /*&& cola.top().parejas_estimado > max_parejas*/) {
		
		Y = cola.top();
		cola.pop();
		Nodo X(Y);
		X.k_persona++;
		
		for (int j = 0; j < n; j++) {
			
			X.sol[X.k_persona] = j;
			X.parejas = Y.parejas;
			if (es_valido(n, m, distancias, allegados, X)) {
				
				//X.parejas_estimado = Y.parejas_estimado;
				
				if (X.k_persona == m - 1) {
					//cout << "prueba: " << X.parejas << " ";
					if (X.parejas > max_parejas) {
						mejor_sol = X.sol;
						max_parejas = X.parejas;
					}
				}
				else {
					cola.push(X);
				}
			}
		}
	}
}

void resuelveCaso() {

    //leer entrada
    int n_plazas, m_comensales;
    cin >> n_plazas >> m_comensales;
    
    vector<vector<double>> distancias(n_plazas, vector<double>(n_plazas));
    for (int i = 0; i < n_plazas; i++) {
        for (int j = 0; j < n_plazas; j++) {
            cin >> distancias[i][j];
        }
    }
    
    vector<vector<int>> allegados(m_comensales, vector<int>(m_comensales));
    for (int i = 0; i < m_comensales; i++) {
        for (int j = 0; j < m_comensales; j++) {
            cin >> allegados[i][j];
        }
    }

	vector<int> mejor_sol;
	int max_parejas = -1;
	restaurante_rp(n_plazas, m_comensales, distancias, allegados, mejor_sol, max_parejas);
	
	if (max_parejas <= 0) {
		cout << "CANCELA" << endl;
	}
	else {
		cout << "PAREJAS " << max_parejas << endl;
	}
    //escribir resultado
}

int main() {
   // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
   std::ifstream in("casos.txt");
   auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif
   
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();
   
   // para dejar todo como estaba al principio
#ifndef DOMJUDGE
   std::cin.rdbuf(cinbuf);
   system("PAUSE");
#endif
   return 0;
}
