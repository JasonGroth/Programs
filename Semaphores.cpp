#include <iostream>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string> 
#include <sys/wait.h>

using namespace std;

// function for the three child processes to run their commands
void childprocesses(int process, string filename){
  if(process == 0){
    execl("/bin/ls","ls","-l", NULL); // Run the ls -l command
  }
  else if(process == 1){
    execl("/bin/ps", "ps", "-ef", NULL); // Run the ps -ef command
  }
  else if(process == 2){
    execl("/bin/cat","cat", filename.c_str(), NULL); // Display content from users file
  }
}

// Main function
int main(int argument_count, char *argument_list[]){
	
	// There needs to be 2 arguments for the program to run.
	if (argument_count != 2){
		printf("Error: Incorrect input!\n");
    cerr << "Usage: " << argument_list[0] << " and a text file" << endl;
    return 1;
	}

  // Variables
  string filename = argument_list[1];
  int child_count = 3;
	int* Child_PID = new int[child_count];
  int current_pid = 0;
	int Parent_PID = getpid();
	
  // Print Part PID
  printf("****************************************\n");
  printf("Parent Process PID = %d\n", Parent_PID);
  printf("****************************************\n");

  // Creates 3 child/sub processes 
	for (int i = 0; i < child_count; i++){
    
    // Print out which process is coming out
    printf("---------------------\n");
    printf("| Child Process {%d} |\n", i + 1);
    printf("---------------------\n");

		if ((current_pid = fork()) ==  0) {
      childprocesses(i, filename);
			break;
    }
    waitpid(Child_PID[i], NULL, 0); // waiting for a process to finish before the next
  }
  
	printf("****************************************\n");
  printf("The Parent Process has finished\n");
  printf("****************************************\n");
}
