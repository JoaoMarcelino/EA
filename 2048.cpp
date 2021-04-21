#include <iostream>
#include <sstream>

#include <algorithm>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>

#include <math.h>

#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define UP 4

using namespace std;

int max_value = 0;
int max_atual = 0;
int row_size;
int best_moves_left;

float moves_needed;

bool is_completed = false;
bool has_changed = false;

struct matrix_info
{
    vector<int> matrix;
    bool is_completed = false;
    bool has_changed = false;
    int moves_left;
};

class uint32_vector_hasher
{
public:
    std::size_t operator()(std::vector<int32_t> const &vec) const
    {
        std::size_t seed = vec.size();
        for (auto &i : vec)
        {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

typedef unordered_map<vector<int>, matrix_info, uint32_vector_hasher> hashtable;

hashtable left_table;
hashtable right_table;
hashtable down_table;
hashtable up_table;

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

void MoveLeft(vector<int> &matrix)
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
}

void MoveRight(vector<int> &matrix)
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
}

void MoveUp(vector<int> &matrix)
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
}

void MoveDown(vector<int> &matrix)
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
}

void ChangeVariables(matrix_info &info)
{
    has_changed = info.has_changed;
    is_completed = info.is_completed;
}

void SetVariables(matrix_info &info)
{
    info.has_changed = has_changed;
    info.is_completed = is_completed;
}

void Recursion(vector<int> matrix, int moves_left, short last_move)
{
    matrix_info aux;

    if (is_completed) // Solução melhor que a existente
    {
        is_completed = false;
        best_moves_left = moves_left;
    }

    else if (moves_left > 0 && moves_left >= moves_needed && moves_left > best_moves_left + 1)
    {
        if (last_move != RIGHT || has_changed)
        {
            has_changed = false;
            hashtable::iterator finder = right_table.find(matrix);

            if (finder != right_table.end())
            {
                aux = finder->second;

                if (moves_left <= aux.moves_left)
                    return;
                else
                {
                    ChangeVariables(aux);
                    Recursion(aux.matrix, moves_left - 1, RIGHT);
                }
            }

            else
            {
                aux.matrix = matrix;
                MoveRight(aux.matrix);

                SetVariables(aux);

                aux.moves_left = moves_left;

                right_table[matrix] = aux;
                Recursion(aux.matrix, moves_left - 1, RIGHT);
            }
        }

        if (last_move != DOWN || has_changed)
        {
            has_changed = false;
            hashtable::iterator finder = down_table.find(matrix);

            if (finder != down_table.end())
            {
                aux = finder->second;

                if (moves_left <= aux.moves_left)
                    return;
                else
                {
                    ChangeVariables(aux);
                    Recursion(aux.matrix, moves_left - 1, DOWN);
                }
            }

            else
            {
                aux.matrix = matrix;
                MoveDown(aux.matrix);

                SetVariables(aux);

                aux.moves_left = moves_left;

                down_table[matrix] = aux;
                Recursion(aux.matrix, moves_left - 1, DOWN);
            }
        }

        if (last_move != LEFT || has_changed)
        {
            has_changed = false;
            hashtable::iterator finder = left_table.find(matrix);

            if (finder != left_table.end())
            {
                aux = finder->second;

                if (moves_left <= aux.moves_left)
                    return;
                else
                {
                    ChangeVariables(aux);
                    Recursion(aux.matrix, moves_left - 1, LEFT);
                }
            }

            else
            {
                aux.matrix = matrix;
                MoveLeft(aux.matrix);

                SetVariables(aux);

                aux.moves_left = moves_left;

                left_table[matrix] = aux;
                Recursion(aux.matrix, moves_left - 1, LEFT);
            }
        }

        if (last_move != UP || has_changed)
        {
            has_changed = false;
            hashtable::iterator finder = up_table.find(matrix);

            if (finder != up_table.end())
            {
                aux = finder->second;

                if (moves_left <= aux.moves_left)
                    return;
                else
                {
                    ChangeVariables(aux);
                    Recursion(aux.matrix, moves_left - 1, UP);
                }
            }

            else
            {
                aux.matrix = matrix;
                MoveUp(aux.matrix);

                SetVariables(aux);

                aux.moves_left = moves_left;

                up_table[matrix] = aux;
                Recursion(aux.matrix, moves_left - 1, UP);
            }
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

        Recursion(matrix, max_moves, -1);

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
