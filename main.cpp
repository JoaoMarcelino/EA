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


void PrintRow(vector<string> row){

    for(auto iterator = row.begin(); iterator != row.end() ; ++iterator){
        cout << *iterator << " ";
    }
    cout << "\n";

    
}


void PrintMatrix(vector<vector<string>> matrix){
    
    cout << "Matrix\n";
    for(auto iterator = matrix.begin(); iterator != matrix.end() ; ++iterator){
        PrintRow(*iterator);
    }
}


vector<vector<string>> ReadMatrix(int size){
    vector<string> aux(size);
    vector<vector<string>> matrix(size, aux);
    string line;
    auto aux_matrix = matrix.begin();

    for(int i =0; i< size; i++){

        getline(cin, line);
        istringstream iss(line);
        vector<string> row(istream_iterator<string>{iss}, istream_iterator<string>());
        
        (*aux_matrix).assign(row.begin(), row.end());
        ++aux_matrix;
    }

    return matrix;
}

vector<vector<string>> MoveLeft(vector<vector<string>> matrix){

    for(auto matrix_iterator = matrix.begin(); matrix_iterator != matrix.end(); ++matrix_iterator){
        int count_erased = 0;
        for (auto row_iterator = (*matrix_iterator).begin(); row_iterator !=(*matrix_iterator).end(); ++row_iterator){
            if (*row_iterator == "0"){
               (*matrix_iterator).erase(row_iterator);
                count_erased++;
                row_iterator--;
            }
        }
        
        for (int i = 0; i < count_erased; i++){
            (*matrix_iterator).push_back("0");
        }

    }
    return matrix;
    PrintMatrix(matrix);
}

vector<vector<string>> MoveRight(vector<vector<string>> matrix){

    for(auto matrix_iterator = matrix.begin(); matrix_iterator != matrix.end(); ++matrix_iterator){
        int count_erased = 0;
        for (auto row_iterator = (*matrix_iterator).begin(); row_iterator !=(*matrix_iterator).end(); ++row_iterator){
            if (*row_iterator == "0"){
               (*matrix_iterator).erase(row_iterator);
                count_erased++;
                row_iterator--;
            }
        }
        
        for (int i = 0; i < count_erased; i++){
            (*matrix_iterator).insert((*matrix_iterator).begin(),"0");
        }

    }
    return matrix;
    PrintMatrix(matrix);
}




void MainMatrices(){


    string line;
    int size_matrix, max_moves;
    vector<vector<string>> matrix;

    getline(cin, line);
    istringstream iss(line);
    vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());

    auto iterator = results.begin();
    size_matrix = stoi(*iterator);
    max_moves = stoi(*(++iterator));

    matrix = ReadMatrix(size_matrix);

    //matrix = MoveLeft(matrix);
    matrix = MoveRight(matrix);
    PrintMatrix(matrix);

    //TODO: make money moves
    max_moves ++;
}


int main()
{      
    
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    string line;
    int num_matrices = 0;

    getline(cin, line);

    istringstream iss(line);
    vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());


    num_matrices =stoi(*(results.begin()));


    for(int i = 0; i < num_matrices; i++){
        MainMatrices();
    }

    return 0;

}