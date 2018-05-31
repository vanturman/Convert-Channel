#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int start = 0;

// wirte a received character to receiver.txt.
void writeToFile(char ch) {
	FILE *fp;
	if ((fp = fopen("./receiver.txt", "a")) == NULL) {
		printf("open receiver.txt error.\n");
		exit(0);
	}
	fputc(ch, fp);
	printf("Write '%c' to receiver.txt yet.\n", ch);
	fclose(fp);
}

// receive a char-type message every two seconds.
char receiveChar() {
	pid_t fpid1, fpid2;		//fpid1, fpid2 is the return number of fork() function.
	int diff;
	int ch;

	printf("------------------------------------------\n");
	printf("Listening ...\n");
	fpid1 = fork();
	if (fpid1 < 0) {
		printf("fork thread error!\n");
	}
	else if (fpid1 == 0) {
		exit(0);
	}
	sleep(1);

	fpid2 = fork();
	if (fpid2 < 0) {
		printf("fork thread error!\n");
	}
	else if (fpid2 == 0) {
		exit(0);
	}
	diff = fpid2 - fpid1 - 1;		//count the difference between two numbers.
	ch = (char) diff;
	if (diff < 63) {
		printf("Receiving ends.\n");
		printf("pid_difference is '%d', data is '%c'.\n",diff, ch);
		return '0';
	}
	else {
		// the sender is a thread. So minus difference & 'ch'
		if (start == 0) {
			diff--;
			ch--;
		}
		printf("Receiving ends.\n");
		printf("pid_difference is '%d', data is '%c'.\n", diff, ch);
		start = 1;
		return ch;
	}
}

int main(void) 
{
	char ch;
	int i;
	//clear previous file content before receiving new file.
	remove("./receiver.txt");
	while ((ch = receiveChar()) != (char) 0 || start == 0) {
		if (start == 0) {
			printf("Not start yet.\n");
		}
		else {
			writeToFile(ch);
		}
	}
	printf("Transmission is finished.\n");
	return 0;
}