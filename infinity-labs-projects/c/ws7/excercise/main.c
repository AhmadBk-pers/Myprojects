
#include <stdio.h>

#include "g.h"

void Foo();

int main()
{
	printf("%d", g_s);
	
	Foo();
	
	printf("%d", g_s);
	
	return 0;
}
