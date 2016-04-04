#include <stdio.h>
#include "../library/mylib.h"
void main()
{
char c;
int i1;
int i2;
int a;
printf("pervoe chislo ");
scanf("%d",&i1);

printf("vtoroe chislo ");
 scanf("%d",&i2);

while (1)
{
 puts(" 1 - add");
 puts(" 2 - usb");
 puts(" 3 - mul");
 puts(" 4 - div");
 c=getchar();
 switch(c)
 {case '1':a=add(i1,i2);
  break;
  case '2': a=usb(i1,i2);
  break;
  case '3': a=mul(i1,i2);
  break;
  case '4': a=div(i1,i2);
  break;
 }
 printf("Rezultat=%d \n", a);
}
}


