#include <iostream.h>
using namespace std
//import numpy as np

//import time




bool possible(int y, int x, int n, int grid[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        if grid[i][x] == n
            return False;
        if grid[y][i] == n
            return False;
    }
    int y0 = (y // 3) * 3;
    int x0 = (x // 3) * 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if grid[y0 + i][x0 + j] == n 
                return False
        }
    }
    return True
}

bool solve(int grid[9][9])
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if grid[i][j] == 0
                for (int pos = 1; pos< 10; pos++)
                {
                    if possible(i, j, pos, grid)
                        grid[i][j] = pos
                        solve(grid1)
                        grid[i][j] = 0
                }

                        return True
        }
    }
    for (int i; i < 9; i++) {

        for (int j; j < 9; j++)
            cout << grid[i][9];
        cound << endl;
    }
}


int main()
{
    int grid1 = [[8, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 3, 6, 0, 0, 0, 0, 0],
        [0, 7, 0, 0, 9, 0, 2, 0, 0],
        [0, 5, 0, 0, 0, 7, 0, 0, 0],
        [0, 0, 0, 0, 4, 5, 7, 0, 0],
        [0, 0, 0, 1, 0, 0, 0, 3, 0],
        [0, 0, 1, 0, 0, 0, 0, 6, 8],
        [0, 0, 8, 0, 0, 0, 0, 1, 0],
        [0, 9, 0, 0, 0, 0, 4, 0, 0], ];

    solve(grid1);

}