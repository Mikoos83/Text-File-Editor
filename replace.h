#ifndef REPLACE_H_
#define REPLACE_H_

//this structure is to keep the updated information about the each file. It has integer and string, which is number of change and the file name respectively
struct file_info {
	
	int num_change;
	char* file_name;

};

//this is to go through the each file and subdirectory. It is from traversal.c
void walk_through(const char*, const char*, struct file_info*);

// this is to count the number of files. It is from traversal.c
int walk_through_count(const char*);

//this is to update the original file and record the updated information. It is from text.c
struct file_info change_text(const char*, const char*);

//this is to print the report in different text file. It is from report.c
void print_result(const char*, const char*, struct file_info*, int);

#endif
