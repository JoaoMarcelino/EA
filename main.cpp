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

int row_size;
int max_value = 0;
int max_atual = 0;
int best_moves_left;

float moves_needed;

bool is_completed = false;
bool has_changed = false;

/*
unordered_map< vector<int>, vector<int> > hashtable_left;
unordered_map< vector<int>, vector<int> > hashtable_right;
*/

void PrintMatrix(vector<int> matrix)
{
    cout << "\nMatrix\n";

    auto inicio = matrix.begin();

    for (int i = 0; i < row_size * row_size; i++)
    {

        cout << *(inicio + i);

        (i + 1) % row_size == 0 ? cout << endl : cout << ' ';
    }
}

vector<int> ReadMatrix()
{
    vector<int> matrix(row_size * row_size);

    string line;
    int n;

    for (auto it = matrix.begin(); it != matrix.end(); it++)
    {
        cin >> n;
        *it = n;
        max_value += n;

        if (max_atual < n)
            max_atual = n;
    }

    return matrix;
}

vector<int> MoveLeft(vector<int> matrix)
{
    auto matrix_iterator = matrix.begin();
    vector<int>::iterator position_iterator;
    int last_number, first_position, position;

    for (int i = 0; i < row_size * row_size; i += row_size)
    {
        last_number = -1;
        first_position = i;

        for (int j = 0; j < row_size; j++)
        {
            position = i + j;
            position_iterator = matrix_iterator + position;

            if (*position_iterator != 0)
            {
                if (*position_iterator == last_number)
                {
                    auto multiplied_iterator = (matrix_iterator + first_position - 1);
                    *multiplied_iterator *= 2;
                    last_number = -1;
                    *position_iterator = 0;

                    has_changed = true;
                    is_completed = *multiplied_iterator == max_value;

                    if (max_atual < *multiplied_iterator)
                    {
                        max_atual = *multiplied_iterator;
                        moves_needed = log2(max_value / max_atual);
                    }
                }

                else if (position != first_position)
                {
                    last_number = *(position_iterator);
                    *(matrix_iterator + first_position) = last_number;
                    *position_iterator = 0;
                    first_position++;
                }

                else
                {
                    last_number = *(position_iterator);
                    first_position++;
                }
            }
        }
    }

    return matrix;
}

vector<int> MoveRight(vector<int> matrix)
{
    auto matrix_iterator = matrix.begin();
    vector<int>::iterator position_iterator;
    int last_number, first_position, position;

    for (int i = 0; i < row_size * row_size; i += row_size)
    {
        last_number = -1;
        first_position = i + row_size - 1;

        for (int j = row_size - 1; j >= 0; j--)
        {
            position = i + j;
            position_iterator = matrix_iterator + position;

            if (*position_iterator != 0)
            {
                if (*position_iterator == last_number)
                {
                    auto multiplied_iterator = (matrix_iterator + first_position + 1);
                    *multiplied_iterator *= 2;
                    last_number = -1;
                    *position_iterator = 0;

                    has_changed = true;
                    is_completed = *multiplied_iterator == max_value;

                    if (max_atual < *multiplied_iterator)
                    {
                        max_atual = *multiplied_iterator;
                        moves_needed = log2(max_value / max_atual);
                    }
                }

                else if (position != first_position)
                {
                    last_number = *(position_iterator);
                    *(matrix_iterator + first_position) = last_number;
                    *position_iterator = 0;
                    first_position--;
                }

                else
                {
                    last_number = *(position_iterator);
                    first_position--;
                }
            }
        }
    }

    return matrix;
}

vector<int> MoveUp(vector<int> matrix)
{
    auto matrix_iterator = matrix.begin();
    vector<int>::iterator position_iterator;
    int last_number, first_position, position;

    for (int i = 0; i < row_size; i++)
    {
        last_number = -1;
        first_position = i;

        for (int j = 0; j < row_size * row_size; j += row_size)
        {
            position = i + j;
            position_iterator = matrix_iterator + position;

            if (*position_iterator != 0)
            {
                if (*position_iterator == last_number)
                {
                    auto multiplied_iterator = (matrix_iterator + first_position - row_size);
                    *multiplied_iterator *= 2;
                    last_number = -1;
                    *position_iterator = 0;

                    has_changed = true;
                    is_completed = *multiplied_iterator == max_value;

                    if (max_atual < *multiplied_iterator)
                    {
                        max_atual = *multiplied_iterator;
                        moves_needed = log2(max_value / max_atual);
                    }
                }

                else if (position != first_position)
                {
                    last_number = *(position_iterator);
                    *(matrix_iterator + first_position) = last_number;
                    *position_iterator = 0;
                    first_position += row_size;
                }

                else
                {
                    last_number = *(position_iterator);
                    first_position += row_size;
                }
            }
        }
    }

    return matrix;
}

vector<int> MoveDown(vector<int> matrix)
{
    auto matrix_iterator = matrix.begin();
    vector<int>::iterator position_iterator;
    int last_number, first_position, position;

    for (int i = 0; i < row_size; i++)
    {
        last_number = -1;
        first_position = i + row_size * (row_size - 1);

        for (int j = row_size * (row_size - 1); j >= 0; j -= row_size)
        {
            position = i + j;
            position_iterator = matrix_iterator + position;

            if (*position_iterator != 0)
            {
                if (*position_iterator == last_number)
                {

                    auto multiplied_iterator = (matrix_iterator + first_position + row_size);
                    *multiplied_iterator *= 2;
                    last_number = -1;
                    *position_iterator = 0;

                    has_changed = true;
                    is_completed = *multiplied_iterator == max_value;

                    if (max_atual < *multiplied_iterator)
                    {
                        max_atual = *multiplied_iterator;
                        moves_needed = log2(max_value / max_atual);
                    }
                }

                else if (position != first_position)
                {
                    last_number = *(position_iterator);
                    *(matrix_iterator + first_position) = last_number;
                    *position_iterator = 0;
                    first_position -= row_size;
                }

                else
                {
                    last_number = *(position_iterator);
                    first_position -= row_size;
                }
            }
        }
    }

    return matrix;
}

void Recursion(vector<int> matrix, int moves_left, short last_move)
{
    if (is_completed) // Só houver 1 número restante
    {
        is_completed = false;
        best_moves_left = moves_left; // Acho que nao precisamos dos returns ent XD
    }

    else if (moves_left > 0 && moves_left >= moves_needed && moves_left > best_moves_left + 1)
    {
        // Last Move -> 1 = Right
        //              2 = Down
        //              3 = Left
        //              4 = Up

        if (last_move != 1 || has_changed)
        {
            has_changed = false;
            Recursion(MoveRight(matrix), moves_left - 1, 1);
        }

        if (last_move != 2 || has_changed)
        {
            has_changed = false;
            Recursion(MoveDown(matrix), moves_left - 1, 2);
        }

        if (last_move != 3 || has_changed)
        {
            has_changed = false;
            Recursion(MoveLeft(matrix), moves_left - 1, 3);
        }

        if (last_move != 4 || has_changed)
        {
            has_changed = false;
            Recursion(MoveUp(matrix), moves_left - 1, 4);
        }
    }
}

void MainMatrices()
{
    int max_moves;
    vector<int> matrix;

    cin >> row_size >> max_moves;

    matrix = ReadMatrix();

    double intpart;

    if (modf(log2(max_value), &intpart) == 0.0)
    {
        best_moves_left = -1;
        moves_needed = log2(max_value / max_atual);
        Recursion(matrix, max_moves, -1);

        //cout << "Yo?" << endl;

        if (best_moves_left == -1)
            cout << "no solution" << endl;

        else
            cout << max_moves - best_moves_left << endl;
    }

    else
        cout << "no solution" << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n_line;
    int num_matrices = 0;

    cin >> n_line;

    num_matrices = n_line;

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
