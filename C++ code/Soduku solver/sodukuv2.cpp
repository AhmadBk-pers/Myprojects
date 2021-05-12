#include <iostream>
#include <ctime> 

//import numpy as np

//import time

time_t start, end;

int counter = 1;

bool possible(int y, int x, int n, int grid[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        if (grid[i][x] == n)
            return false;
        if (grid[y][i] == n)
            return false;
    }
    int y0 = (y / 3) * 3;
    int x0 = (x / 3) * 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[y0 + i][x0 + j] == n)
                return false;
        }
    }
    return true;
}

bool solve(int grid[9][9])
{

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (grid[i][j] == 0)
            {
                for (int pos = 1; pos < 10; pos++)
                {
                    if (possible(i, j, pos, grid))
                    {
                        grid[i][j] = pos;
                        solve(grid);
                        grid[i][j] = 0;
                    }
                }

                return true;
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            std::cout << grid[i][j];
        std::cout << std::endl;
    }
    end = time(NULL);
    std::cout << "-------------Soloution" << counter << "-------------" << std::endl;
    std::cout << "-------------time" << end - start << "-------------" << std::endl;
    counter += 1;
}


int main()
{
    start = time(NULL);
    int grid1[9][9] = { {8, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 3, 6, 0, 0, 0, 0, 0},
        {0, 7, 0, 0, 9, 0, 2, 0, 0},
        {0, 5, 0, 0, 0, 7, 0, 0, 0},
        {0, 0, 0, 0, 4, 5, 7, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 3, 0},
        {0, 0, 1, 0, 0, 0, 0, 6, 8},
        {0, 0, 8, 0, 0, 0, 0, 1, 0},
        {0, 9, 0, 0, 0, 0, 4, 0, 0} };

    solve(grid1);

}