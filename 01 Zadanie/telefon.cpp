#include <stdio.h>
#include <conio.h>
#include <string.h>
 
struct tov {char name[10]; float c; char kol[10];} t1;
void input(FILE *); // �������� ������ �����
void print(FILE *); // �������� �����
void app(FILE *); // ���������� � ����
void find(FILE *); // ����� � ���������
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
 tf=fopen("file1.dat","wb"); // �������� ��������� ����� ��� ������
 printf("\n New kontakt\n");
 do
 {printf("\n New kontakt\n"); 
  printf("\n Imya: "); scanf("%s",t1.name);
  printf("\n telefon: "); scanf("%f",&t1.c);
  printf(" Familiya: "); scanf("%s",t1.kol);
  fwrite(&t1,sizeof(t1),1,tf); // ������ � ���� ����� ��������� t1
  printf("\n Zakonchit? y/n ");
  ch=getch();
 }
while (ch != 'y');
 fclose(tf);
}
void print(FILE *tf)
{ int i;
 tf=fopen("file1.dat","rb"); // �������� ��������� ����� ��� ������
 i=1;
 fread(&t1,sizeof(t1),1,tf); // ������ �� ����� ����� ��������� t1
 while (!feof(tf))
 {printf("\n %3d Name %10s telefon %6.0f Familya %10s", i, t1.name, t1.c, t1.kol);
  fread(&t1,sizeof(t1),1,tf);
  i++;
 }
getch();
}
void app(FILE *tf)
{char ch;
 tf=fopen("file1.dat","ab"); // �������� ��������� ����� ��� ����������
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
 tf=fopen("file1.dat","rb+"); // �������� ��������� ����� ��� ������ � ������
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
       fseek(tf, -i, 1); // ������� �� sizeof(t1) ���� �����
      fwrite(&t1,sizeof(t1),1,tf);//������ ��������� ���������
     }
   }
fread(&t1,sizeof(t1),1,tf);
}
fclose(tf);
 
}