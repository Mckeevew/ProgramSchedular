#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "vector.h"




//Will return 0 if command is stored into the vector
//Will return 1 if Execute command was entered
int getCommand(Vector* commandQueue)
{
    //100 charecters will be the limit and default length to all commands

    char* command = malloc(sizeof(char) * 100);
    printf("Please Enter the name of a Program to Run.\n\n");


    int ch,i=0;
    while((ch=fgetc(stdin))!='\n'){
    	command[i++]=ch;
    }


	printf("Entered");
    if(strcmp(command, "execute") == 0)
    {
        printf("Program Entry Ended. Starting programs...\n");
        return 1;
    }
    else
    {
        printf("You entered: %s\n\n", command);
        printf("Currently %d programs are scheduled to run.\n\n",(vector_total(commandQueue) + 1));
        vector_add(commandQueue, command);
        return 0;
    }
}

void startProgrames(Vector* commandQueue)
{
	//array of exit codes
	int* exitArr=malloc(vector_total(commandQueue) * sizeof(int));
	//array of pids
	pid_t* taskArr=malloc(vector_total(commandQueue) * sizeof(pid_t));
	//array of program complete times
	double* timeArr=malloc(vector_total(commandQueue) * sizeof(double));
	clock_t startTime;//program start time
	clock_t endTime;//program end time
	double totalTime=0;//difference between start and end times
	double finalTime = 0;//the time it took to run all programs
    int exitStatus;//exit status of child program
	//char* arg[] ={NULL};//arguments for program
	pid_t pid2;//PID of the child process
	for(int i = 0; i < vector_total(commandQueue); i++)
	{
		//done so that program runtim won't count command parsing
		char* command = vector_get(commandQueue,i);
		//size of variables may chamge, may want to malloc some of this
		//make sure the last input into argv is NULL
		char* ptr = strtok(command, " ");
		char* argv[100];
		int commBuild = 0;
		while(ptr != NULL)
		{
			argv[commBuild++] = ptr;
			ptr = strtok(NULL," ");
		}
		argv[commBuild] = NULL;

		pid_t pid;
		pid = fork();//duplicate

		//parent code
		//The parents is responsible for recording times
		if(pid >0)
		{
			startTime = clock();
			//can we get exit codes like this?
			pid2=wait(&exitStatus);
			endTime = clock();
			totalTime =(double)(((endTime-startTime)/CLOCKS_PER_SEC)*1000);
			if(WIFEXITED(exitStatus))
			{
				exitArr[i]=WEXITSTATUS(exitStatus);
			}
			taskArr[i]=pid2;//record PID
			timeArr[i]=totalTime;//record program run time
		}
		//child code
		//The child is responsible for executing command processes
		else if(pid == 0)
		{
			//is there a list of arguments we are supposed to provide
			//exec() only returns on fail
			//exitStatus = execvp(vector_get(&commandQueue,i),arg);

			//command builder looping index variable
			printf("EXECUTING:");
			for(int j = 0; j < commBuild; j++)
			{
				printf(" %s", argv[j]);
			}
			printf("\n");

			exitStatus = execvp( argv[0], argv);
			printf("Exit Status: %d\n",exitStatus);
			perror("ERROR: ");
			//we need to print the command names at the end, when reporting run times/exit codes
			//so, we should not delete command queue
			vector_delete(commandQueue, i);
			exit(exitStatus);//I think this should return exit status to master
		}
		//fork fail code
		else
		{
			//failed fork.
			exitArr[i]=-1;
			taskArr[i]=-1;//having the exitArr and taskArr be equivalent indicates fork fail
			timeArr[i]=0;//record time/fail
		}
	}
	if(vector_total(commandQueue)>0)
	{
		for(int i = 0; i < vector_total(commandQueue); i++)
		{
			//print id
			if(taskArr[i]==-1)
			{
				//print faineld command name
				printf("Could not start program-fork failure\n.");
			}
			else
			{
				//need to convert time to measureable units
				finalTime += timeArr[i];
				printf("pid: %d\truntime: %lf ms\texit status: %d\n",taskArr[i],timeArr[i],exitArr[i]);
			}
		}
		printf("Final run time: %lf ms\n",finalTime);
	}
	else
	{
		printf("No programs were scheduled to run.\n");
	}
	free(exitArr);
	free(taskArr);
	free(timeArr);
}

int main(int argc, char** argv)
{
	Vector commandQueue;
    int finished = 0;
    vector_init(&commandQueue);
    printf("###########\t");
    printf("Welcome To Program Runner");
    printf("\t###########\n\n");
    printf("Once you have entered all of the programs you would like to run, enter 'execute'.\n");

    while(finished != 1)
    {
        finished = getCommand(&commandQueue);
    }

	printf("###########\t");
    printf("Running Your Programes");
    printf("\t###########\n\n");

    startProgrames(&commandQueue);

    vector_free(&commandQueue);
    return 0;
}
