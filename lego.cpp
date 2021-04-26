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
long long int  mod =  1000000007; 

// FUNCÕES DISPONIBILIZADAS PELO PROFESSOR

long long int  mod_abs(long long int  a) {
 	return ((a % mod) + mod) % mod;
}

long long int  mod_add(long long int  a, long long int  b) {
 	return (mod_abs(a) + mod_abs(b)) % mod;
}

long long int  mod_sub(long long int  a, long long int  b) {
	return mod_add(a, -b);
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


long long int TabelhaAdd(int fila,int coluna){
    long long int sum = 0;
    long long int sub = 0;
    
    if (fila - size_block < 0 ){
        sub = tabelha[fila -1][coluna];
        //cout << "sub1- "<< sub<< endl;
    }
    else{
        sub =mod_sub(tabelha[fila - 1][coluna], tabelha[fila - size_block][coluna - 1]);
    }
    
    sum =  mod_add(sub, tabelha[fila - 1][coluna - 1]);

    //cout << "Contas de " << fila <<" + " << coluna <<": " << sub  << " - " << soma << endl;

    return tabelha[fila][coluna] = sum;
}



long long int SomaAdd( int fila, int coluna){
    long long int sum = 0;
    long long int sub = 0;

    if(fila == 0){
        sub = 0;
    }
    else if (fila - size_block + 1 < 0 ){
        sub = soma[fila][coluna + 1];
        //cout << "SUB de [" << fila <<", " << coluna <<"]: " << soma[fila][coluna + 1]  << " - NULL "<<" + " << soma[fila][coluna] << endl;

     }
     else {
        //cout << "SUB de [" << fila <<", " << coluna <<"]: " << soma[fila][coluna + 1]  << " - "<< soma[fila - size_block + 1][coluna]<<" + " << soma[fila][coluna] << endl;
        sub = mod_sub(soma[fila][coluna + 1], soma[fila - size_block + 1][coluna]);
     }
    
    sum =mod_add(soma[fila][coluna], sub);

    return sum;
}

long long int  addArcs(long long int  &row_count, int  linha, int  coluna){
    long long int  count = 0;
    long long int  aux = TabelhaAdd(linha, coluna);

    long long int temp = 0;

    if(aux == 0)
        return 0;
    
    row_count = mod_add(row_count, aux);

    temp = SomaAdd(linha - 1, number_blocks - coluna - 2);
    count = mod_add(count, aux *temp);

    return count;
}


long long int  ArchBuilder(){

    tabelha[0][0] = 1;
    soma[0] = vector<unsigned int>(tabela_h + 1, 1);
    long long int  count = 0;
    int initial_j = 1;

    for (int  i = 1; i < tabela_w; i++){

        long long int  row_count = 0;
        bool isWorth = true;

        for (int  j = initial_j; j < tabela_h; j++){
            
            if (isWorth){

                long long int arcs = addArcs(row_count, i , j);

                if(arcs != 0){
                    count = mod_add(count, arcs);
                }

                else
                {
                    if (j == initial_j) return count; //nao da para printar com isto
                    isWorth = false;
                }

            }
            soma[i][j]= row_count;

        }
        if (i / (size_block - 1) >= initial_j){
            initial_j++;

            if (initial_j >= number_blocks) break;
        }

        soma[i][tabela_h]= row_count;

    }

    /*
    cout << "Tabelha" << endl;
    printTabelha(tabelha, tabela_w, tabela_h);
    cout<< "Soma" << endl;
    printTabelha(soma, tabela_w, tabela_h + 1);
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
        soma = vector<vector<unsigned int>>(tabela_w, vector<unsigned int>(tabela_h + 1, 0));

        result = ArchBuilder();

        cout << result << endl;
        
       
    }

    return 0;
}
