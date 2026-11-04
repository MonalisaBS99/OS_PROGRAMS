
#include<stdio.h>
int main()
{
int n;
printf("=================================welcome==============================\n");
printf("enter number of orders:\n");
scanf("%d",&n);
int bursttime[n];
int waitingtime[n];
int turnaroundtime[n];
for(int i=0;i<n;i++)
{
printf("enter processing time for order %d\n",i+1);
scanf("%d",&bursttime[i]);
}
waitingtime[0]=0;
for(int i=1;i<n;i++)
{
waitingtime[i]=waitingtime[i-1]+bursttime[i-1];
}
for(int i=0;i<n;i++)
turnaroundtime[i]=waitingtime[i]+bursttime[i];
int sum1=0;
int sum2=0;
for(int i=0;i<n;i++){
sum1+=waitingtime[i];
sum2+=turnaroundtime[i];}
float avgw=(float)sum1/n;
float avgt=(float)sum2/n;
printf("\n \t%s\t%s\t%s\t%s\n","orders","bursttime","waitingtime","turnaroundtime");
for(int i=0;i<n;i++)
{
printf("\n \t%d\t%d\t%d\t%d\n",i+1,bursttime[i],waitingtime[i],turnaroundtime[i]);
}
return 0;
}
