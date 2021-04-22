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
vector<vector<unsigned int>> tabelha;
vector<vector<unsigned int>> soma;

//1 000 000 007
unsigned long int  mod =  1000000007; 

// FUNCÕES DISPONIBILIZADAS PELO PROFESSOR

unsigned long int  mod_abs(unsigned long int  a) {
 	return ((a % mod) + mod) % mod;
}

unsigned long int  mod_add(unsigned long int  a, unsigned long int  b) {
 	return (mod_abs(a) + mod_abs(b)) % mod;
}

unsigned long int  mod_sub(unsigned long int  a, unsigned long int  b) {
	return mod_add(a, -b);
}

unsigned long int  mod_mult(unsigned long int  a, unsigned long int  b) {
 	return mod_abs((mod_abs(a) * mod_abs(b)));
}

void printTabelha(vector<vector<unsigned int>> tabelha , int  width,  int  height)
{
    for ( int  i = 0; i < width; i++)
	{
        for ( int  j = 0; j < height; j++)
            cout << tabelha[i][j] << " ";
        cout << endl;
    }
}

unsigned long int  TabelhaAdd( int  fila, int  coluna)
{
    unsigned long int  soma = 0;

	for ( int  i = 0; i < size_block - 1; i++) 
	{
		if (fila - i == 0)
			break;

		//soma += tabelha[fila - 1 - i][coluna - 1];
        soma =  mod_add(soma, tabelha[fila - 1 - i][coluna - 1]);
	}

    return tabelha[fila][coluna] = soma;
}


unsigned long int  addArcs(unsigned long int  &row_count, int  linha, int  coluna){
    unsigned long int  count = 0;
    unsigned long int  aux = TabelhaAdd(linha, coluna);

    if(aux == 0){
        soma[linha][coluna] = row_count;
        return 0;
    }

    row_count = mod_add(row_count, aux); //claramente faz coisas
    //row_count= row_count + aux;

	soma[linha][coluna] = row_count;
    
    for (int  i = 1; i < size_block ; i++){

        if (linha - i < 0)
            break;

        if (number_blocks - coluna -2 >= 0){
            //cout << "tabela "<< linha +  size_block << " : "<< coluna+1 <<" (" << aux << ")";
            //cout <<"multiplicado por soma " << linha - i   +  size_block<< " : "<< number_blocks - coluna - 1 <<" (" << soma[linha - i][number_blocks - coluna -2] << ")\n";

            //count += aux * soma[linha - i][number_blocks - coluna -2];
            count = mod_add(count, aux * soma[linha - i][number_blocks - coluna -2]);
        }
    }

    return count;
}


unsigned long int  ArchBuilder(){

    tabelha[0][0] = 1;
    soma[0] = vector<unsigned int>(tabela_w, 1); 
    unsigned long int  count = 0;
    int initial_j = 1;

    for (int  i = 1; i < tabela_w; i++){

        unsigned long int  row_count = 0;
        for (int  j = initial_j; j < tabela_h; j++){
            
            unsigned long int arcs = addArcs(row_count, i , j);


            count = mod_add(count, arcs);
            //count += addArcs(row_count, i , j);
            //cout << "Contas de " << i <<" + " << j<<": " << count << endl;
        }

        // TODO Find first
        //cout << "value: " << i + 3 << " i " << i << " initial_j: "<< initial_j << " total: "<< i/ (size_block - 1)<< endl;
        if (i/ (size_block - 1) >= initial_j){
            initial_j++;

            if (initial_j>= number_blocks) break;
        }
    }

    /*
    cout << "Tabelha" << endl;
    printTabelha(tabelha, tabela_w, tabela_h);
    cout<< "Soma" << endl;
    printTabelha(soma, tabela_w, tabela_h);
    */
   
    return count;
}


int main(){

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int  number_cases, result;
    cin >> number_cases;

    for(int  i = 0; i < number_cases; i++){

        cin >> number_blocks >> size_block >> max_height;

        tabela_w = max_height - size_block + 1;
        tabela_h = number_blocks;

        tabelha = vector<vector<unsigned int>>(tabela_w, vector<unsigned int>(tabela_h, 0));
        soma = vector<vector<unsigned int>>(tabela_w, vector<unsigned int>(tabela_h, 0));

        result = ArchBuilder();

        cout << result << endl;
    }

    return 0;
}

// Checkar se resultados != 0 para n fazer add's
// Parar se for uma linha de 0's