#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
void line(int);

struct PCB
{
	int p, at, bt, wt, ta;
}a[10], t;

void main() {
	int c=0, idle=0, i, j, n, con_swt[20], d=0;
	float WTsum, TAsum, WTavg, TAavg, util_time=0, util_perc;
	char cswt_idle[40];
	// clrscr();
	do {
		printf("\n Enter number of processes: ");
		scanf("%d", &n);
		if(n<1) {
			system("cls");
			printf("\n Number of processes must be > 0");
		}
	}while(n<1);
	
	printf("\n Enter Arrival time(AT) and Burst time(BT) for processes:\n");
	for(i=0;i<n;i++) {
		a[i].p=i;
		printf("\n Process %d", i);
		line(11);
		printf(" AT[%d] = ", i);
		scanf("%d", &a[i].at);
		printf(" BT[%d] = ", i);
		scanf("%d", &a[i].bt);
		printf("\n");
	}
	
	system("cls");
	printf("\n --------- FCFS Scheduling ---------\n");
	printf("\n Input:");
	line(37);
	printf(" Process   Arrival time   Burst Time");
	line(37);
	for(i=0;i<n;i++)
		printf(" P%d            %d ms          %d ms\n", i, a[i].at, a[i].bt);
	
	// sorting acc. to increasing arrival time
	for(i=0;i<n;i++) {
		for(j=i+1;j<n;j++) {
			if(a[j].at<a[i].at) {
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
	
	// calculations
	for(i=0;i<n;i++) {
		util_time+=a[i].bt;
		if(c<a[i].at) {
			idle+=a[i].at-c;
			if(c) {
				cswt_idle[d]='i';
				con_swt[d++]=c;
			}
			c=a[i].at;
			cswt_idle[d]='o';
		}
		con_swt[d++]=c;
		a[i].wt=c-a[i].at;
		a[i].ta=a[i].wt+a[i].bt;
		WTsum+=a[i].wt;
		TAsum+=a[i].ta;
		c+=a[i].bt;
	}
	con_swt[d++]=c;
	WTavg=WTsum/n;
	TAavg=TAsum/n;
	util_perc=util_time/c*100;
	
	for(i=0;i<n;i++) {
		for(j=i+1;j<n;j++) {
			if(a[j].p<a[i].p) {
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
		printf(" P%d            %d ms            %d ms\n", a[i].p, a[i].wt, a[i].ta);
	
	printf("\n\n Average Waiting Time: %.3f ms\n", WTavg);
	printf("\n Average Turnaround Time: %.3f ms\n", TAavg);
	printf("\n CPU Utilization Time: %.3f ms\n", util_time);
	printf("\n CPU Utilization Percentage: %.3f %%\n", util_perc);
	printf("\n CPU Idle Time: %.3f ms\n", (float)idle);
	printf("\n Context switch points:");
	for(i=0;i<d;i++) {
		printf("\n -> %d ms", con_swt[i]);
		if(i==0 || cswt_idle[i]=='o')
			printf(" | OS -> Process");
		else if(i==d-1 || cswt_idle[i]=='i')
			printf(" | Process -> OS");
		else
			printf(" | Process -> OS -> Process");
	}
	printf("\n\n Mode switch points:");
	for(i=0;i<d;i++) {
		printf("\n -> %d ms", con_swt[i]);
		if(i==0 || cswt_idle[i]=='o')
			printf(" | Kernel -> User");
		else if(i==d-1 || cswt_idle[i]=='i')
			printf(" | User -> Kernel");
		else
			printf(" | User -> Kernel -> User");
	}
	getch();
}

void line(int x) {
	int i;
	printf("\n");
	for(i=0;i<x;i++)
		printf("-");
	printf("\n");
}
