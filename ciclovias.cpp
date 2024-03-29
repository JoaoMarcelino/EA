#include <iostream>

#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

int n_vertices;
int maior_circuito, total_estrada;
vector<vector<int>> matriz_adjacencia;
vector<vector<int>> circuitos;

// Tarjan
int t;
stack<int> S;
vector<bool> on_stack;
vector<int> dfs;
vector<int> low;

// Kruskal
vector<int> set;
vector<int> ranking;

class Aresta
{
public:
    int tamanho;
    int origem;
    int destino;

    Aresta(int t, int o, int d)
    {
        tamanho = t;
        origem = o;
        destino = d;
    }
};

void Tarjan(int v)
{
    dfs[v - 1] = t;
    low[v - 1] = t;
    t++;

    S.push(v);
    on_stack[v - 1] = true;

    for (int w = 1; w <= n_vertices; w++)
    {
        if (matriz_adjacencia[v - 1][w - 1] != 0)
        {
            if (dfs[w - 1] == -1)
            {
                Tarjan(w);
                low[v - 1] = min(low[v - 1], low[w - 1]);
            }

            else if (on_stack[w - 1])
                low[v - 1] = min(low[v - 1], dfs[w - 1]);
        }
    }

    if (low[v - 1] == dfs[v - 1])
    {
        vector<int> c = vector(0, 0);
        int w;

        do
        {
            w = S.top();
            S.pop();

            on_stack[w - 1] = false;
            c.push_back(w);

        } while (w != v);

        if (!c.empty() && c.size() > 1)
            circuitos.push_back(c);
    }
}

// Funções auxiliares do Kruskal
int find(int a)
{
    if (set[a - 1] != a)
        set[a - 1] = find(set[a - 1]);

    return set[a - 1];
}

void link(int a, int b)
{
    if (ranking[a - 1] > ranking[b - 1])
        set[b - 1] = a;
    else
        set[a - 1] = b;

    if (ranking[a - 1] == ranking[b - 1])
        ranking[b - 1]++;
}

void createUnion(int a, int b)
{
    link(find(a), find(b));
}

int comparaArestas(Aresta &a, Aresta &b)
{
    return a.tamanho < b.tamanho;
}

vector<Aresta> getArestas(vector<int> circuito)
{
    vector<Aresta> arestas;

    for (auto &origem : circuito)
    {
        for (auto &destino : circuito)
        {
            if (matriz_adjacencia[origem - 1][destino - 1] != 0)
            {
                Aresta a(matriz_adjacencia[origem - 1][destino - 1], origem, destino);
                arestas.push_back(a);
            }
        }
    }

    sort(arestas.begin(), arestas.end(), comparaArestas);

    return arestas;
}

int Kruskal(vector<int> circuito)
{
    int total = 0;

    for (auto &vertice : circuito)
    {
        set[vertice - 1] = vertice;
        ranking[vertice - 1] = 0;
    }

    vector<Aresta> arestas = getArestas(circuito);

    for (auto &aresta : arestas)
    {
        if (find(aresta.origem) != find(aresta.destino))
        {
            total += aresta.tamanho;
            createUnion(aresta.origem, aresta.destino);
        }
    }

    return total;
}

int maiorCircuito()
{
    int maior = 0;

    for (auto &circuito : circuitos)
    {
        if ((int)circuito.size() > maior)
            maior = circuito.size();
    }

    return maior;
}

void calculaCiclovias()
{
    for (auto &circuito : circuitos)
    {
        int tamanho = Kruskal(circuito);
        total_estrada += tamanho;

        if (tamanho > maior_circuito)
            maior_circuito = tamanho;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n_testes;
    cin >> n_testes;

    for (int i = 0; i < n_testes; i++)
    {
        int n_arestas, n_questoes;

        cin >> n_vertices >> n_arestas >> n_questoes;

        matriz_adjacencia = vector(n_vertices, vector(n_vertices, 0));

        for (int i = 0; i < n_arestas; i++)
        {
            int v1, v2, distancia;

            cin >> v1 >> v2 >> distancia;

            matriz_adjacencia[v1 - 1][v2 - 1] = distancia;
        }

        maior_circuito = 0;
        total_estrada = 0;
        circuitos = vector<vector<int>>(0, vector<int>(0, 0));

        t = 0;
        S = stack<int>();
        dfs = vector(n_vertices, -1);
        low = vector(n_vertices, -1);
        on_stack = vector(n_vertices, false);

        for (int i = 1; i <= n_vertices; i++)
        {
            if (dfs[i - 1] == -1)
                Tarjan(i);
        }

        if (n_questoes >= 1)
            cout << circuitos.size();

        if (n_questoes >= 2)
            cout << " " << maiorCircuito();

        if (n_questoes >= 3)
        {
            set = vector(n_vertices, -1);
            ranking = vector(n_vertices, -1);

            calculaCiclovias();
            cout << " " << maior_circuito;
        }

        if (n_questoes >= 4)
            cout << " " << total_estrada;

        cout << endl;
    }

    return 0;
}