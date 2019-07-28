#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "VectorC/vector.h"



static Vector commandQueue;

//Will return 0 if command is stored into the vector
//Will return 1 if Execute command was entered
int getCommand(void)
{
    //100 charecters will be the limit and default length to all commands
    char command[100];
    printf("Please Enter the name of a Program to Run.\n");
    scanf("%s", command);
    if(strcmp(command, "exec") == 0)
    {
        printf("Program Entry Ended. Starting programes...\n");
        return 1;
    }
    else
    {
        printf("You entered: %s\n", command);
        printf("Currently %d programes are scheduled to run.\n",(vector_total(&commandQueue) + 1));
        vector_add(&commandQueue, &command);
        return 0;
    }
}

void startProgrames(void)
{
        pid_t pid;
        //pid = fork ();

        if (pid == 0)
        {
            //Child proccess execute shell command process
            for(int i = 0; i < vector_total(&commandQueue); i++)
            {
                //Start Programmes
            }
        }
        else if (pid < 0)
        {
            printf("ERROR: Fork Procces Failed.\n");
        }
        else
        {
            //Parent Process
        }
}

int main(int argc, char** argv)
{
    int finished = 0;
    vector_init(&commandQueue);
    printf("###########\t");
    printf("Welcome To Program Runner");
    printf("\t###########\n");
    printf("Once you have entered all of the programes you would like to run, enter 'exec'.\n");

    while(finished != 1)
    {
        finished = getCommand();
    }

    startProgrames();

    vector_free(&commandQueue);
    return 0;
}