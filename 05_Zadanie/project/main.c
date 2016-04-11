#include <stdio.h>
#include <stdlib.h>
/* заголовочный файл для работы с динамическими библиотеками */
#include <dlfcn.h>
/* заголовочный файл для работы с opendir */
#include <dirent.h>
#include <string.h>
//Если вы хотите добавить свои библиотеки в папку plagins
//они должны называться lib***.so
int main(void)
{
    //Объявляем переменные
DIR *dir;
int i=0, ci=1;
 struct dirent *entry;
  double i1,i2;
   double (*myPlugin1_calFunc)(double a,double b);
    void *ext_library; // хандлер внешней библиотеки
     double ret;     // значение для теста
char library_name[20]="", *bibl=".so", *sravn, vvod[3]="", c;
char libr_nachalo[]="../plagins/lib";
char libr_konec[]=".so";
c=(char)(ci+'0');
while (1)
{
 switch(c)
 {
 case '1':
printf("Введите первое число ");
scanf("%lf",&i1);

printf("Введите второе число ");
scanf("%lf",&i2);
//Вывод содержимого каталога plaugins
  dir = opendir("../plagins");
  printf("Вы можете воспользоваться следующими функциями: \n");
    while ((entry = readdir(dir)) != NULL)
    {
        sravn=strstr(entry->d_name,bibl);
            if(sravn!=NULL)
            {
                for(i=3;i<6;i++)
                   printf("%c", entry->d_name[i]);//вывод названия функции

                    printf("\n");
            }
    }
    closedir(dir);

printf("Какой функцией вы хотите воспользоватся? \n");
    scanf("%9s", vvod);
        sprintf(library_name, "%s%s%s", libr_nachalo, vvod, libr_konec);
            //printf("%s\n", library_name);

ext_library = dlopen(library_name,RTLD_LAZY); //загрузка библиотеки
if (!ext_library)
    {
		//если ошибка, то вывести ее на экран
		fprintf(stderr,"dlopen() error: %s\n", dlerror());
		return 1;
	};
	//загружаем из библиотеки требуемую процедуру (в нашем случае она одна)
myPlugin1_calFunc=(double (*)(double a,double b))dlsym(ext_library,"calcFunc");
   if (myPlugin1_calFunc==NULL){
        fprintf(stderr,"dlsym error: not found symbol\n" );
        dlclose(ext_library);
        return 1;
    }
 ret=myPlugin1_calFunc(i1,i2);//вызываем функцию
    printf("answer:%f\n",ret);
	//закрываем библиотеку
	dlclose(ext_library);
 break;
 case '0': return 0;
 default : puts(" Error!");
 }
 puts(" 1 - продолжить ");
 puts(" 0 - выход");
 scanf("%d",&ci);
 c=(char)(ci+'0');
}
	return 0;
}
