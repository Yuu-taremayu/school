#include <stdio.h>

int DFF[3] = {0, 0, 0};
int x[4] = {0, 0, 0, 0};

int XOR(int a, int b)
{
	return (a+b) % 2;
}

void circuit(int input)
{
	x[3] = DFF[2];
	DFF[2] = DFF[1];
	DFF[1] = XOR(DFF[0], x[3]);
	DFF[0] = XOR(input, x[3]);
}

int main(void)
{
	int IN[5] = {1, 0, 0, 1, 0};
	int t, k;

	for (t = 0; t < 5; t++) {
		circuit(IN[t]);
		printf("%d   ", IN[t]);
		for (k = 0; k < 3; k++) {
			printf("%d ", DFF[k]);
		}
		printf("  %d", x[3]);
		printf("\n");
	}
	printf("\n");

	return 0;
}
