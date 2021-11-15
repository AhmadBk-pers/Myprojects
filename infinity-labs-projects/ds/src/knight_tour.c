/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ------
* Description   Knight tour module 
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <limits.h>	/* CHAR_BIT */
#include <stdlib.h> /* free */
#include <assert.h>

#include "bit_array.h"


#define INVALID_INDEX (size_t)-1
#define SUCCESS 0
#define FAIL 1
#define BITS_ARR_BIT_NUM (sizeof(bitsarr_t) * CHAR_BIT) 

static int KnightTourStep(size_t **final_path, size_t rows, size_t cols, size_t index, size_t step_num, const bitsarr_t *available_moves_LUT);
static void InitAvailableMovesLUT(bitsarr_t *available_moves, size_t rows, size_t cols);
static void InitFinalPath(size_t **final_path, size_t rows, size_t cols);
static int CalculateIndex(size_t cols, size_t start_x, size_t start_y);
static size_t GetRowNumber(size_t cols, size_t index);
static size_t GetColNumber(size_t cols, size_t index);
static size_t GetNextMoveIndex(bitsarr_t *available_moves_ptr, const bitsarr_t *available_moves_LUT, size_t **final_path, size_t cols);
static bitsarr_t GetAvailableMoves(size_t index, size_t rows, size_t cols);
static void AddPosition(bitsarr_t *available_moves_ptr, int row, int col, size_t rows, size_t cols);


int KnightTour(size_t **final_path, size_t rows, size_t cols, size_t start_x, size_t start_y)
{
    bitsarr_t *available_moves_LUT = NULL;
    size_t index = 0;
    int status = 0;

    assert(final_path);

    available_moves_LUT = (bitsarr_t *)malloc(rows * cols * sizeof(bitsarr_t));
    if (!available_moves_LUT)
    {
        return FAIL;
    }

    InitFinalPath(final_path, rows, cols);
    InitAvailableMovesLUT(available_moves_LUT, rows, cols);

    index = CalculateIndex(cols, start_x, start_y);

    status = KnightTourStep(final_path, rows, cols, index, 1, available_moves_LUT);
    
    free(available_moves_LUT);

    return status;
}

static int KnightTourStep(size_t **final_path, size_t rows, size_t cols, size_t index, size_t step_num, const bitsarr_t *available_moves_LUT)
{
    bitsarr_t available_moves = 0;
    size_t row = 0, col = 0;
    int status = 0;
    
    assert(final_path);
    assert(available_moves_LUT);

    row = GetRowNumber(cols, index);
    col = GetColNumber(cols, index);

    if (0 != final_path[row][col])
    {
        return FAIL;    
    }

    final_path[row][col] = step_num;

    if (rows * cols == step_num)
    {
        return SUCCESS;
    }

    available_moves = available_moves_LUT[index];

    do
    {
        index = GetNextMoveIndex(&available_moves, available_moves_LUT, final_path, cols);

        if (INVALID_INDEX == index)
        {
            final_path[row][col] = 0;

            return FAIL;
        }
        status = KnightTourStep(final_path, rows, cols, index, step_num + 1, available_moves_LUT);

    }while(status);

    return SUCCESS;
}

static size_t GetRowNumber(size_t cols, size_t index)
{
    return index / cols;
}

static size_t GetColNumber(size_t cols, size_t index)
{
    return index % cols;
}

static int CalculateIndex(size_t cols, size_t start_x, size_t start_y)
{
    return (cols * start_x) + start_y;
}

/*returns INVALID_INDEX in case of no moves available*/
static size_t GetNextMoveIndex(bitsarr_t *available_moves_ptr, const bitsarr_t *available_moves_LUT, size_t **final_path, size_t cols)
{
    size_t index = 0, min_moves_index = INVALID_INDEX, min_number_of_moves = 9;

    assert(available_moves_ptr);

    if (!*available_moves_ptr)
    {
        return INVALID_INDEX;
    }

    for (index = 0; index < (int)BITS_ARR_BIT_NUM && *available_moves_ptr; ++index)
    {
        if (BitsArrGetVal(*available_moves_ptr, index))
        {
            size_t number_of_moves = BitsArrCountOn(available_moves_LUT[index]);

            if (number_of_moves < min_number_of_moves)
            {
                size_t row = GetRowNumber(cols, index), col = GetColNumber(cols, index);
                
                if (0 == final_path[row][col])
                {
                    min_number_of_moves = number_of_moves;
                    min_moves_index = index;
                }
                else
                {
                    *available_moves_ptr = BitsArrSetOff(*available_moves_ptr, index);
                }
            }
        }
    }

    if (INVALID_INDEX != min_moves_index)
    {
        *available_moves_ptr = BitsArrSetOff(*available_moves_ptr, min_moves_index);
    }

    return min_moves_index;
}

static void InitFinalPath(size_t **final_path, size_t rows, size_t cols)
{
    size_t i = 0, j = 0;

    assert(final_path);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            final_path[i][j] = 0;
        }
    }
}

static void InitAvailableMovesLUT(bitsarr_t *available_moves, size_t rows, size_t cols)
{
    size_t i = 0, j = 0, index = 0;

    assert(available_moves);

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            index = CalculateIndex(cols, i, j);
            available_moves[index] = GetAvailableMoves(index, rows, cols);
        }
    }
}

static bitsarr_t GetAvailableMoves(size_t index, size_t rows, size_t cols)
{
    bitsarr_t available_moves = 0x0;
    size_t row = 0, col = 0;

    row = GetRowNumber(cols, index);
    col = GetColNumber(cols, index);

    AddPosition(&available_moves, (int)row - 2, (int)col - 1, rows, cols);
    AddPosition(&available_moves, (int)row - 2, (int)col + 1, rows, cols);
    AddPosition(&available_moves, (int)row + 2, (int)col - 1, rows, cols);
    AddPosition(&available_moves, (int)row + 2, (int)col + 1, rows, cols);
    AddPosition(&available_moves, (int)row - 1, (int)col - 2, rows, cols);
    AddPosition(&available_moves, (int)row - 1, (int)col + 2, rows, cols);
    AddPosition(&available_moves, (int)row + 1, (int)col - 2, rows, cols);
    AddPosition(&available_moves, (int)row + 1, (int)col + 2, rows, cols);

    return available_moves;
}

static void AddPosition(bitsarr_t *available_moves_ptr, int row, int col, size_t rows, size_t cols)
{
    size_t position = 0;

    assert(available_moves_ptr);

    if ((0 <= row && row < (int)rows) && (0 <= col && col < (int)cols))
    {
        position = CalculateIndex(cols, row, col);
        *available_moves_ptr = BitsArrSetOn(*available_moves_ptr, position);
    }
}