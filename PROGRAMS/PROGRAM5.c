#include <stdio.h>
#include <stdlib.h>

# define n 5
# define thinking 0
#define hungry 1
#define eating 2
int state[n];
void test(int i)
{
    int l=(i+n-1)%n;
    int r=(i+1)%n;
    if(state[i]==thinking&&state[l]!=eating&&state[r]!=eating)
    {
        state[i]=eating;
    }
}
void pickup(int i)
{
    state[i]=hungry;
    printf("\n philosopher is hungry");
    test(i);
    if(state[i]==eating)
    {
        printf("\n philosopher is eating");
    }
    else
        printf("\n philospher is waiting");
}
void putdown(int i)
{
    state[i]=thinking;
    printf("\n philosopher is thinking ");
    test((i+n-1)%n);
    test((i+1)%n);
}

int main()
{
    for(int i=0;i<n;i++)
    {
        state[i]=thinking;
    }
    printf("\n initial: all philosopher are thinking");
    for(int j=1;j<=2;j++)
    {
        printf("\n=======CYCLE %d======",j);
        for(int i=0;i<n;i++)
        {
            pickup(i);
            if(state[i]==eating)
            {
                putdown(i);
            }
        }
    }
    printf("=========FINISHED========");
    return 0;
}

