#include <iostream>

#include <vector>

using namespace std;

/*
 * numero_blocos = n
 * tamanho_bloco = h
 * altura_max = H
 */
int numero_blocos, tamanho_bloco, altura_max;

int tabela_h, tabela_w;
vector<vector<int>> arcos;
vector<vector<int>> soma;

int mod = 1000000007;

int mod_abs(long a)
{
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b)
{
    return (mod_abs(a) + mod_abs(b)) % mod;
}

int mod_sub(int a, int b)
{
    return mod_add(a, -b);
}

int CalculaArcos(int linha, int coluna)
{
    int sub;

    if (linha - tamanho_bloco < 0)
        sub = arcos[linha - 1][coluna];

    else
        sub = mod_sub(arcos[linha - 1][coluna], arcos[linha - tamanho_bloco][coluna - 1]);

    return arcos[linha][coluna] = mod_add(sub, arcos[linha - 1][coluna - 1]);
}

int CalculaSoma(int linha, int coluna)
{
    int sub;

    if (linha == 0)
        sub = 0;

    else if (linha - tamanho_bloco + 1 < 0)
        sub = soma[linha][coluna + 1];

    else
        sub = mod_sub(soma[linha][coluna + 1], soma[linha - tamanho_bloco + 1][coluna]);

    return mod_add(soma[linha][coluna], sub);
}

int ContaArcos(int &total_linha, int linha, int coluna)
{
    int arcos_possiveis = CalculaArcos(linha, coluna);
    int arcos_complementares = CalculaSoma(linha - 1, numero_blocos - coluna - 2);

    if (arcos_possiveis == 0)
        return 0;

    total_linha = mod_add(total_linha, arcos_possiveis);

    return mod_abs(arcos_possiveis * (long)arcos_complementares);
}

int ArchBuilder()
{
    arcos[0][0] = 1;
    soma[0] = vector<int>(tabela_h + 1, 1);

    int total = 0;
    int j_inicial = 1;

    for (int i = 1; i < tabela_w; i++)
    {
        int total_linha = 0;
        bool is_max = false;

        for (int j = j_inicial; j < tabela_h; j++)
        {
            if (!is_max)
            {
                int arcs = ContaArcos(total_linha, i, j);

                if (arcs == 0)
                {
                    if (j == j_inicial)
                        return total;

                    is_max = true;
                }

                else
                    total = mod_add(total, arcs);
            }

            soma[i][j] = total_linha;
        }

        if (i / (tamanho_bloco - 1) >= j_inicial)
        {
            j_inicial++;

            if (j_inicial >= numero_blocos)
                break;
        }

        soma[i][tabela_h] = total_linha;
    }

    return total;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int numero_casos, resultado;
    cin >> numero_casos;

    for (int i = 0; i < numero_casos; i++)
    {
        cin >> numero_blocos >> tamanho_bloco >> altura_max;

        tabela_w = altura_max - tamanho_bloco + 1;
        tabela_h = numero_blocos;

        arcos = vector<vector<int>>(tabela_w, vector<int>(tabela_h, 0));
        soma = vector<vector<int>>(tabela_w, vector<int>(tabela_h + 1, 0));

        resultado = ArchBuilder();

        cout << resultado << endl;
    }

    return 0;
}
