#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>

using namespace std;


    /* LINHAS A MAIS PARA MELHOR VIZUALIZAÇÃO
    4

    3 5
    2 0 2
    4 0 8
    0 0 0

    3 10
    4 2 4
    4 2 4
    4 4 4

    3 4
    4 2 4
    4 2 4
    4 4 4

    4 10
    8 4 0 0
    4 0 0 0
    8 4 0 0
    0 0 4 0

    */

    /* 
    a pedido de josphze
    https://google.github.io/styleguide/cppguide.html#Variable_Names 
    */

vector<vector<string>> ReadMatrix(int size_matrix){
    
    //TODO: read matrix
}


void MainMatrices(){
    string size_matrix, max_moves;
    vector<vector<string>> matrix;

    //TODO: read size_matrix, max_moves

    matrix = ReadMatrix(stoi(size_matrix));

    //TODO: make money moves
}


int main()
{      
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string num_matrices;

    //TODO: read num_matrices


    for(int i = 0; i< stoi(num_matrices); i++){
        MainMatrices();
    }

}