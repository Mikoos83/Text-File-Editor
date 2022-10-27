#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "replace.h"

int main (int argc, char *argv[]){

	//this is for getcwd method and to print it on the screen for the user and the report later.
	//for the searching, "." is used.
	char cwd[PATH_MAX];

	if(getcwd(cwd, sizeof(cwd)) == NULL){

		perror("Failed to retrieve current directory path. Program will be closed...");
		exit(1);

	}
	else {
		strcat(cwd, "\0");
		printf("Current directory: %s\n", cwd);
	}
	
	//if user forgets to put the target string, program will be closed.
	if(argv[1] == NULL){
		perror("Target string was not provided. Program will be closed...");
		exit(1);

	}

	//count the number of files to check and report
	int total = walk_through_count(".");
	
	//report the number
	printf("There are total %d files to check\n", total);
	printf("----------------------------------------\n");
	
	//create an array for the file update information according to its number
	struct file_info* files = (struct file_info*)malloc(sizeof(struct file_info)*total);
	
	//search from the current directory
	walk_through(".", argv[1], files);

	//print the report - use cwd name for the sake of the report
	print_result(cwd, argv[1], files, total);	
	
	//free the memory allocated with malloc
	for(int i = 0; i < total; i++){
	
		free(files[i].file_name);
	}
	free(files);
	
	//closing message
	printf("\nThank you for using this program\n");


	return 0;
}
