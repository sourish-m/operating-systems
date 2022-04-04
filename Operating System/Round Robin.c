#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
void line(int);

struct PCB
{
	int p, at, bt, pr, wt, ta, rt;
}a[10], t;

void main()
{ 
	int i, j, c=0, idle=0, n, con_swt[20], d=0, quant, comp=0, flag=0;
	float WTsum=0, TAsum=0, WTavg, TAavg, util_time=0, util_perc;
	char cswt_idle[40];
//	clrscr();
	
	do
	{
		printf("\n Enter number of processes: ");
		scanf("%d", &n);
		
		if(n<1)
		{
			system("cls");
			printf("\n Number of processes must be > 0");
		}
	}while(n<1);
	
	printf("\n Enter Arrival time, Burst time and Priority for processes:\n");
	
	for(i=0;i<n;i++)
	{
		a[i].p=i;
		printf("\n Process %d", i);
		line(11);
		printf(" AT[%d] = ", i);
		scanf("%d", &a[i].at);
		printf(" BT[%d] = ", i);
		scanf("%d", &a[i].bt);
		printf(" PR[%d] = ", i);
		scanf("%d", &a[i].pr);
		util_time+=a[i].bt;
		a[i].rt=a[i].bt;
		printf("\n");
	}
	printf(" Enter time quantum: ");
	scanf("%d", &quant);
	
	system("cls");
	printf("\n --------- Round Robin Scheduling ---------\n");
	printf("\n Input: (Lower the num, higher the priority)");
	line(48);
	printf(" Process   Arrival time   Burst Time   Priority");
	line(48);
	for(i=0;i<n;i++)
	{
		printf(" P%d            %d ms          %d ms        %d\n", i, a[i].at, a[i].bt, a[i].pr);
	}
	printf("\n Time quantum: %d\n", quant);
	
//	sorting acc. to increasing arrival time
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(a[j].at<a[i].at)
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
	
//	calculations
	for(i=0;comp!=n;)
	{
		if(a[i].at>c)
		{
			idle+=a[i].at-c;
			if(c)
			{
				cswt_idle[d]='i';
				con_swt[d++]=c;
			}
			c=a[i].at;
			cswt_idle[d]='o';
		}
		
		if(a[i].rt<=quant && a[i].rt>0) 
		{
			con_swt[d++]=c;
		    c+=a[i].rt;
		    a[i].rt=0;
		    flag=1;
		}
	    else if(a[i].rt>0)  
	    {
	    	con_swt[d++]=c;
	        a[i].rt-=quant;
	        c+=quant;
	    }
	    
	    if(a[i].rt==0 && flag==1)  
	    {
	        comp++;
	        a[i].ta=c-a[i].at;
			a[i].wt=a[i].ta-a[i].bt;
			WTsum+=a[i].wt;
			TAsum+=a[i].ta;
	        flag=0;
	    }
	    if(i==n-1)
	    	i=0;
	    else if(a[i+1].at<=c || a[i].rt==0)
	    	i++;
	    else if(a[i].rt)
			i=0;
	}
	con_swt[d++]=c;
	WTavg=WTsum/n;
	TAavg=TAsum/n;
	util_perc=util_time/c*100;
	
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(a[j].p<a[i].p)
			{
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
	
	printf("\n Output:");
	line(42);
	printf(" Process   Waiting time   Turnaround Time");
	line(42);
	for(i=0;i<n;i++)
	{
		printf(" P%d            %d ms            %d ms\n", a[i].p, a[i].wt, a[i].ta);
	}
	
	printf("\n\n Average Waiting Time: %.3f ms\n", WTavg);
	printf("\n Average Turnaround Time: %.3f ms\n", TAavg);
	printf("\n CPU Utilization Time: %.3f ms\n", util_time);
	printf("\n CPU Utilization Percentage: %.3f %%\n", util_perc);
	printf("\n CPU Idle Time: %.3f ms\n", (float)idle);
	printf("\n Context switch points:");
	for(i=0;i<d;i++)
	{
		printf("\n -> %d ms", con_swt[i]);
		if(i==0)
		printf(" | OS -> Process");
		else if(cswt_idle[i]=='i')
		printf(" | Process -> OS");
		else if(cswt_idle[i]=='o')
		printf(" | OS -> Process");
		else if(i==d-1)
		printf(" | Process -> OS\n");
		else
		printf(" | Process -> OS -> Process");
	}
	printf("\n Mode switch points:");
	for(i=0;i<d;i++)
	{
		printf("\n -> %d ms", con_swt[i]);
		if(i==0)
		printf(" | Kernel -> User");
		else if(cswt_idle[i]=='i')
		printf(" | User -> Kernel");
		else if(cswt_idle[i]=='o')
		printf(" | Kernel -> User");
		else if(i==d-1)
		printf(" | User -> Kernel");
		else
		printf(" | User -> Kernel -> User");
	}
	
	getch();
}

void line(int x)
{
	int i;
	printf("\n");
	for(i=0;i<x;i++)
	{
		printf("-");
	}
	printf("\n");
}

