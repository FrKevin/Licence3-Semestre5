#include <stdio.h>
#include <limits.h>

void prlimit(void) {
	printf("PATH_MAX : %i, NAME_MAX : %i\n",(int)PATH_MAX, (int)NAME_MAX);
}

int main(int argc, char*argv[]) {
	prlimit();
	return 0;
}
