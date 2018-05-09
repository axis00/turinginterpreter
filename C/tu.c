#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tape[1024] = "#aaaa#~";
char* machine[1024];
int machineMax = 1;
int machineIndex = 0;

int runState(char* state);
char** split(char* in,const char* delim);
void printTape();
void runMachine();

int main(int argCount, char** argVal)
{
	//read turing file
	FILE* f = fopen(argVal[1],"r");

	size_t buffSize = 64;
	char* lineBuff = malloc(buffSize * sizeof(char));

	machine[0] = "not a state";

	while(fgets(lineBuff,buffSize,f)){
		machine[machineMax] = malloc(buffSize * sizeof(char));
		strcpy(machine[machineMax],lineBuff);
		machineMax++;
	}

	printf("%c\n", tape[0]);

	printf("Initial Tape : %s\n", tape);

	runMachine();

	printf("Final Tape : %s\n", tape);

	fclose(f);
	free(lineBuff);

}

int runState(char* state){

	if(strcmp(state,"halt!") == 0) return 0;

	char* tok = strtok(state,":");

	if(strcmp(tok,"right") == 0){
		machineIndex++;
	}else if(strcmp(tok,"left") == 0){
		machineIndex--;
		if(machineIndex < 0) return -1;
	}

	tok = strtok(NULL,":");
	tok = strtok(tok," ");
	printf("%s\n", tok);
	if(tok) printf("%s\n", "TOOOOOOK");
	while(tok){
		if(tok[0] == tape[machineIndex]){
			tape[machineIndex] = strtok(NULL," ")[0];
			return atoi(strtok(NULL," "));
		}else{
			tok = strtok(NULL," ");
			while(strcmp(tok,"|") != 0 && tok){
				tok = strtok(NULL," ");
			}
			tok = strtok(NULL," ");
		}
	}
	
	return machineIndex;

}

void printTape(){
	char cell;
	int counter = 0;
	do{
		cell = tape[counter];
		printf("%c", cell);
		counter++;
	}while(cell == '~');
	printf("\n");
}

void runMachine(){
	int nextState = 1;
	while(nextState > 0){
		printf("%d\n", nextState);
		nextState = runState(machine[nextState]);
	}
}