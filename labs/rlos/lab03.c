#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[], char* env[]) {
	printf("--------------------LAB3--------------------\n");
	printf("%d\n",argc);
	// на счет проблемы с тем что вызванная программа принимает лишние аргументы 
	// если вы посмотрите описание этой функции вы скорее всего увидете что то вроде
	// The last parameter must always be 0. It is a NULL terminator.
	// Since the argument list is variable we must have some way of telling C when it is to end.
	// The NULL terminator does this job.
	// Поэтому чтобы сказать что параметры закончились вызов execl в вашем случае должен выглядеть так
	// xecl(argv[1], argv[1], argv[0], 0); 
	execl(argv[1], argv[1], argv[0]); 
	printf("Ошибка передачи управления\n");
	// Так как следующие строки выполнятся только в случае неудачи смены контекста, 
	//кажется немного странным что вы завершаете программу с кодом правильного завершения приложения exit(0)
	printf("--------------------LAB3END--------------------\n");
	exit(0);
}

