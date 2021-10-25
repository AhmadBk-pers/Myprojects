/********************************************************
 * calc.h - calc API
 * Author : Ahmad Bakri
 * Reviewed and approved by : Binyamin
 * 14/10/2021
 * OLRD 110 Ramat Gan
 * *********************************************************/

#ifndef __OL110CALC_H__
#define __OL110CALC_H__

#include <stddef.h> /* size_t */

typedef struct calc calc_t;

/* Enum for different errors - syntax, allocations, division by zero */
/* errors */
typedef enum 
{
    CALC_SUCCESS = 0,
    CALC_MATH_ERROR = 1,
    CALC_ALLOC_ERROR = 2,
    CALC_SYNTAX_ERROR = 3
} calc_status_t;

calc_t *CalcCreate(void);

/* O(n) */
/* input: 1. expression to calculate
          2. pointer to store the calculator result in case of sucess
          3. calculator pointer*/
/* return: see calc_status_t enum  */   
calc_status_t CalcCalculate(const char *expression, double *result, calc_t *calc);

void CalcDestroy(calc_t *calc);


#endif /* __OL110CALC_H__ */

