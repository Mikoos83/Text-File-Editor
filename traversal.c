#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include "replace.h"

void walk_through(const char*, const char*, struct file_info*); 
int walk_through_count(const char*);
static char* subdir_name_maker(const char*, const char*);

//constant count: used to count how many files are there. Returned by walk_through_count
static int count = 0;
//constant tag: used to track the array of struct file_info
static int tag = 0;

void walk_through(const char* path_name, const char* target, struct file_info files[]){

	DIR* d;
	struct dirent* dir;
	d = opendir(path_name);

	if(d){
		while((dir = readdir(d)) != NULL){
			if(dir->d_type!=DT_DIR && strcmp(dir->d_name, "a.out") != 0){
				
				printf("\nThis is a file.\n");
				files[tag] = change_text(subdir_name_maker(path_name, dir->d_name), target);
				tag++;
			}//end of if
			else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..") != 0){
				printf("This is subdirectory: %s\n",dir->d_name);
				printf("Opening directory..\n\n");
				walk_through(subdir_name_maker(path_name, dir->d_name),target, files);
				printf("Going out of subdirectory..\n\n");
				continue;
			}//end of else

		}//end of while

	}//end of if
	closedir(d);
}//end of walk_through

// this method is used to count how many files are there to be checked. Returned int will be used for memory allocation
int walk_through_count(const char* path_name){

	DIR *d;
	struct dirent *dir;
	d = opendir(path_name);

	if(d){
		while ((dir = readdir(d)) != NULL){

			if(dir->d_type!=DT_DIR && strcmp(dir->d_name, "a.out") !=0){
				printf("%s\n", dir->d_name);	
				count++;

			}//end of if

			else if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0){

				walk_through_count(subdir_name_maker(path_name, dir->d_name));

			}//end of else if

		}//end of while

	}//end of if
	
	closedir(d);
	return count;
}

//helping method to create subdirectory path name
static char* subdir_name_maker(const char* path_name, const char* dir_name){

	char* subdir_name = (char *)malloc(strlen(path_name)+strlen(dir_name)+2);
	strcpy(subdir_name, path_name);
	strcat(subdir_name, "/");
	strcat(subdir_name, dir_name);
	strcat(subdir_name, "\0");
	return subdir_name;

}
