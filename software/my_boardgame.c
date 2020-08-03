#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
void show_info(PLAYER *p, int num);

int main(void)
{
	PLAYER *p = NULL;
	int num = 0;
	int turn = 0;
	int seed = 0;

	p = init_player(p, &num);
	p = roulette(p, turn, seed);
	p = decide_operand(p, turn);
	show_info(p, num);

	return 0;
}

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

PLAYER *roulette(PLAYER *p, int turn, int seed)
{
	int i;

	srand(seed);

	for (i = 0; p[turn].roulette[i] != 0; i++);
	p[turn].roulette[i] = (rand() % 10) + 1;

	return p;
}

PLAYER *decide_operand(PLAYER *p, int turn)
{
	int i;
	int item = -1;
	int comfirm = -1;

	for (i = 0; p[turn].operand[i] != '0'; i++);

	printf("choose your %d operand\n", i);
	printf("1:+ 2:- 3:* 4:/ 5:%%\n");

	while (1) {
		printf("please input your number:");
		scanf("%d", &item);
		switch(item) {
			default:
				break;
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
		}
		printf("is it ok?");
		printf("your choice => %c\n", p[turn].operand[i]);
		printf("if you comfirmed, type 0:");
		scanf("%d", &comfirm);
		if (comfirm == 0) {
			break;
		}
	}
	return p;
}


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
