#include <stdio.h>
#include <stdlib.h>

struct state
{

	

}

int main(int argCount, char** argVal)
{

	char tape[1024];
	int inputIndex, machineIndex = 0;

	FILE* f = fopen(argVal[1],"r");

	size_t buffSize = 64;
	char* lineBuff = (char *)malloc(buffSize * sizeof(char));

	while(fgets(lineBuff,buffSize,f)){
		printf("%s", lineBuff);
	}
	
	fclose(f);
	free(lineBuff);

}