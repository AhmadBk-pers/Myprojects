#include <stdlib.h> 



int g1;
static int g2;
static int g3 = 0;
static int g4 = 8;

static void foo1()
{
	static int g5;
	int l1 = 9;
}

void foo2()
{
	static int g6 = 0;
	static int g7 = 7;
	
	void *p = malloc(10);
	free(p); p = 0;
	
}

extern void bar();
