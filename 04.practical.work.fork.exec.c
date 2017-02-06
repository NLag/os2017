#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int childprocess(char *file,char *args[]) {
	pid_t pid = fork();
	if (pid == 0)
	{
		printf("Child Process: \n");
		execvp(file,args);
	}
	return pid;
}

int main() {
	printf("Main parent process\n");

	char *args1[] = {"ps", "-ef", NULL };
	waitpid(childprocess("ps",args1),NULL,0);

	char *args2[] = {"free", "-h", NULL };
	waitpid(childprocess("free",args2),NULL,0);

	return 0;
}		