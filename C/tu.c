#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char tape[1024];
char* machine[1024];
int machineMax = 1;
int machineIndex = 0;

int runState(char* state,int cur);
char** split(char* in,const char* delim);
void printTape();
void runMachine();

int main(int argCount, char** argVal)
{
	//read turing file
	FILE* f = fopen(argVal[1],"r");
	strcpy(tape,argVal[2]);

	size_t buffSize = 64;
	char* lineBuff = malloc(buffSize * sizeof(char));

	machine[0] = "not a state";

	while(fgets(lineBuff,buffSize,f)){
		machine[machineMax] = malloc(buffSize * sizeof(char));
		strcpy(machine[machineMax],lineBuff);
		machineMax++;
	}

	printf("Initial Tape : %s\n", tape);

	runMachine();

	printf("Final Tape : %s\n", tape);

	fclose(f);
	free(lineBuff);

}

int runState(char* state,int cur){

	if(strcmp(state,"halt!") == 0) return 0;

	char* buff = malloc(64 * sizeof(char));
	strcpy(buff,state);
	char* tok = strtok(buff,":");

	if(strcmp(tok,"right") == 0){
		machineIndex++;
	}else if(strcmp(tok,"left") == 0){
		machineIndex--;
		if(machineIndex < 0) {
			free(buff);
			return -1;
		}
	}

	tok = strtok(NULL,":");	
	tok = strtok(tok," ");
	while(tok){
		if(tok[0] == tape[machineIndex]){
			tape[machineIndex] = strtok(NULL," ")[0];
			free(buff);
			return atoi(strtok(NULL," "));
		}else{
			tok = strtok(NULL," ");						
			while(tok && strcmp(tok,"|") != 0){
				tok = strtok(NULL," ");
			}
			tok = strtok(NULL," ");

		}
	}
	
	free(buff);
	return cur;

}

void runMachine(){
	int nextState = 1;
	while(nextState > 0 && machineIndex < 1024){
		nextState = runState(machine[nextState],nextState);
	}
}