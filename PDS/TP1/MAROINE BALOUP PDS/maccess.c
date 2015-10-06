#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char** argv) {
	char* mode; 
	char* file; 
	int res = 999;
	
	assert(argc == 3);
	
	mode = argv[1];
	file = argv[2];
	
	if(strcmp(mode, "-r") == 0) {
		res = access(file, R_OK);
	}
	
	else if(strcmp(mode, "-w") == 0) {
		res = access(file, W_OK);
	}
	else if(strcmp(mode, "-x") == 0) {
		res = access(file, X_OK);
	}
	else {
		printf("Argument non reconnu");
		return EXIT_FAILURE;
	}
	
	if(res == 0)
		printf("\n Autorisation accordée \n");
	else 
		printf("\n Autorisation refusée \n");
	
	return EXIT_SUCCESS;
}
