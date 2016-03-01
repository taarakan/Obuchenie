#include <stdio.h>
#include <conio.h>
#pragma pack(push, 1)
struct test{
int a;
char b;
int c;
char d;
int e;
 char f;
}a;
int main()
{
    int b;
    b=sizeof(a);
	printf("\n%d",b);
    getch();
	return 0;
}
