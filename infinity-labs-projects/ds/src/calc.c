/*****************************************************************************
* Author        Ahmad Bakri
* Reviewer      ---
* Description    combined with Finite State Machine.
                Operators: +, -, *, /, ^.
* Group         OL110
* Company       ILRD Ramat Gan
* ****************************************************************************/

#include <stdlib.h>     /* malloc, free, strtod */
#include <assert.h>     /* assert */
#include <math.h>       /* pow */
#include <ctype.h>      /* isspace */

#include "calc.h"       /* API of this file */
#include "stack.h"      /* for stack_t and functions of stack */

#define STACK_SIZE 20

enum {WAITING_NUMBER, WAITING_OPERATOR, SYN_ERR};
enum for_precedence_teable {LEFT_BRACKET = -1, INVALID_CHAR = 0};

struct calc
{
    stack_t *numbers;
    stack_t *operators;
    int state;
};

static const char INVALID_OPERATOR = 0;

static int precedence[256] = {INVALID_CHAR};

static void InitPrecedenceTable(void);
static int IsEmptyOperators(const calc_t *calc);
static int IsEmptyNumbers(const calc_t *calc);
static char PeekOperator(const calc_t *calc);
static char PopOperator(calc_t *calc);
static void PushOperator(calc_t *calc, char operator);
static double PopNumber(calc_t *calc);
static void PushNumber(calc_t *calc, double num);
static int FinalCalculate(calc_t *calc, double *result);
static int AddRightBracket(calc_t *calc);
static void AddLeftBracket(calc_t *calc);
static void AddOperator(char **end_ptr, calc_t *calc);
static void AddNumber(char **end_ptr, calc_t *calc);
static int MakeLastOperation(calc_t *calc);
static char *SkipSpaces(char **end_ptr);
static void InitCalc(calc_t *calc);

calc_t *CalcCreate(void)
{
	calc_t *calc = NULL;
    stack_t *numbers = NULL;
    stack_t *operators = NULL;

    calc = malloc(sizeof(*calc));
    if (!calc)
    {
        return NULL;
    }

    numbers = StackCreate(STACK_SIZE);
    if (!numbers)
    {
        free(calc);
        calc = NULL;

        return NULL;
    }

    operators = StackCreate(STACK_SIZE);
    if (!operators)
    {
        free(calc);
        calc = NULL;
        free(numbers);
        numbers = NULL;

        return NULL;
    }

    calc->numbers = numbers;
    calc->operators = operators;
    calc->state = WAITING_NUMBER;

    PushOperator(calc, INVALID_OPERATOR);

    return calc;
}

void CalcDestroy(calc_t *calc)
{
	assert (calc);

    StackDestroy(calc->numbers);
    StackDestroy(calc->operators);
    calc->numbers = NULL;
    calc->operators = NULL;

    free(calc);
    calc = NULL;
}


calc_status_t CalcCalculate(const char *expression, double *result, calc_t *calc)
{
	char *exp_ptr = (char *)expression;

    assert (expression);
    assert (result);
    assert (calc);
    
    InitCalc(calc);
    
    while (*exp_ptr)
    {
    	if (SYN_ERR == calc->state)
    	{
    		return CALC_SYNTAX_ERROR;
    	}
    	else if (WAITING_NUMBER == calc->state)
    	{
    		AddNumber(&exp_ptr, calc);
    	}
    	else if (WAITING_OPERATOR == calc->state)
    	{
    		AddOperator(&exp_ptr, calc);
    	}
    }
    
    if (WAITING_OPERATOR != calc->state)
    {
        return CALC_SYNTAX_ERROR;
    }

    return FinalCalculate(calc, result);
}

static void AddOperator(char **end_ptr, calc_t *calc)
{
    char peek = 0;
    unsigned char operator = 0;
    int status = 0;

    assert (calc);
    assert (end_ptr);

    operator = *(SkipSpaces(end_ptr));
    (*end_ptr)++;

    InitPrecedenceTable();

    if (INVALID_CHAR == precedence[operator] ||
        LEFT_BRACKET == precedence[operator])
    {
        calc->state = SYN_ERR;
        return;
    }
    else if (')' == operator)
    {
        status = AddRightBracket(calc);
        if (status != CALC_SUCCESS)
        {
            calc->state = SYN_ERR;
            return;
        }

        calc->state = WAITING_OPERATOR;
        return;
    }

    peek = PeekOperator(calc);

    while (peek != INVALID_OPERATOR &&
            precedence[(unsigned char)operator] <= 
            precedence[(unsigned char)peek])
    {
        int status = 0;

        if ('^' == operator)
        {
            break;
        }

        status = MakeLastOperation(calc);

        if (status != CALC_SUCCESS)
        {
            return;
        }

        peek = PeekOperator(calc);
    }

    PushOperator(calc, operator);
    calc->state = WAITING_NUMBER;
}

static void InitPrecedenceTable(void)
{
    static int flag = 1;

    if (flag)
    {
        precedence['('] = -1;
        precedence[')'] = 4;
        precedence['+'] = 1;
        precedence['-'] = 1;
        precedence['*'] = 2;
        precedence['/'] = 2;
        precedence['^'] = 3;

        flag = 0;
    }
}

static int AddRightBracket(calc_t *calc)
{
    char peek = 0;
    
    assert (calc);

    peek = PeekOperator(calc);

    while (peek != '(')
    {
        if (IsEmptyOperators(calc))
        {
            calc->state = SYN_ERR;
            return CALC_SYNTAX_ERROR;
        }

        MakeLastOperation(calc);

        peek = PeekOperator(calc);
    }

    PopOperator(calc);

    return CALC_SUCCESS;
}

static int MakeLastOperation(calc_t *calc)
{
    double right_num = 0;
    double left_num = 0;
    double result = 0;
    char operator = 0;

    assert (calc);

    right_num = PopNumber(calc);
    left_num = PopNumber(calc);
    operator = PopOperator(calc);

    switch (operator)
    {
        case '+':
            result = left_num + right_num;
            break;

        case '-':
            result = left_num - right_num;
            break;

        case '*':
            result = left_num * right_num;
            break;

        case '/':
            result = left_num / right_num;
            if (0 == right_num)
            {
                return CALC_MATH_ERROR;
            }
            break;

        case '^':
            result = pow(left_num, right_num);
            break;
    }

    PushNumber(calc, result);

    return CALC_SUCCESS;
}

static void AddNumber(char **end_ptr, calc_t *calc)
{
    char *nptr = *end_ptr;
    double num = strtod(nptr, end_ptr);

    if (nptr != *end_ptr)
    {
        PushNumber(calc, num);
        calc->state = WAITING_OPERATOR;
    }
    else if (*(SkipSpaces(end_ptr)))
    {
        if ('(' == **end_ptr)
        {
            AddLeftBracket(calc);
            (*end_ptr)++;
            calc->state = WAITING_NUMBER;
        }
        else
        {
            calc->state = SYN_ERR;
        }
    }
}

static char *SkipSpaces(char **end_ptr)
{
    assert (end_ptr);

    while (isspace(**end_ptr))
    {
        (*end_ptr)++;
    }

    return *end_ptr;
}

static void AddLeftBracket(calc_t *calc)
{
    PushOperator(calc, '(');
}

static void InitCalc(calc_t *calc)
{
    while (!IsEmptyNumbers(calc))
    {
        PopNumber(calc);
    }

    while (!IsEmptyOperators(calc))
    {
        PopOperator(calc);
    }

    calc->state = WAITING_NUMBER;
}

static int FinalCalculate(calc_t *calc, double *result)
{
    int status = 0;

    assert (calc);

    if (PeekOperator(calc) == '(')
    {
        return CALC_SYNTAX_ERROR;
    }

    while (!IsEmptyOperators(calc))
    {
        status = MakeLastOperation(calc);

        if (status != CALC_SUCCESS)
        {
            return status;
        }
    }

    *result = PopNumber(calc);

    return CALC_SUCCESS;
}

static void PushNumber(calc_t *calc, double num)
{
    assert (calc);

    StackPush(calc->numbers, (void *)*(size_t *)&num);
}

static double PopNumber(calc_t *calc)
{
    void *popped = 0;

    assert (calc);

    popped = StackPop(calc->numbers);

    return *(double *)&popped;
}

static void PushOperator(calc_t *calc, char operator)
{
    assert (calc);

    StackPush(calc->operators, (void *)*(size_t *)&operator);
}

static char PopOperator(calc_t *calc)
{
    void *popped = NULL;

    assert (calc);

    popped = StackPop(calc->operators);

    return *(char *)&popped;
}

static char PeekOperator(const calc_t *calc)
{
    void *popped = NULL;

    assert (calc);

    popped = StackPeek(calc->operators);

    return *(char *)&popped;
}

static int IsEmptyOperators(const calc_t *calc)
{
    assert (calc);

    return (PeekOperator(calc) == INVALID_OPERATOR);
}

static int IsEmptyNumbers(const calc_t *calc)
{
    assert (calc);

    return StackIsEmpty(calc->numbers);
}
