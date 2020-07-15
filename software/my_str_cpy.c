#include <stdio.h>

void my_str_cpy(char *s, char *t)
{
	while (*s != '\0') {
		*(t++) = *(s++);
	}
	*(t++) = '\0';
}

int main(void)
{
	char s[5 + 1] = "Hello";
	char t[5 + 1];

	my_str_cpy(s, t);

	printf("t = %s\n", t);
	return 0;
}
