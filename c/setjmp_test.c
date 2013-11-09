#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
jmp_buf jmp_los;
void func2()
{
	printf("func2\n");
	longjmp(jmp_los, 0);	
}

void func1()
{
	printf("func1\n");
	func2();
}

int main()
{
	printf("main start\n");
	setjmp(jmp_los);
	func1();
	printf("main end\n");
	return 0;
}
