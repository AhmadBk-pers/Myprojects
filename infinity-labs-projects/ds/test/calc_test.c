#include <stdio.h>
#include <math.h>

#include "calc.h"

typedef struct exp_test_case
{
    char*           expression;
    double          result;
    calc_status_t   status;
}exp_test_case_t;


int main()
{
    int i, num_of_errors = 0;
    calc_status_t status = CALC_SUCCESS;
    double res;
    calc_t *calc = CalcCreate();
    const char *errors[] = {"SUCCESS", "MATH ERROR", "MEMORY ALLOCATION", "SYNTAX"};

    exp_test_case_t  test_cases[] = {
            {"1", 1, CALC_SUCCESS},
            {"2345", 2345, CALC_SUCCESS},
            {"(123)", 123, CALC_SUCCESS},
            {"1+1", 2, CALC_SUCCESS},
            {"33-12", 21, CALC_SUCCESS},
            {"333*3", 999, CALC_SUCCESS},
            {"1/2", 0.5, CALC_SUCCESS},
            {"3^2", 9, CALC_SUCCESS},
            {"(1+1)", 2, CALC_SUCCESS},
            {"(5-3)-2", 0, CALC_SUCCESS},
            {"5-(3-2)", 4, CALC_SUCCESS},
            {"5-3-2", 0, CALC_SUCCESS},
            {"(320/8)/4", 10, CALC_SUCCESS},
            {"320    /  (   8   /   4   )", 160, CALC_SUCCESS},
            {"320/8/4", 10, CALC_SUCCESS},
            {"1+2+3+4", 10, CALC_SUCCESS},
            {"1-2-3-4", -8, CALC_SUCCESS},
            {"1*2*3*4", 24, CALC_SUCCESS},
            {"2^3^2", 512, CALC_SUCCESS},
            {"12-3+4",  13, CALC_SUCCESS},
            {"12+3-4",  11, CALC_SUCCESS},
            {"8/4*2",  4, CALC_SUCCESS},
            {"8*4/2",  16, CALC_SUCCESS},
            {"12+3*5",  27, CALC_SUCCESS},
            {"12*3+5",  41, CALC_SUCCESS},
            {"2*4^2-+1", 31, CALC_SUCCESS},
            {"2*(4+1)-3", 7, CALC_SUCCESS},
            {"2^(3+5)*2", 512, CALC_SUCCESS},
            {"6+4^ 2    *+2+  1", 39, CALC_SUCCESS},
            {"((2+1)*3)", 9, CALC_SUCCESS},
            {"(2*(2-3))", -2, CALC_SUCCESS},
            {"(3*(3+3)/3)", 6, CALC_SUCCESS},
            {"8/(16*2-30)", 4, CALC_SUCCESS},
            {"(1+2+3+4+5)*2", 30, CALC_SUCCESS},
            {"(2^3^2)*2", 1024, CALC_SUCCESS},
            {"2^(0-2)", 0.25, CALC_SUCCESS},
            {"1/3*6", 2, CALC_SUCCESS},
            {"1/5/2", 0.10, CALC_SUCCESS},
            {"1/(0+-2)", -0.5, CALC_SUCCESS},
            {"4^(1/2)", 2, CALC_SUCCESS},
            {"(1/2)^2", 0.25, CALC_SUCCESS},
            {"(1/2)^-2", 4, CALC_SUCCESS},
            {"((2-4)^3/((2*2)^2*2-30))^2", 16, CALC_SUCCESS},
            {"-1", -1, CALC_SUCCESS},
            {"-1 -2 +3 + +3 + -4", -1, CALC_SUCCESS},
            {"-1.5 - +4.5 - -0.5", -5.5, CALC_SUCCESS},
            {"-1.5-+4.5--0.5", -5.5, CALC_SUCCESS},
            {"-1.5--4.5", 3, CALC_SUCCESS},
            {"-1.5 - -4.5", 3, CALC_SUCCESS},
            {"- 6", 0, CALC_SYNTAX_ERROR},
            {"-", 0, CALC_SYNTAX_ERROR},
            {"7**6", 0, CALC_SYNTAX_ERROR},
            {"2 3", 0, CALC_SYNTAX_ERROR},
            {"+9 *", 0, CALC_SYNTAX_ERROR},
            {"((2-4)^3/((2*2)^2*2-30))^2", 16, CALC_SUCCESS},
            {"-6+-2+-5*-3", 7, CALC_SUCCESS},
            {"-6+-2+-5.5*-3.5", 11.25, CALC_SUCCESS},
            {"+43 - 1", 42, CALC_SUCCESS},
            {"-0.5+0.5", 0, CALC_SUCCESS},
            {"0.5-0.5", 0, CALC_SUCCESS},
            {"-42 * -1", 42, CALC_SUCCESS},
            {"0-42.5", -42.5, CALC_SUCCESS},
            {"0.5+41.5", 42, CALC_SUCCESS},
            {"6/(3-3)", 0, CALC_MATH_ERROR},
            {")6", 0, CALC_SYNTAX_ERROR},
            {"(4))", 0, CALC_SYNTAX_ERROR},
            {"((8", 0, CALC_SYNTAX_ERROR},
            {NULL, 0, CALC_SUCCESS}
    };

    for (i = 0; test_cases[i].expression; ++i)
    {
        status = CalcCalculate(test_cases[i].expression, &res, calc);
        if (status == test_cases[i].status)
        {
            if (CALC_SUCCESS == status)
            {
                /*printf("Expression# %d: %s = %.2f\n",i + 1, test_case[i].expression, res);*/
                if (res != test_cases[i].result)
                {
                    ++num_of_errors;
                    printf("-----> Error. Bad result: Expression: \"%s\".\nExpected: %f. Result: %f.\n\n", test_cases[i].expression, test_cases[i].result, res);
                }
            }
        }
        else
        {
            printf("-----> Error. Bad status: Expression: \"%s\".\nExpected: %s. Status: %s.\n"
                   "\nStopping test cases.\nPerformed %d test cases out of %lu, having %d errors before this one.\n\n",
                   test_cases[i].expression, errors[test_cases[i].status], errors[status], i, sizeof(test_cases) / sizeof(test_cases[0]) - 1, num_of_errors);
            break;
        }
    }

    if (i+1 == (sizeof(test_cases) / sizeof(test_cases[0])))
    {
        printf("Performed %d test cases out of %lu, with %d errors.\n", i, sizeof(test_cases) / sizeof(test_cases[0]) - 1, num_of_errors);
    }

    CalcDestroy(calc); calc = NULL;

    return (0);
}
