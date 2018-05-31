#include <sys/stat.h>  
#include <stdio.h>  
#include <stdlib.h>  

// set a flag named 'start' to judge meaasge transfer start or not.
int start = 0;

// create file function
// because ASCII code is range of 0 to 128, 
// so create 128 files to receive ASCII code.
void createFiles(){
	FILE *fp;
	char name_tag[30];
	int i;

	for (i = 0; i < 128; i++) {
		sprintf(name_tag, "./tmp/%d.txt", i);
		if ((fp = fopen(name_tag, "w+")) == NULL){
			printf("open error.\n");
			exit(0);
		}
		// all the file's context is 'a'.
		fputc('a', fp);
		fclose(fp);
	}
}

// receive one char every two second.
char receiveChar() {
	sleep(2);
	struct stat buf;
	int result;
	int old_time_int = -1;
	int time_int;
	char name_tag[30];
	char ch;
	int i;

	for (i = 0; i < 128; i++){
		sprintf(name_tag, "./tmp/%d.txt", i); //get file name to 'name_tag'
		result = stat(name_tag, &buf); // write file stat_info to 'buf'   

		if (result != 0)
			printf("get file %d's stat_info error.\n");

		else{
			time_int = buf.st_atime; // get file access time.  
			// judge the character that sender send.
			// find which file is the last read.
			if (old_time_int != -1 && old_time_int - time_int > 1)   {
				ch = (char)i;
				printf("Updated file: '%d', Receiving char: '%c'.\n", i, ch);
				start = 1;   
				return ch;
			}
			old_time_int = time_int;
		}
	}
	return '0';
}


// write a received character to receiver.txt
void writeToFile(char ch)  {
	FILE *fp;
	if ((fp = fopen("./receiver.txt", "a")) == NULL){
		printf("open receiver.txt error.\n");
		exit(0);
	}
	fputc(ch, fp);
	printf("Write '%c' to file yet.\n", ch);
	fclose(fp);
}


int main(void){
	char ch;
	remove("./receiver.txt"); // delete previous files content before receiving new files.
	createFiles(); // create files to receiving message.   
	// receive  message every one second.
	while (((ch = receiveChar()) != (char)0) || start == 0){ 
		if (start == 0)
			printf("Not start yet.\n");   
		else
			writeToFile(ch);  
	}
	printf("Transmission is finished.\n");
	return 0;
}

