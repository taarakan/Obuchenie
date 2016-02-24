#include <stdio.h>
#include <conio.h>
struct s
{
bool b0:1;
bool b1:1;
bool b2:1;
bool b3:1;
bool b4:1;
bool b5:1;
bool b6:1;
bool b7:1;
};
int main()
{int b;
    long a=126;
    s *t=(s*)&a;
    printf("%d",t->b7);
    printf("%d",t->b6);
    printf("%d",t->b5);
    printf("%d",t->b4);
    printf("%d",t->b3);
    printf("%d",t->b2);
    printf("%d",t->b1);
    printf("%d",t->b0);
	b=sizeof(s);
	printf("\n%d",b);
    getch();
	return 0;
}
