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
    bool local_has_changed = has_changed;
    vector<int> aux;

    if (is_completed) // Solução melhor que a existente
    {
        is_completed = false;
        best_moves_left = moves_left;
    }

    else if (moves_left > 0 && moves_left >= moves_needed && moves_left > best_moves_left + 1 && last_move != 0)
    {
        // Last Move -> 0001 = Right
        //              0010 = Down
        //              0100 = Left
        //              1000 = Up
        // Onde 1 representa que se pode fazer o move

        if (last_move & 1 || local_has_changed)
        {
            has_changed = false;
            aux = MoveRight(matrix);

            if (!has_changed)
                Recursion(aux, moves_left - 1, last_move & 14); // XXXX and 1110
            else
                Recursion(aux, moves_left - 1, 15);
        }

        if (last_move & 2 || local_has_changed)
        {
            has_changed = false;
            aux = MoveDown(matrix);

            if (!has_changed)
                Recursion(aux, moves_left - 1, last_move & 13); // XXXX and 1101
            else
                Recursion(aux, moves_left - 1, 15);
        }

        if (last_move & 4 || local_has_changed)
        {
            has_changed = false;
            aux = MoveLeft(matrix);

            if (!has_changed)
                Recursion(aux, moves_left - 1, last_move & 11); // XXXX and 1011
            else
                Recursion(aux, moves_left - 1, 15);
        }

        if (last_move & 8 || local_has_changed)
        {
            has_changed = false;
            aux = MoveUp(matrix);

            if (!has_changed)
                Recursion(aux, moves_left - 1, last_move & 7); // XXXX and 0111
            else
                Recursion(aux, moves_left - 1, 15);
        }
    }
}

void MainMatrices()
{
    int max_moves;
    vector<int> matrix;
    double intpart;

    cin >> row_size >> max_moves;

    matrix = ReadMatrix();

    moves_needed = log2(max_value / max_atual);

    if (modf(log2(max_value), &intpart) == 0.0 && moves_needed <= max_moves)
    {
        best_moves_left = -1;

        Recursion(matrix, max_moves, 15);

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
