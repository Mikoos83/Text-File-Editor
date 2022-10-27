#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "replace.h"

void print_result(const char*, const char*, struct file_info*, int);
static int compareTo(const void* a, const void* b);

//this void method creates a txt file and print the chaning result there. 
void print_result(const char* path_name, const char* target, struct file_info files[], int total){
	
	//open the FILE I/O
	FILE* fptr;
	fptr = fopen("report.txt", "w");
	if(fptr == NULL){
		
		fprintf(stderr, "%s", "Null pointer error, program ends...");
		exit(1);

	}

	//prints in the txt file
	fputs("Target string: ", fptr);
	fputs(target, fptr);
	fputs("\n", fptr);
	fputs("Search begins in current folder: ", fptr);
	fputs(path_name, fptr);
	fputs("\n\n**Search Report**\n", fptr);
	fputs("Update \t File Name\n", fptr);

	//sort the file information to be in descending order
	qsort(files, total, sizeof(struct file_info), compareTo);

	for(int i = total-1; i >=0; i--){

		fprintf(fptr, "%d", files[i].num_change);
		fputs("\t", fptr);
		// this part is to print the subdirectory and the file name only, not the entire path including the current directory
		
		char* short_name = files[i].file_name;
		for(int j = 2; j <strlen(files[i].file_name); j++){
			fprintf(fptr, "%c", short_name[j]);
		}
		fputs("\n", fptr);
	}
	//close the FILE I/O
	fclose(fptr);
}

//helping method for the quick sorting
static int compareTo(const void* a, const void* b){

	return (*(int*)a - *(int*)b);
}

