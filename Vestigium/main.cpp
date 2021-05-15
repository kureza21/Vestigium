/** \brief implementation of Vestigium Problem in 2020 Google Code Jam Qualification Round
 *
 * \param kureza21
 * \param
 * \return
 *
 */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cstring>

using namespace std;

typedef struct GridType
{
    int col;
    int row;
    int* data;
};

GridType* MakeGrid(int col, int row)
{
    GridType* grid = (GridType*)malloc(sizeof(GridType));
    grid->data = (int*)malloc (sizeof(int)*col*row);
    grid->col = col;
    grid->row = row;
    for (int i =0; i < grid->col * grid->row ; i++)
        grid->data[i] = 0;
    return grid;
}

void FillGrid(GridType* grid, int j)
{
    for (int i =0; i < (grid->col * grid->row) ; i++)
        grid->data[i] = j;
}

int ReadGrid(GridType* grid, int col, int row)
{
    if (grid == NULL)
        return NULL;

    if (col >= grid->col || row >= grid->row)
        return NULL;

    return grid->data[(row * (grid->row))+col];
}

void WriteGrid(GridType*grid, int col, int row, int i)
{
    if (grid == NULL)
        return;

    if (col >= grid->col || row >= grid->row)
        return;

    grid->data[(row * (grid->row))+col] = i;

}

void PrintGrid(GridType* grid)
{
    for (int i =0 ; i < grid->col ; i++)
    {
        for (int j = 0 ; j < grid->row; j++)
        {
            cout << ReadGrid(grid,i,j)<< " ";
        }
        cout << endl;
    }
}


/*trace duplicate value in the grid array, once found it returns a value*/
/*traced via columns*/
void find_dup_col(GridType*g , int row, int start_col, int* ret)
{
    if (start_col > g->col)
    {
        return;
    }

    for (int i = start_col+1 ; i < g->col ; i++ )
    {
        if (ReadGrid(g,start_col,row) == ReadGrid(g,i,row))
        {
            ret[0]++;
            return;
        }
    }
    find_dup_col(g,row,start_col+1,ret);

}

/*same as above but it traces via rows*/
/*traced via rows*/
void find_dup_row(GridType*g , int col, int start_row, int* ret)
{
    if (start_row > g->row)
    {
        return;
    }

    for (int i = start_row+1 ; i < g->row ; i++ )
    {
        if (ReadGrid(g,col,start_row) == ReadGrid(g,col,i))
        {
            ret[0]++;
            return;
        }
    }
    find_dup_row(g,col,start_row+1,ret);

}

void solve (GridType* g)
{
    int diagonal_sum = 0;

    //diagonal sum
    for (int c = 0 ; c < g->col ; c++)
    {
        diagonal_sum += ReadGrid(g,c,c);
    }

    //check repeated row
    int r=0; int c =0;
    int duplicate_row =0;
    int duplicate_col =0;

    int sum = 0;

    for (int i =0 ; i < g->col ; i++)
    {
        find_dup_row(g,i,0,&duplicate_row);
        find_dup_col(g,i,0,&duplicate_col);
    }

    cout << diagonal_sum << " " << duplicate_row << " " << duplicate_col ;

}

int main()
{
    //cout << "Hello world!" << endl;
    int test_case =0;
    int problem_data_size =0;
    int grid_size =0;
    int data;
    cin >> test_case;
    GridType* grid_data;


    vector <GridType*> GridCollection;

    for (int n = 0; n < test_case ; n++)
    {
        cin >> problem_data_size;

        /*the grid is square so the columns = rows*/
        grid_data = MakeGrid(problem_data_size,problem_data_size);
        FillGrid(grid_data,0);

        for (int c = 0 ; c < problem_data_size ; c++)
        {
            for ( int r = 0 ; r < problem_data_size; r++)
            {
                cin >> data;
                WriteGrid(grid_data,c,r,data);
            }

        }
        GridCollection.push_back(grid_data);
    }

    int case_index =1;
    for (GridType* g:GridCollection)
    {
        cout << "Case #" << case_index << ": ";
        solve(g);
        cout << endl;
        case_index++;
    }

    GridCollection.clear();

    return 0;
}
