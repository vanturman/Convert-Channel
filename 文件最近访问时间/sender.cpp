#include <sys/stat.h>  
#include <stdio.h>  
#include <stdlib.h>  

// senderChar function.
// send char-type message through reading char-numbers files.
// this is where reading char-number files really works.
void accessFiles(int count){
	FILE *fp;
	int i;
	char tab;
	char name_tag[30];
	// read char-number file to change their access time.
	for (i = 0; i < count; i++){
		sprintf(name_tag, "./tmp/%d.txt", i);
		if ((fp = fopen(name_tag, "r")) == NULL){
			printf("open %d.txt error.\n", i);
			exit(0);
		}
		tab = fgetc(fp);
		fclose(fp);
	}
}


int main(void){
	char ch;
	FILE *fp;
	// open sender.txt
	if ((fp = fopen("./sender.txt", "r")) == NULL){
		printf("open sender.txt error.\n");
		exit(0);
	}
	// read a high-security level file context to send.
	while ((ch = fgetc(fp)) != EOF){
		printf("Sending char '%c'.\n", ch);
		accessFiles((int)ch);
		sleep(2);
	}
	// it comes to an end when read every file of the directory.
	accessFiles(128); 
	fclose(fp);
	return 0;
}

