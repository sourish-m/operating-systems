#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
void check();
void line(int);
int change(int, int);
void sort();
void rrobin();
void sjf();
void fcfs();

struct PCB {
	int p, at, bt, wt, ta, rt, qn;
	bool visited;
}a[10], t;
int c=0, idle=0, n, con_swt[20], d=0;
float WTsum=0, TAsum=0, WTavg, TAavg, util_time=0, util_perc;
char cswt_idle[40];
int quant, comp=0;
int q1[10], f1=0, r1=-1;
int q2[10], f2=0, r2=-1;
int q3[10], f3=0, r3=-1;
int c1=0, c2=0;

int main() {
//	clrscr();
	int i, j;
	
	do {
		printf("\n Enter number of processes: ");
		scanf("%d", &n);

		if(n<1) {
			system("cls");
			printf("\n Number of processes must be > 0");
		}
	}while(n<1);

	printf("\n Enter Arrival time(AT), Burst time(BT) and Queue No.(QN) according to the corresponding queue types:");
	printf("\n 1 - System Process\n 2 - Interactive Process\n 3 - Batch Process\n");
	for(i=0;i<n;i++) {
		a[i].p=i;
		printf("\n Process %d", i);
		line(11);
		printf(" AT[%d] = ", i);
		scanf("%d", &a[i].at);
		printf(" BT[%d] = ", i);
		scanf("%d", &a[i].bt);
		do {
			printf(" QN[%d] = ", i);
			scanf("%d", &a[i].qn);
		}while(a[i].qn<1 || a[i].qn>3);
		if(a[i].qn==1)
			c1++;
		else if(a[i].qn==2)
			c2++;
		util_time+=a[i].bt;
		a[i].rt=a[i].bt;
		a[i].visited=false;
		printf("\n");
	}
	printf(" Enter time quantum for system process(es): ");
	scanf("%d", &quant);
	
	system("cls");
	printf("\n --------- Multi-Level Queue Scheduling ---------\n");
	printf("\n Input: (Lower the Queue no., higher the priority)");
	line(49);
	printf(" Process   Arrival time   Burst time   Queue no.");
	line(49);
	for(i=0;i<n;i++)
		printf(" P%d            %d ms          %d ms          %d\n", i, a[i].at, a[i].bt, a[i].qn);
		
	printf("\n Time quantum for system process(es): %d\n", quant);

//	sorting acc. to increasing arrival time
	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {
			if(a[j].at<a[i].at || (a[j].at==a[i].at && a[j].qn<a[i].qn)) {
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}

//	calculations
	while(comp!=n) {
		check();
		if(f1<=r1)
			rrobin();
		else if(f2<=r2)
			sjf();
		else if(f3<=r3)
			fcfs();
	}
	con_swt[d++]=c;
	WTavg=WTsum/n;
	TAavg=TAsum/n;
	util_perc=util_time/c*100;


	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {
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
	for(i=0; i<n; i++)
		printf(" P%d            %d ms            %d ms\n", a[i].p, a[i].wt, a[i].ta);

	printf("\n\n Average Waiting Time: %.3f ms\n", WTavg);
	printf("\n Average Turnaround Time: %.3f ms\n", TAavg);
	printf("\n CPU Utilization Time: %.3f ms\n", util_time);
	printf("\n CPU Utilization Percentage: %.3f %%\n", util_perc);
	printf("\n CPU Idle Time: %.3f ms\n", (float)idle);
	printf("\n Context switch points:");
	for(i=0; i<d; i++) {
		printf("\n -> %d ms", con_swt[i]);
		if(i==0 || cswt_idle[i]=='o')
			printf(" | OS -> Process");
		else if(i==d-1 || cswt_idle[i]=='i')
			printf(" | Process -> OS\n");
		else
			printf(" | Process -> OS -> Process");
	}
	printf("\n Mode switch points:");
	for(i=0; i<d; i++) {
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

void rrobin() {
	int i, j;
	
	i=q1[f1];
	f1++;
	
	if(a[i].at>c) {
		if(c) {
			idle+=a[i].at-c;
			cswt_idle[d]='i';
			con_swt[d++]=c;
		}
		c=a[i].at;
		cswt_idle[d]='o';
	}

	if(a[i].rt>quant) {
		con_swt[d++]=c;
		a[i].rt-=quant;
		c+=quant;
	} else {
		con_swt[d++]=c;
		c+=a[i].rt;
		a[i].rt=0;
		comp++;
		c1--;
		a[i].ta=c-a[i].at;
		a[i].wt=a[i].ta-a[i].bt;
		WTsum+=a[i].wt;
		TAsum+=a[i].ta;
	}

	for(j=1; j<n; j++) {
		if(a[j].rt>0 && a[j].at<=c && !a[j].visited) {
			q1[++r1]=j;
			a[j].visited=true;
		}
	}

	if(a[i].rt>0) {
		q1[++r1]=i;
	}
	
	if(f1<=r1)
		rrobin();
	else
		return;
}

void sjf() {
	int i;
	sort();
	i = q2[f2];
	f2++;
	
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
	
	if(c1!=0) {
		c++;
		a[i].rt--;
		
		if(a[i].rt==0) {
			comp++;
			c2--;
			a[i].ta=c-a[i].at;
			a[i].wt=a[i].ta-a[i].bt;
			WTsum+=a[i].wt;
			TAsum+=a[i].ta;
		}
		else
			q2[++r2]=i;
		
		if(change(i, 2)==1)
			return;
	}
	else {
		a[i].wt=c-a[i].at;
		a[i].ta=a[i].wt+a[i].bt;
		WTsum+=a[i].wt;
		TAsum+=a[i].ta;
		c+=a[i].rt;
		a[i].rt=0;
		comp++;
		c2--;
	}
	
	if(f2<=r2)
		sjf();
}

void fcfs() {
	int i;
	i = q3[f3];
	
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
	
	if(c1!=0 || c2!=0) {
		c++;
		a[i].rt--;
		
		if(a[i].rt==0) {
			comp++;
			f3++;
			a[i].ta=c-a[i].at;
			a[i].wt=a[i].ta-a[i].bt;
			WTsum+=a[i].wt;
			TAsum+=a[i].ta;
		}
		
		if(change(i, 3)!=3)
			return;
	}
	else {
		a[i].wt=c-a[i].at;
		a[i].ta=a[i].wt+a[i].bt;
		WTsum+=a[i].wt;
		TAsum+=a[i].ta;
		c+=a[i].rt;
		a[i].rt=0;
		comp++;
		f3++;
	}
	
	if(f3<=r3)
		fcfs();
}

void sort()
{
	int i, j, t;
	
	for(i=f2; i<r2; i++) {
		for(j=i+1; j<=r2; j++) {
			if(a[q2[j]].rt<a[q2[i]].rt) {
				t = q2[i];
				q2[i] = q2[j];
				q2[j] = t;
			}
		}
	}
}

int change(int x, int qu) {
	int i;
	for(i=x+1; i<n; i++) {
		if(a[i].at>c)
			return qu;
		else if(a[i].qn<a[x].qn)
			return a[i].qn;
	}
	return qu;
}

void check() {
	int i;
	bool flag=false;
	for(i=0; i<n; i++) {
		if(a[i].at<=c && !a[i].visited) {
			switch(a[i].qn) {
				case 1:
					q1[++r1]=i;
					break;
				case 2:
					q2[++r2]=i;
					break;
				case 3:
					q3[++r3]=i;
					break;
			}
			flag=true;
			a[i].visited=true;
		}
//		else if(a[i].at>c && !flag) {
//			if(c) {
//				idle+=a[i].at-c;
//				cswt_idle[d]='i';
//				con_swt[d++]=c;
//			}
//			c=a[i].at;
//			cswt_idle[d]='o';
//			break;
//		}
	}
}  

void line(int x)
{
	int i;
	printf("\n");
	for(i=0; i<x; i++)
		printf("-");
	printf("\n");
}
