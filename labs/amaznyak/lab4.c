#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define EXTEND "Брошу ещё"
#define STOP "Последний бросок"

#define parent "Вася"
#define child "Петя"

/* ИГРА 21'
	Игра с помощью игральных костей.
	Игроки ходят по очереди и бросают кости.
	Цель игры что бы бросись кости несколько раз и получить в результате сумму 31.
	Если сумма очков больше 21' то ты проигрываешь. Игроки видят кол-во очков друг друга.
	Можно остановиться и не бросать кости. Выигрывает тот у кого сумма очков больше.
	2 процесса будут играть в эту игру.
*/
int main(int argc, char* argv[], char* env[]) {
	printf("\n Процессы играют в 21'. \n");
	
	srand(time(NULL));
	
	int fdp[2],fdc[2], p_id;
	size_t size;
	int i = 0;
	int chat = 1;
	
	int dice = 0;
	int dice1 = 1;
	
	char* msg_list[] = {EXTEND,
						STOP};
	char msg[64];
	
	if(pipe(fdc) < 0){
		printf("Can\'t Не получилось создать трубу :(\n");
		exit(-1); 
	} 
	if(pipe(fdp) < 0){
		printf("Can\'t Не получилось создать трубу :(\n");
		exit(-1); 
	} 
	printf("%s захотел позвать %s играть в 21 игральными костями \n", parent, child);
	p_id = fork(); 

	if(p_id < 0){ 
		printf("У %s не получилось позвать %s.\n", parent, child);
		exit(-1);
	}
	
	if (p_id > 0) {
		/*parent*/
		close(fdc[0]);
		close(fdp[1]);	
		int parent_count = 0;
		int extend = 0;
		
		while (chat > 0){
			
			
		
			size = write(fdc[1], msg_list[extend], 64);
			
			// Принимаю решение бросать кость в следующий ход ещё или нет
			if(rand()%2 == 1){
			printf("%s : %s \n", parent, EXTEND);
			extend = 0;
			} else {
			printf("%s : %s \n", parent , STOP);
			extend = 1;
			}
			
			while (size = read(fdp[0], msg, 64) < 0);
		
			printf( "%s мне сказал: %s\n" , child , msg );
			
			printf( "%s: Бросаю кость \n" , parent );
			dice1 = (rand()%6)+7;
			parent_count = parent_count + dice1;
			printf("%s: У меня выпало %d !\n", parent ,dice1 );
			
			if (strcmp(msg, msg_list[1]) == 0){
				chat = -1;
				printf("%s: Итого у меня %d очков", parent , parent_count);
				}
			i++;
		}
		
		close(fdc[1]);
		close(fdp[0]);
		printf("\n %s закрыл трубы \n", parent);
	} else {
		printf( "\n %s принял вызов %s \n" , child , parent );
		/*child*/
		close(fdc[1]);
		close(fdp[0]);
		
		int child_count = 0;
		int extend = 0;
		while (chat > 0){
			while (size = read(fdc[0], msg, 64) < 0);
			
			printf( "%s мне сказал: %s\n" , parent , msg );
			
			
			
			size = write(fdp[1], msg_list[extend], 64);
			
			if(rand()%2 == 1){
			printf("%s : %s \n", child, EXTEND);
			extend = 0;
			} else {
			printf("%s : %s \n", child , STOP);
			extend = 1;
			}
			
			printf( "%s: Бросаю кость \n" , child );
			dice = (rand()%6)+1;
			child_count = child_count + dice;
			printf("%s: У меня выпало %d !\n", child ,dice );
			
			if (strcmp(msg, msg_list[1]) == 0){
				chat = -1;
				printf("%s: Итого у меня %d очков", child,child_count);
				}
			i++;
		}
		
		close(fdp[1]);	
		close(fdc[0]);
		printf("\n %s закрыл трубы \n", child);
	}
	exit(0);
}
