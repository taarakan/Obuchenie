#include <stdio.h>
#include <stdlib.h>
/* заголовочный файл для работы с динамическими библиотеками */
#include <dlfcn.h>
int main(void)
{
double i1,i2;
double (*myPlugin1_calFunc)(double a,double b);
void *ext_library; // хандлер внешней библиотеки
double ret;     // значение для теста
printf("pervoe chislo ");
scanf("%lf",&i1);

printf("vtoroe chislo ");
scanf("%lf",&i2);


ext_library = dlopen("../plagins/libadd.so",RTLD_LAZY); //загрузка библиотеки
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
	return 0;
}
