#include <iostream>
#include <sstream>

#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include <math.h>

using namespace std;

int size_matrix;
int max_value = 0;

bool is_completed = false;
bool has_changed = false;

void PrintRow(vector<int> row)
{
    for (auto iterator = row.begin(); iterator != row.end(); ++iterator)
    {
        cout << *iterator << " ";
    }
    cout << "\n";
}

void PrintMatrix(vector<vector<int>> matrix)
{
    cout << "Matrix\n";

    for (auto iterator = matrix.begin(); iterator != matrix.end(); ++iterator)
        PrintRow(*iterator);

    cout << "\n";
}

vector<vector<int>> ReadMatrix()
{
    vector<int> aux(size_matrix);
    vector<vector<int>> matrix(size_matrix, aux);

    string line;
    auto aux_matrix = matrix.begin();

    for (int i = 0; i < size_matrix; i++)
    {
        getline(cin, line);
        istringstream iss(line);
        vector<int> row(istream_iterator<int>{iss}, istream_iterator<int>());

        auto aux_row = (*aux_matrix).begin();

        for (auto iterator = row.begin(); iterator != row.end(); ++iterator)
        {
            max_value += *iterator;
            *aux_row++ = *iterator;
        }

        (*aux_matrix).assign(row.begin(), row.end());
        ++aux_matrix;
    }

    return matrix;
}

vector<vector<int>> RotateMatrix(vector<vector<int>> matrix)
{
    vector<int> aux(size_matrix);
    vector<vector<int>> new_matrix(size_matrix, aux);

    int row = 0;
    int column = 0;
    auto new__matrix_iterator = new_matrix.begin();

    for (auto matrix_iterator = matrix.begin(); matrix_iterator != matrix.end(); ++matrix_iterator)
    {
        column = 0;

        for (auto row_iterator = (*matrix_iterator).begin(); row_iterator != (*matrix_iterator).end(); ++row_iterator)
        {
            //(*new_matrix).assign(row_iterator.begin(), row_iterator.end());
            auto new_row_iterator = (*(new__matrix_iterator + column)).begin();

            *(new_row_iterator + row) = *row_iterator;
            column++;
        }

        row++;
    }

    return new_matrix;
}

vector<vector<int>> MoveLeft(vector<vector<int>> matrix)
{
    int count_erased;
    int last_number = -1;

    for (auto matrix_iterator = matrix.begin(); matrix_iterator != matrix.end(); ++matrix_iterator)
    {
        count_erased = 0;
        last_number = -1;

        for (auto row_iterator = (*matrix_iterator).begin(); row_iterator != (*matrix_iterator).end(); ++row_iterator)
        {
            if (*row_iterator == 0)
            {
                (*matrix_iterator).erase(row_iterator);
                count_erased++;
                row_iterator--;
            }

            else if (*row_iterator == last_number)
            {
                (*matrix_iterator).erase(row_iterator);
                count_erased++;
                row_iterator--;
                last_number = -1;
                *row_iterator = *row_iterator * 2;

                has_changed = true;
                is_completed = *row_iterator == max_value;
            }

            else
                last_number = *row_iterator;
        }

        for (int i = 0; i < count_erased; i++)
            (*matrix_iterator).push_back(0);
    }

    return matrix;
}

vector<vector<int>> MoveRight(vector<vector<int>> matrix)
{
    int count_erased;
    int last_number = -1;

    for (auto matrix_iterator = matrix.begin(); matrix_iterator != matrix.end(); ++matrix_iterator)
    {
        count_erased = 0;
        last_number = -1;

        for (auto row_iterator = (*matrix_iterator).end() - 1; row_iterator != (*matrix_iterator).begin() - 1; --row_iterator)
        {

            if (*row_iterator == 0)
            {
                (*matrix_iterator).erase(row_iterator);
                count_erased++;
            }

            else if (*row_iterator == last_number)
            {
                (*matrix_iterator).erase(row_iterator);
                count_erased++;
                last_number = -1;
                *row_iterator = *row_iterator * 2;

                has_changed = true;
                is_completed = *row_iterator == max_value;
            }

            else
                last_number = *row_iterator;
        }

        for (int i = 0; i < count_erased; i++)
            (*matrix_iterator).insert((*matrix_iterator).begin(), 0);
    }

    return matrix;
}

vector<vector<int>> MoveUp(vector<vector<int>> matrix)
{
    matrix = RotateMatrix(matrix);
    matrix = MoveLeft(matrix);
    matrix = RotateMatrix(matrix);

    return matrix;
}

vector<vector<int>> MoveDown(vector<vector<int>> matrix)
{
    matrix = RotateMatrix(matrix);
    matrix = MoveRight(matrix);
    matrix = RotateMatrix(matrix);

    return matrix;
}

int Recursion(vector<vector<int>> matrix, int moves_left, int moves, string last_move)
{
    vector<int> child(4, -1);
    auto iterator = child.begin();

    if (is_completed) // Só houver 1 número restante
    {
        is_completed = false;
        return moves_left;
    }

    if (moves_left == 0)
        return -1;

    if (last_move != "Left" || has_changed)
    {
        has_changed = false;
        *iterator++ = Recursion(MoveLeft(matrix), moves_left - 1, moves + 1, "Left");
    }

    if (last_move != "Right" || has_changed)
    {
        has_changed = false;
        *iterator++ = Recursion(MoveRight(matrix), moves_left - 1, moves + 1, "Right");
    }

    if (last_move != "Up" || has_changed)
    {
        has_changed = false;
        *iterator++ = Recursion(MoveUp(matrix), moves_left - 1, moves + 1, "Up");
    }

    if (last_move != "Down" || has_changed)
    {
        has_changed = false;
        last_move = "Down";
        *iterator = Recursion(MoveDown(matrix), moves_left - 1, moves + 1, "Down");
    }

    return *max_element(child.begin(), child.end());
}

void MainMatrices()
{

    string line;
    int max_moves;
    vector<vector<int>> matrix;

    getline(cin, line);
    istringstream iss(line);
    vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());

    auto iterator = results.begin();
    size_matrix = stoi(*iterator);
    max_moves = stoi(*(++iterator));

    matrix = ReadMatrix();

    double intpart;
    int printable_value;

    //TODO: make money moves
    if (modf(log2(max_value), &intpart) == 0.0)
    {
        printable_value = Recursion(matrix, max_moves, 0, "");

        if (printable_value == -1)
            cout << "no solution" << endl;

        else
            cout << max_moves - printable_value << endl;
    }

    else
        cout << "no solution" << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    string line;
    int num_matrices = 0;

    getline(cin, line);

    istringstream iss(line);
    vector<string> results(istream_iterator<string>{iss}, istream_iterator<string>());

    num_matrices = stoi(*(results.begin()));

    for (int i = 0; i < num_matrices; i++)
    {
        MainMatrices();
        max_value = 0;
    }

    return 0;
}

/* LINHAS A MAIS PARA MELHOR VIZUALIZAÇÃO


    2
    3 5
    2 2 4
    2 2 0
    2 2 0


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
