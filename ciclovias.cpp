#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> matriz_adjacencia;

void printVector(vector<int> &vec)
{
    for (auto it = vec.begin(); it != vec.end() - 1; it++)
        cout << *it << "\t";
    cout << *(vec.end() - 1) << "\n";
}

void printMatriz(vector<vector<int>> &matriz)
{
    for (auto it = matriz.begin(); it != matriz.end(); it++)
        printVector(*it);
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n_testes;
    cin >> n_testes;

    for (int i = 0; i < n_testes; i++)
    {
        int n_vertices, n_arestas, n_questoes;

        cin >> n_vertices >> n_arestas >> n_questoes;

        matriz_adjacencia = vector(n_vertices, vector(n_vertices, 0));

        for (int i = 0; i < n_arestas; i++)
        {
            int v1, v2, distancia;

            cin >> v1 >> v2 >> distancia;

            matriz_adjacencia[v1 - 1][v2 - 1] = distancia;
        }

        printMatriz(matriz_adjacencia); // Correr algoritmo aqui
        }

    return 0;
}
