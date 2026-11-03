#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#define shm_name "/OS_SHM_SIMPLE"
#define bs 100
int main()
{
        pid_t pid;
        int fd;
        char *shm;
        char temp[bs];
        fd=shm_open(shm_name,O_CREAT|O_RDWR,0666);
        if(fd==-1)
        {
                perror("shm open");
                exit(1);
        }
        ftruncate(fd,bs);
        shm=mmap(NULL,bs,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
        if(shm==MAP_FAILED)
        {
                perror("mmap");
                exit(1);
        }
        pid=fork();
        if(pid<0)
        {
                perror("fork");
                exit(1);
        }
        else
                if(pid==0)
                {
                        sprintf(shm,"Modified by child %s",shm);
                        printf("child :Modified msg %s\n",shm);
                        exit(0);
                }
                else
                {
                        strcpy(shm,"hello from parent");
                        printf("Parent :initial mesg=%s\n",shm);
                        wait(NULL);
                        printf("parent :final message %s\n",shm);
                }
        munmap(shm,bs);
        close(fd);
        shm_unlink(shm_name);
        return 0;
}

