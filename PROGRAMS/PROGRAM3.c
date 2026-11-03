#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#define bs 3
#define n 10
pthread_mutex_t mtx;
pthread_cond_t notfull,notempty;
int count=0;
int in=0;
int out=0;
int b[bs];
void *camera(void *arg)
{ for(int i=0;i<n;i++)
        { int vc=10+rand()%90;
                pthread_mutex_lock(&mtx);
                while(count==bs)
                pthread_cond_wait(&notfull,&mtx);
                b[in]=vc;
                in=(in+1)%bs;
                printf("camera produced %d counts and buffer %d",vc,count+1);
                count++;
                pthread_cond_signal(&notempty);
                pthread_mutex_unlock(&mtx);
        usleep(50000);
        }
        return NULL;
}
void *analytics(void *arg)
{for(int i=0;i<n;i++){
pthread_mutex_lock(&mtx);
        while(count==0)
                pthread_cond_wait(&notempty,&mtx);


int v=b[out];
out=(out+1)%bs;
printf("analytics consumed % d buffer %d",v,count-1);
count--;
pthread_cond_signal(&notfull);
pthread_mutex_unlock(&mtx);
usleep(70000);
        }
        return NULL;
}
int main()
{
        pthread_t tcam,tanal;
        srand((unsigned int)time(NULL));
        pthread_mutex_init(&mtx,NULL);
        pthread_cond_init(&notfull,NULL);
        pthread_cond_init(&notempty,NULL);
        pthread_create(&tcam,NULL,camera,NULL);
        pthread_create(&tanal,NULL,analytics,NULL);
        pthread_join(tcam,NULL);
        pthread_join(tanal,NULL);

        pthread_mutex_destroy(&mtx);
        pthread_cond_destroy(&notfull);
        pthread_cond_destroy(&notempty);
        printf("ALL THREADS COMPLETD !!!!!!!!!!");
        return 0;
}
