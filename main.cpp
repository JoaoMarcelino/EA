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

    for (int i = 0; i < row_size * row_size; i++){

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
                    auto multiplier_iterator = (matrix_iterator + first_position - 1);
					*multiplier_iterator *= 2;
                    last_number = -1;
					*position_iterator = 0;

                    has_changed = true;
                    is_completed = *multiplier_iterator == max_value;
                    if (max_atual < *multiplier_iterator)
						max_atual = *multiplier_iterator;
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
					auto multiplier_iterator = (matrix_iterator + first_position + 1);
                    *multiplier_iterator *= 2;
                    last_number = -1;
					*position_iterator = 0;

                    has_changed = true;
                    is_completed = *multiplier_iterator == max_value;
                    if (max_atual < *multiplier_iterator)
						max_atual = *multiplier_iterator;
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

        for (int j = 0; j < row_size * row_size; j+= row_size)
		{
            position = i + j;
            position_iterator = matrix_iterator + position;
			
            if (*position_iterator != 0)
			{   
				if (*position_iterator == last_number)
				{
                    auto multipier_iterator = (matrix_iterator + first_position - row_size);
                    *multipier_iterator *= 2;
                    last_number = -1;
					*position_iterator = 0;

                    has_changed = true;
                    is_completed = *multipier_iterator == max_value;
                    if (max_atual < *multipier_iterator)
						max_atual = *multipier_iterator;
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
                    
                    auto multipier_iterator = (matrix_iterator + first_position + row_size);
                    *multipier_iterator *= 2;
                    last_number = -1;
					*position_iterator = 0;

                    has_changed = true;
                    is_completed = *multipier_iterator == max_value;
                    if (max_atual < *multipier_iterator)
						max_atual = *multipier_iterator;
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

int Recursion(vector<int> matrix, int moves_left, int moves, string last_move)
{
    vector<int> child(4, -1);
    auto iterator = child.begin();

    if (moves_left <= best_moves_left || log2(max_value / max_atual) > moves_left)  // Se a solução atual for pior
    {
        is_completed = false;
        return -1;
    }

    if (is_completed) // Só houver 1 número restante
    {
        is_completed = false;
        best_moves_left = moves_left;

        return best_moves_left;
    }

    if (moves_left == 0)
        return -1;

    if (last_move != "Right" || has_changed)
    {
        has_changed = false;
        *iterator++ = Recursion(MoveRight(matrix), moves_left - 1, moves + 1, "Right");
    }

    if (last_move != "Down" || has_changed)
    {
        has_changed = false;
        *iterator++ = Recursion(MoveDown(matrix), moves_left - 1, moves + 1, "Down");
    }

    if (last_move != "Left" || has_changed)
    {
        has_changed = false;
        *iterator++ = Recursion(MoveLeft(matrix), moves_left - 1, moves + 1, "Left");
    }

    if (last_move != "Up" || has_changed)
    {
        has_changed = false;
        *iterator = Recursion(MoveUp(matrix), moves_left - 1, moves + 1, "Up");
    }

    return iterator != child.begin() ? *max_element(child.begin(), child.end()) : -1;
}

void MainMatrices()
{
    int max_moves;
    vector<int> matrix;

    cin >> row_size >> max_moves;

    matrix = ReadMatrix();
    
    double intpart;
    //TODO: make money moves

    if (modf(log2(max_value), &intpart) == 0.0)
    {
        best_moves_left = -1;
        Recursion(matrix, max_moves, 0, "");

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

// Acho que deviamos refazer os MoveX e Rotates tmb maybe para tornar a matriz mais eficiente
// Maybe até usar map's ou algo do género como o Shiny tinha dito, maybe matriz linear tmb
// Ou ent a cena que o Rui tinha perguntado sobre pesquisa horizontal ate X, dps vertical
// Also n consegui perceber nada dos MoveX's, tá bué confuso e sem comments é fdd
// Mas dps esclarecemos isso
// Jospy
