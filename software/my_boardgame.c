#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#define NAME_MAXNUM 255
#define ROULETTE_MAXNUM 4
#define OP_MAXNUM 3

typedef struct PLAYER
{
	char name[NAME_MAXNUM + 1];
	int roulette[ROULETTE_MAXNUM];
	char operand[OP_MAXNUM + 1];
	int *mynumber;
	int score;
} PLAYER;

PLAYER *init_player(PLAYER *p, int *num);
PLAYER *roulette(PLAYER *p, int turn, int seed);
PLAYER *decide_operand(PLAYER *p, int turn);
int decide_timeofgame(void);
void decide_modnum(void);
void show_info(PLAYER *p, int num);

int main(void)
{
	PLAYER *p = NULL;
	int num = 0;
	int turn = 0;
	int seed = 0;
	int time = 0;
	int i, j, k;

	p = init_player(p, &num);
	time = decide_timeofgame();
	turn = num;

	i = 0;
	while (time > i) {
		for (j = 0; j < ROULETTE_MAXNUM; j++) {
			for (k = 0; k < turn; k++) {
				p = roulette(p, k, seed);
			}
		}
		decide_modnum();
		for (j = 0; j < turn; j++) {
			p = decide_operand(p, j);
		}
		i++;
	}
	show_info(p, num);

	return 0;
}

/*	initialize players				*/
/*	decide number of player, each player name	*/
/*	other variables are initialized zero		*/
PLAYER *init_player(PLAYER *p, int *num)
{
	/* temporary variable */
	int temp;
	char s[256];
	/* variable for loop */
	int i, j;

	/* decide number of player and dynamic allocation */
	printf("Choose number of player(recommend:2-4):");
	scanf("%d", &temp);
	p = (PLAYER *)malloc(sizeof(PLAYER) * temp);
	*num = temp;

	/* decide player name */
	for (i = 0; i < *num; i++) {
		printf("%d player, tell me your name(MAX 255 characters):", i + 1);
		scanf("%s", s);
		for (j = 0; s[j] != '\0'; j++) {
			p[i].name[j] = s[j];
		}
		p[i].name[j + 1] = '\0';
	}

	/* initialize roulette array */
	for (i = 0; i < *num; i++) {
		for (j = 0; j < ROULETTE_MAXNUM; j++) {
			p[i].roulette[j] = 0;
		}
	}

	/* initialize operand array */
	for (i = 0; i < *num; i++) {
		for (j = 0; j < OP_MAXNUM; j++) {
			p[i].operand[j] = '0';
		}
		p[i].operand[OP_MAXNUM + 1] = '\0';
	}

	/* initialize mynumber */
	for (i = 0; i < *num; i++) {
		p[i].mynumber = NULL;
	}

	/* initialize score */
	for (i = 0; i < *num; i++) {
		p[i].score = 0;
	}

	return p;
}

/*	decide number of roulette 			*/
/*	each players decide number at their turn	*/
PLAYER *roulette(PLAYER *p, int turn, int seed)
{
	int i;

	srand(seed);

	for (i = 0; p[turn].roulette[i] != 0; i++) {
		usleep(300);
		p[turn].roulette[i] = (rand() % 10) + 1;
	}

	return p;
}

/*	decide operands		*/
PLAYER *decide_operand(PLAYER *p, int turn)
{
	int i;
	int item;
	char dummy;
	int comfirm = -1;
	int chara_flag = 0;

	/* print player's number */
	printf("your numbers are =>");
	for (i = 0; i < ROULETTE_MAXNUM; i++) printf(" %d", p[turn].roulette[i]);
	printf("\n");

	while (1) {
		for (i = 0; i < OP_MAXNUM; i++) {
			printf("choose your %d operand\n", i + 1);
			printf("1:+ 2:- 3:* 4:/ 5:%%\n");
			printf("please input your number:");
			scanf("%d%c", &item, &dummy);
			while (chara_flag != 1) {
				if (0 >= item && item <= 9) {
					chara_flag = 1;
				}
				else {
					scanf("%*[^\n]%*d");
					printf("you can use only number.\n");
					printf("please input your number:");
					scanf("%d%c", &item, &dummy);
					printf("%d\n", item);
				}
			}
			switch(item) {
				case 1:
					p[turn].operand[i] = '+';
					break;
				case 2:
					p[turn].operand[i] = '-';
					break;
				case 3:
					p[turn].operand[i] = '*';
					break;
				case 4:
					p[turn].operand[i] = '/';
					break;
				case 5:
					p[turn].operand[i] = '%';
					break;
				default:
					break;
			}
			printf("\n");
		}
		p[turn].operand[i + 1] = '\0';

		printf("is it ok?");
		printf("your choice =>");
		for (i = 0; i < OP_MAXNUM; i++)	printf(" %c", p[turn].operand[i]);
		printf("\n");
		printf("if you comfirmed, type 0:");
		scanf("%d", &comfirm);
		if (comfirm == 0) {
			break;
		}
	}
	return p;
}

/*	decide time of game	*/
int decide_timeofgame(void)
{
	int time = 0;

	printf("please input time of game(recommend:1-3):");
	scanf("%d", &time);
	printf("\n");

	return time;
}

void decide_modnum(void)
{
	int mod = 0;

	mod = (rand() % 10) + 1;
	printf("%d is modulo operation number\n", mod);
	printf("\n");
}

/*	show all player's infomation		*/
void show_info(PLAYER *p, int num)
{
	int i, j;

	for (i = 0; i < num; i++) {
		printf("\n");
		printf("---%d player---\n", i + 1);

		printf("name:%s\n", p[i].name);

		printf("roulette numbers:");
		for (j = 0; j < ROULETTE_MAXNUM; j++) {
			if (p[i].roulette[j] == 0) break;
			printf("%d ", p[i].roulette[j]);
		}
		printf("\n");

		printf("operands:");
		for (j = 0; j < OP_MAXNUM; j++) {
			if (p[i].operand[j] == '0') break;
			printf("%c ", p[i].operand[j]);
		}
		printf("\n");

		printf("score:%d\n", p[i].score);
	}
	printf("\n");
}
