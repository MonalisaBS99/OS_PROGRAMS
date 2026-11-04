#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main()
{
int jobs=5;
pid_t pid;
printf("\n ===============Parent id %d:============\n",getpid());
for(int i=0;i<jobs;i++){
pid=fork();
if(pid<0)
{
perror("fork failed");
exit(0);
}
else
if(pid==0)
{
printf("========child image processing ............========\n");
printf("child ID %d paret id %d\n",getpid(),getppid());
sleep(2);
printf("==============child image processing completed============\n");
exit(0);
}
else
{
printf("Parent ID "%d",getpid());
}
}
printf("========\n parent waiting..................\n");

for(int i=0;i<jobs;i++)
wait(NULL);
printf("==========parent :ALL process completed==========\n");
return 0;
}
