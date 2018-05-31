#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// senderChar function.
// send char-type message through creating char-numbers thread.
void sendChar(char ch)
{
	pid_t fpid;
	int i;
	int count = (int)ch;
	printf("------------------------------------------\n");
	printf("Sending '%c' secretly, this character's pid count is '%d'.\n",ch,count);
	
	for (i = 0; i < count; i++) {
		fpid = fork();
		// when failed to create a new thread.
		if (fpid < 0) {
			printf("fork thread error!\n");
			exit(0);
		}
		else if (fpid == 0) {
			printf("Sending '%c', pid is '%d'.\n",ch, getpid());
			sleep(1);
			exit(0);
		}
	}

}


int main(void) 
{
	char ch;
	FILE *fp;
	int i;
	// open sender.txt.  
	if ((fp = fopen("./sender.txt", "r")) == NULL) {
		printf("open sender.txt error.\n");
		exit(0);
	}
	// send a char-type message every one seconds.
	while ((ch = fgetc(fp)) != EOF) {
		sendChar(ch);
		sleep(1);
	}
	// close senderText.
	fclose(fp);

	return 0;
}