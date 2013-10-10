#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Сразу возникает вопролс, а вы запускали это приложение? Если да, то вас ничего не смутило?
int main(int argc, char *argv[], char *envp[])
{
	int i = 0;
	int j = 0; 
	while(i != argc ){
		// так как в argv[i] это указатель на массив char-ов то вам стоит выводить не один символ,
		// а сразу много символов, как то так, printf("%s" , argv[i]);
		printf("%c" , argv[i]);
		i++;
	}
	printf("%c" , "END");
	// и опять же так как envp[j] это не число, то почему вы сравниваете его с 0,
	// нулевой указатель выглядит так - NULL
	while(envp[ j ] != 0){
		// и опять же вместо симфола стоит выводить строку
		printf("%c" , envp[ j ]);
		j++;
	}

return 0;
}
