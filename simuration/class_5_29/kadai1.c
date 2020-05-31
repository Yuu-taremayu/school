#include <stdio.h>

int main(void){
	
	double x = 0.0;
    
	while (1) {
		if (x == 1.0)
			break;
		x += 0.1;
        	printf("x = %lf\n", x);
	}
	printf("Done!\n");
	return 0;
}
