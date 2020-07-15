#include <stdio.h>

void my_str_link(char *s1, char *s2 , char *t)
{
	while (*s1 != '\0') *(t++) = *(s1++);
	while (*s2 != '\0') *(t++) = *(s2++);
	*(t++) = '\0';
}

int main(void)
{
	char s1[6 + 1] = "Hello,";
	char s2[5 + 1] = "World";
	char t[11 + 1];

	my_str_link(s1, s2, t);

	printf("t = %s\n", t);

	return 0;
}
