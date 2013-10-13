#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

	int fd; 
	size_t size;
	char string[] = "Hello, world!";
	char resstring[14]; 
	/* Обнуляем маску создания файлов текущего процесса для того, чтобы
	права доступа у создаваемого файла точно соотвествовали параметру вызова open() */

	(void)umask(0); 

	/* Попытаемся открыть файл с именем myfile в текущей директории только
	для операций вывода. Если файл не существует, попробуем его создать с правами 
	доступа 0666, т.  е. read-write для всех категорий пользователей */

	if((fd = open("myfile", O_WRONLY | O_CREAT, 0666)) < 0){

		/* Если файл открыть не удалось, печатаем об этом сообщение и прекращаем работу */

		printf("Can\'t open file\n");
		exit(-1); 
	} 

	/* Пробуем записать в файл 14 байт из нашего массива, т.е. всю строку "Hello, world!" 
	вместе с признаком конца строки */

	size = write(fd, string, 14);
	
	if(size != 14){

		/* Если записалось меньшее количество байт, сообщаем об ошибке */

		printf("Can\'t write all string\n"); 
		exit(-1); 
	} 
	
	size = read(fd, resstring, 14);
	
	if(size < 0){

		/* Если прочитать не смогли, сообщаем об ошибке */

		printf("Can\'t read string\n"); 
		exit(-1); 
	} 

	/* Печатаем прочитанную строку */

	printf("%s\n",resstring);
	/* Закрываем файл */

	if(close(fd) < 0){ 
		printf("Can\'t close file\n");
	}

	return 0;
}