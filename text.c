#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "replace.h"

struct file_info change_text (const char*, const char*);

//this method returns the updated information about the each file
struct file_info change_text (const char* path_name, const char* target){

	//create file structure to record the number of change and the file name
	struct file_info f ={.num_change = 0, .file_name = (char* ) malloc(strlen(path_name)+1)};	
	strcpy(f.file_name, path_name);
	strcat(f.file_name, "\0");
	printf("%s\n", f.file_name);

	//open FILE I/O
	FILE* fptr;
	fptr = fopen(path_name, "r");

	//exception handling
	if(fptr == NULL){
		perror("Error! Program will be closed...");
		exit(1);
	}

	//print the original contents and count the number of chars for the memory allocation
	int c = getc(fptr);
	int letter = 0;

	while (c!=EOF){
		letter++;
		c = getc(fptr);
	}
	printf("\n----------------------------------------\n");

	//close the file temporarily
	fclose(fptr);

	//dynamic memory allocation to read and hold the file input
	char* buff = (char *)malloc((letter*sizeof(char))+1);

	//open the file again and read the chars in
	fptr = fopen(path_name, "r");

	int index = 0;
	c = getc(fptr);
	while (c != EOF){
		buff[index] = putchar(c);
		index++;
		c = getc(fptr);
	}
	buff[letter] = '\0'; 
	
	//create another memory same size as the buff for the chars manipulation
	char* copy = (char *)malloc(strlen(buff)+1);

	for (int i = 0; i < strlen(buff);){

		//if the first letter is not the same, just copy the lower case letter and continue
		if(tolower(buff[i]) !=tolower(target[0])){
			copy[i] = buff[i];
			i++;
			continue;
		}
		else{
			//if the first letter is the same, take the substring and compare with target
			char subbuff [strlen(target)+1];
			memcpy (subbuff, &buff[i], strlen(target));
			subbuff[strlen(target)] = '\0';

			for(int i = 0; i < strlen(subbuff); i++){
				subbuff[i] = tolower(subbuff[i]);
			}

			//if the substring and the copy is same, assign Upper case letter in the copy memory
			if (strcmp(subbuff, target) == 0){
				
				for(int j = 0 ; j <strlen(target); j++){
			
					copy[i] = toupper(subbuff[j]);
					i++;
				}
			//update the number of change
			f.num_change++;		
			}
			else{
					copy[i] = buff[i];
					i++;
			}

		}
	}

	//close the copy array with '\0' and print the new string
	copy[strlen(buff)] = '\0';
	printf("\n----------------------------------------\n");
	printf("NEW TEXT:\n%s\n", copy);
	printf("----------------------------------------\n\n");

	//close FILE I/O temporarily
	fclose(fptr);

	//open FILE I/O to write the file
	fptr = fopen(path_name, "w");
	fputs(copy, fptr);
	
	//free the allocated memory
	free(buff);
	free(copy);
	
	//close the FILE I/O and return the struct
	fclose(fptr);
	return f;
	
}//end of method
