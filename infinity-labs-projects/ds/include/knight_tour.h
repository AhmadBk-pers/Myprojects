/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Version       1.2.0                                           *
 ~ Author        OL110 Students                                  ~
 * Reviewer      Binyamin                                        *
 ~ Description   Knight's Tour - Header Module                   ~
 * Group         OL110                                           *
 ~ Company       ILRD Ramat Gan                                  ~
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef __KNIGHT_OL_110_H__
#define __KNIGHT_OL_110_H__

#include <stddef.h> /* size_t */


/*
param :
    final_path - 2D array of dimentions rows*cols, to store the result.
        the result is represented by storing step/index number in each cell.
        (0 <= final_path[i][j] < rows*cols, for each valid i and j).
    rows, cols - the dimentions of the board.
    start_x, start_y - initial position of the knight.
return : 0 on success of finding a knight tour, with update of 'final_path',
    or non-zero on failure, 'final_path' array update undefined.
complexity : 8 ^ (rows * cols).
*/
int KnightTour(size_t **final_path, size_t rows, size_t cols,
                size_t start_x, size_t start_y);

#endif /* __KNIGHT_OL_110_H__ */