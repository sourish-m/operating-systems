#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <stdlib.h>
void sort();
void sps();
void rrobin();
void fcfs();
void check();
void idle_time(int);
void wt_ta_calc(int);
int change(int, int);
void line(int);

struct PCB {
	int p, at, bt, wt, ta, rt, qn, pr;
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
	// clrscr();
	int i, j;
	
	do {
		printf("\n Enter number of processes: ");
		scanf("%d", &n);

		if(n<1) {
			system("cls");
			printf("\n Number of processes must be > 0");
		}
	}while(n<1);
	
	// input
	printf("\n Enter Arrival time(AT), Burst time(BT), Priority(PR) and Queue No.(QN) according to the corresponding queue types:");
	printf("\n 1 - System(OS) Process [SPS]\n 2 - Interactive Process [RR]\n 3 - Batch Process [FCFS]\n");
	for(i=0;i<n;i++) {
		a[i].p=i;
		printf("\n Process %d", i);
		line(11);
		printf(" AT[%d] = ", i);
		scanf("%d", &a[i].at);
		printf(" BT[%d] = ", i);
		scanf("%d", &a[i].bt);
		printf(" PR[%d] = ", i);
		scanf("%d", &a[i].pr);
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
	printf("\n Input: (Lower the Priority/Queue no., higher the respective priority)");
	line(60);
	printf(" Process   Arrival time   Burst time   Priority   Queue no.");
	line(60);
	for(i=0;i<n;i++)
		printf(" P%d            %d ms          %d ms          %d          %d\n", i, a[i].at, a[i].bt, a[i].pr, a[i].qn);
		
	printf("\n Time quantum for interactive process(es): %d\n", quant);
	
	// calculations
	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {
			if(a[j].at<a[i].at) {
				t=a[i];
				a[i]=a[j];
				a[j]=t;
			}
		}
	}
	con_swt[d++]=c;
	while(comp!=n) {
		check();
		if(f1<=r1)
			sps();
		else if(f2<=r2)
			rrobin();
		else if(f3<=r3)
			fcfs();
	}
	if(con_swt[d-1]!=c)
		con_swt[d++]=c;
	WTavg=WTsum/n;
	TAavg=TAsum/n;
	util_perc=util_time/c*100;

	// output
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
			printf(" | Process -> OS");
		else
			printf(" | Process -> OS -> Process");
	}
	printf("\n\n Mode switch points:");
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

void sort() {
	int i, j, t;
	for(i=f1; i<r1; i++) {
		for(j=i+1; j<=r1; j++) {
			if(a[q1[j]].pr<a[q1[i]].pr || a[q1[j]].pr==a[q1[i]].pr && a[q1[j]].bt<a[q1[i]].bt) {
				t = q1[i];
				q1[i] = q1[j];
				q1[j] = t;
			}
		}
	}
}

void sps() {
	int i, j;
	i = q1[f1];
	
	if(c<a[i].at)
		idle_time(i);
	
	if(con_swt[d-1]!=c)
		con_swt[d++]=c;
	
	sort();
	comp++;
	f1++;
	c1--;
	c+=a[i].rt;
	a[i].rt=0;
	wt_ta_calc(i);
	check();
	
	if(f1<=r1)
		sps();
	else {
		con_swt[d++]=c;
		return;
	}
}

void rrobin() {
	int i, j, count, idk=f2;
	i=q2[f2];
	
	if(a[i].at>c)
		idle_time(i);
	
	if(c1!=0) {
		if(con_swt[d-1]!=c)
			con_swt[d++]=c;
		count=quant;
		while(!change(i, 2) && a[i].rt>0 && count>0) {
			c++;
			a[i].rt--;
			count--;
		}
		
		if(a[i].rt==0) {
			comp++;
			f2++;
			c2--;
			wt_ta_calc(i);
		}
	}
	else {
		if(a[i].rt>quant) {
			if(con_swt[d-1]!=c)
				con_swt[d++]=c;
			a[i].rt-=quant;
			c+=quant;
		}
		else {
			if(con_swt[d-1]!=c)
				con_swt[d++]=c;
			comp++;
			f2++;
			c2--;
			c+=a[i].rt;
			a[i].rt=0;
			wt_ta_calc(i);
		}
	}
	check();
	if(idk==f2)
		f2++;
	
	if(a[i].rt>0)
		q2[++r2]=i;
	
	if(f2<=r2 && !change(i, 2))
		rrobin();
	else {
		con_swt[d++]=c;
		return;
	}
}

void fcfs() {
	int i;
	i = q3[f3];
	
	if(c<a[i].at)
		idle_time(i);
	
	if(c1!=0 || c2!=0) {
		if(con_swt[d-1]!=c)
			con_swt[d++]=c;
		while(!change(i, 3) && a[i].rt>0) {
			c++;
			a[i].rt--;
		}
		
		if(a[i].rt==0) {
			comp++;
			f3++;
			wt_ta_calc(i);
		}
	}
	else {
		if(con_swt[d-1]!=c)
			con_swt[d++]=c;
		c+=a[i].rt;
		a[i].rt=0;
		comp++;
		f3++;
		wt_ta_calc(i);
	}
	
	if(f3<=r3 && !change(i, 3))
		fcfs();
	else {
		con_swt[d++]=c;
		return;
	}
}

void check() {
	int i;
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
			a[i].visited=true;
		}
		else if(f1>r1 && f2>r2 && f3>r3 && !a[i].visited) {
			idle_time(i);
			break;
		}
		else if(a[i].at>c)
			break;
	}
}

void idle_time(int x) {
	idle+=a[x].at-c;
	if(c) {
		if(con_swt[d-1]!=c) {
			cswt_idle[d]='i';
			con_swt[d++]=c;
		}
		else
			cswt_idle[d-1]='i';
	}
	c=a[x].at;
	cswt_idle[d]='o';
	con_swt[d++]=c;
}

void wt_ta_calc(int x) {
	a[x].ta=c-a[x].at;
	a[x].wt=a[x].ta-a[x].bt;
	WTsum+=a[x].wt;
	TAsum+=a[x].ta;
}

int change(int x, int qu) {
	int i;
	for(i=x+1; i<n; i++) {
		if(a[i].at>c)
			return 0;
		else if(a[i].qn<a[x].qn)
			return 1;
	}
	return 0;
}

void line(int x) {
	int i;
	printf("\n");
	for(i=0; i<x; i++)
		printf("-");
	printf("\n");
}
