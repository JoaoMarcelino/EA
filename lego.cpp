#include <iostream>
#include <sstream>

#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>

#include <math.h>

using namespace std;

/*
 * number_blocks = n
 * size_block = h
 * max_height = H
 */
int number_blocks, size_block, max_height;

int tabela_h, tabela_w;
vector<vector<int>> tabelha;
vector<vector<int>> soma;

//1 000 000 007
int mod =  1000000007; 

// FUNCÕES DISPONIBILIZADAS PELO PROFESSOR

int mod_abs(int a, int mod) {
 	return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
 	return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
	return mod_add(a, -b, mod);
}

void printTabelha(vector<vector<int>> tabelha ,int width, int height)
{
    for (int i = 0; i < width; i++)
	{
        for (int j = 0; j < height; j++)
            cout << tabelha[i][j] << " ";
			
        cout << endl;
    }
}

int TabelhaAdd(int fila, int coluna)
{
    int soma = 0;
    
	for (int i = 0; i < size_block - 1; i++) 
	{
		if (fila - i == 0)
			break;

		soma += tabelha[fila - 1 - i][coluna - 1];
	}

    return tabelha[fila][coluna] = soma;
}


int addArcs(int &row_count, int linha, int coluna){
    int count = 0;
    int aux = TabelhaAdd(linha, coluna);
    row_count= row_count + aux;

	soma[linha][coluna] = row_count;
    

    if(aux == 0){
        return 0;
    }

    for (int i = 1; i < size_block ; i++){

        if (linha - i < 0)
            break;

        /*
        cout << "tabela "<< linha +  size_block << " : "<< coluna+1 <<" (" << aux << ")";
        cout <<"multiplicado por soma " << linha - i   +  size_block<< " : "<< number_blocks - coluna - 1 <<" (" << soma[linha - i][number_blocks - coluna -2] << ")\n";
        */

        //count += aux * soma[linha - i][number_blocks - coluna -2];
        count = mod_add(count, aux * soma[linha - i][number_blocks - coluna -2], mod);
    }


    return count;

}


int ArchBuilder(){

    tabelha[0][0] = 1;
    soma[0] = vector(tabela_w, 1); 
    int count = 0;
    for (int i = 1; i < tabela_w; i++){
        int row_count = 0;
        for (int j = 1; j < tabela_h; j++){
            
            //count += addArcs(row_count, i , j);
            count = mod_add(count, addArcs(row_count, i , j), mod);
            //cout << "Contas de " << i <<" + " << j<<": " << count << endl;
            
        }
    }
    
    cout << "Tabelha" << endl;
    printTabelha(tabelha,max_height - size_block + 1, number_blocks);
    cout<< "Soma" << endl;
    printTabelha(soma, max_height - size_block + 1, number_blocks);
    
    return count;
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int number_cases, result;
    cin >> number_cases;

    for(int i = 0; i < number_cases; i++){

        cin >> number_blocks >> size_block >> max_height;

        tabela_w = max_height - size_block + 1;
        tabela_h = number_blocks;

        tabelha = vector<vector<int>>(tabela_w, vector<int>(tabela_h, 0));
        soma = vector<vector<int>>(tabela_w, vector<int>(tabela_h, 0));

        result = ArchBuilder();

        cout << result << endl;
    }

    return 0;
}