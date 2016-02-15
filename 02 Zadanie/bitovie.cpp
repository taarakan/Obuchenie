#include <stdio.h>
#include <conio.h>
struct s
{
unsigned b0:1;
unsigned b1:1;
unsigned b2:1;
unsigned b3:1;
unsigned b4:1;
unsigned b5:1;
unsigned b6:1;
unsigned b7:1;
unsigned b8:1;
unsigned b9:1;
unsigned b10:1;
unsigned b11:1;
unsigned b12:1;
unsigned b13:1;
unsigned b14:1;
unsigned b15:1;
unsigned b16:1;
unsigned b17:1;
unsigned b18:1;
unsigned b19:1;
unsigned b20:1;
unsigned b21:1;
unsigned b22:1;
unsigned b23:1;
unsigned b24:1;
unsigned b25:1;
unsigned b26:1;
unsigned b27:1;
unsigned b28:1;
unsigned b29:1;
unsigned b30:1;
unsigned b31:1;
};
int main()
{
    long a=158;
    s *t=(s*)&a;
    printf("%d",t->b31);
	printf("%d",t->b30);
	printf("%d",t->b29);
	printf("%d",t->b28);
	printf("%d",t->b27);
	printf("%d",t->b26);
	printf("%d",t->b25);
	printf("%d",t->b24);
	printf("%d",t->b23);
	printf("%d",t->b22);
	printf("%d",t->b21);
	printf("%d",t->b20);
	printf("%d",t->b19);
	printf("%d",t->b18);
	printf("%d",t->b17);
	printf("%d",t->b16);
	printf("%d",t->b15);
	printf("%d",t->b14);
	printf("%d",t->b13);
	printf("%d",t->b12);
	printf("%d",t->b11);
	printf("%d",t->b10);
    printf("%d",t->b9);
    printf("%d",t->b8);
    printf("%d",t->b7);
    printf("%d",t->b6);
    printf("%d",t->b5);
    printf("%d",t->b4);
    printf("%d",t->b3);
    printf("%d",t->b2);
    printf("%d",t->b1);
    printf("%d",t->b0);
    getch();
	return 0;
}
