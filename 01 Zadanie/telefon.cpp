#include <stdio.h>
#include <conio.h>
#include <string.h>
 
struct tov {char name[10]; float c; char kol[10];} t1;
void input(FILE *); // создание нового файла
void print(FILE *); // просмотр файла
void app(FILE *); // добавление в файл
void find(FILE *); // поиск и изменение
int main()
{ char c;
FILE *tf;
while (1)
{
 puts(" 1 - new file");
 puts(" 2 - view file");
 puts(" 3 - dobavit");
 puts(" 4 - search");
 puts(" 0 - exit");
 c=getch();
 switch(c)
 { case '1':input(tf);break;
  case '2':print(tf);break;
  case '3':app(tf);break;
  case '4':find(tf);break;
  case '0':return 0;
  default : puts(" Error!");
 }
}
}
void input(FILE *tf)
{char ch;
 tf=fopen("file1.dat","wb"); // открытие бинарного файла для записи
 printf("\n New kontakt\n");
 do
 {printf("\n New kontakt\n"); 
  printf("\n Imya: "); scanf("%s",t1.name);
  printf("\n telefon: "); scanf("%f",&t1.c);
  printf(" Familiya: "); scanf("%s",t1.kol);
  fwrite(&t1,sizeof(t1),1,tf); // запись в файл одной структуры t1
  printf("\n Zakonchit? y/n ");
  ch=getch();
 }
while (ch != 'y');
 fclose(tf);
}
void print(FILE *tf)
{ int i;
 tf=fopen("file1.dat","rb"); // открытие бинарного файла для чтения
 i=1;
 fread(&t1,sizeof(t1),1,tf); // чтение из файла одной структуры t1
 while (!feof(tf))
 {printf("\n %3d Name %10s telefon %6.0f Familya %10s", i, t1.name, t1.c, t1.kol);
  fread(&t1,sizeof(t1),1,tf);
  i++;
 }
getch();
}
void app(FILE *tf)
{char ch;
 tf=fopen("file1.dat","ab"); // открытие бинарного файла для добавления
 printf("\n New kontakt \n");
 do
 { printf("\n Name: "); scanf("%s", t1.name);
  printf(" telefon: "); scanf("%f",&t1.c);
  printf(" Familiya: "); scanf("%s",t1.kol);
  fwrite(&t1,sizeof(t1),1,tf);
  printf(" Zakonchit? y/n ");
  ch=getch();
 }
while (ch != 'y');
 fclose(tf);
}
void find(FILE *tf)
{char c, tov[10];
 long int i;
 tf=fopen("file1.dat","rb+"); // открытие бинарного файла для чтения и записи
 puts(" Name kontakta ");
 gets(tov);
 fread(&t1,sizeof(t1),1,tf);
 while (!feof(tf))
 {if (strcmp(t1.name,tov)==0)
  {printf(" Name %10s telefon %6.2f Familiya %s",t1.name,t1.c,t1.kol);
   printf("\n Izmenit? y/n ");
   c=getch();
   if (c=='y')
     { printf("\n Familiya: "); scanf("%s",t1.kol);
       printf("\n telefon: "); scanf("%f",&t1.c);
       i=sizeof(t1);
       fseek(tf, -i, 1); // возврат на sizeof(t1) байт назад
      fwrite(&t1,sizeof(t1),1,tf);//запись изменённой структуры
     }
   }
fread(&t1,sizeof(t1),1,tf);
}
fclose(tf);
 
}