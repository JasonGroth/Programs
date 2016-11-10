#include <iostream>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string> 
#include <sys/wait.h>

using namespace std;

int main(int argument_count, char *argument_list[]){
	
	// There needs to be 2 arguments for the program to run.
	if (argument_count != 2){
		printf("Error: Incorrect input!\n");
    cerr << "Usage: " << argument_list[0] << " and a value for N" << endl;
    return 1;
	}
	
  int N = 0;
	// convert char N to a int N
		try{
			N = stoi(argument_list[1]);
		}
		catch(...){
			printf("Error: N is not an integer!\n");
      cerr << "Usage: " << argument_list[0] << " and a value for N" << endl;
      return 1;
		}
	
	// if N is a negative number
	if (stoi(argument_list[1]) <= 0){
		printf("Error: N is less than or equal to 0\n");
    cerr << "Usage: " << argument_list[0] << " and a value for N" << endl;
    return 1;
	}
	
	
  int child_count = 3;
	int* Child_PID = new int[child_count];
  int current_pid = 0;
	int Parent_PID = getpid();
	
  // creates 3 child/sub processes 
	for (int i = 0; i < child_count; i++){
		if ((current_pid = fork()) ==  0) {
			break;
    }
    Child_PID[i] = current_pid;
  }
	
  // Print out PID for Main and Child Procesess
	for(int i = 0; i < N; i++){
		if (current_pid ==  0) {
			 printf("Child Process PID = %d ", getpid());
			 printf("Parent Process PID = %d\n", Parent_PID);
    }
		else{
			printf("Main Process PID = %d\n", Parent_PID);
		}
    sleep(2); //Wait 2 seconds between the processes
	}
  
  // Let the process finish
  for (int i = 0; i < child_count; i++){ 
    waitpid(Child_PID[i], NULL, 0);
  }
	
}
