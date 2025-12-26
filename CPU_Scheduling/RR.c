#include<stdio.h>
#include<string.h>
struct process
{
	char name[10];
	int at;
    int at1;
	int bt;
    int bt1;
	int ct;
	int tt;
	int wt;
    int sno;
}p[10];
struct gantt
{
	char name[10];
	int ct;
}g[10];
void read(int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("\nName: ");
		scanf("%s",p[i].name);
		printf("\nArrival time: ");
		scanf("%d",&p[i].at);
		printf("\nBurst time: ");
		scanf("%d",&p[i].bt);
	}
}
void sort_at(int n)
{
	int i,j;
	struct process temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(p[j].at1 > p[j+1].at1)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}	
}
void sort_bt(int n,int initial)
{
	int i,j;
	struct process temp;
	for(i=initial;i<n-1;i++)
	{
		for(j=initial;j<n-1;j++)
		{
			if(p[j].at1==p[j+1].at1 && p[j].bt>p[j+1].bt)
			{
				temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
			}
		}
	}	
}
void display(int n)
{
	int i;
	printf("\n_____________________");
	printf("\nPname|AT|BT|CT|TT|WT|");
	printf("\n_____________________");
	for(i=0;i<n;i++)
	{
		printf("\n%s   |%d |%d |%d |%d |%d |",p[i].name,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt);
	}
	printf("\n_____________________");
	printf("\n");
	
}

void gantt(int num)
{
	int i;
	
	for(i=0;i<num;i++)
	{
		printf("______");
	}
	printf("\n");
	printf("|");
	
	for(i=0;i<num;i++)
	{
		if(strcmp(g[i].name,"idle")==0)
			printf("%s |",g[i].name);
		else
			printf("%s   |",g[i].name);
	}
	printf("\n");
	
	for(i=0;i<num;i++)
	{
		printf("______");
	}
	printf("\n");
	printf("0     ");
	for(i=0;i<num;i++)
	{
		printf("%d     ",g[i].ct);
	}
}
int main()
{
	int n,i,j,t,num,k;
	float avgtt=0,avgwt=0;
	printf("\nEnter the number of process: ");
	scanf("%d",&n);
    printf("\nEnter the number time slice: ");
	scanf("%d",&t);
	read(n);
    for(i=0;i<n;i++)
    {
        p[i].at1=p[i].at;
    }
	sort_at(n);
	for(i=0,j=0;i<n;i++)
	{
        sort_bt(n,i);
		display(n);
		if(p[i].at1!=0 && i==0)
		{	
			p[i].ct=p[i].at1+p[i].bt;
			strcpy(g[j].name,"idle");
			g[j].ct=p[i].at1;	
			j++;
			strcpy(g[j].name,p[i].name);
			g[j].ct=p[i].ct;	
			j++;
		}
		else if(p[i].at1==0 && i==0)
		{
			p[i].ct=p[i].at1+p[i].bt;
			strcpy(g[j].name,p[i].name);
			g[j].ct=p[i].ct;	
			j++;
		}
        else if(p[i].at1!=0)
		{
			p[i].ct=p[i].at1+p[i].bt;
			strcpy(g[j].name,"idle");
			g[j].ct=p[i].at1;	
			j++;
			strcpy(g[j].name,p[i].name);
			g[j].ct=p[i].ct;	
			j++;
		}
		else if(p[i].at1==0)
		{
			p[i].ct=p[i-1].ct+p[i].bt;
			strcpy(g[j].name,p[i].name);
			g[j].ct=p[i].ct;	
			j++;
		}
		for(k=0;k<n;k++)
        {
            p[k].at1=p[k].at1-g[j-1].ct;
            if(p[k].at1<0)
            {
                p[k].at1=0;
            }
	    }
    }
	num=j;
	for(i=0;i<n;i++)
	{
		p[i].tt=p[i].ct-p[i].at;
		p[i].wt=p[i].tt-p[i].bt;
	}
	display(n);
	gantt(num);
	for(i=0;i<n;i++)
	{
		avgtt=avgtt+p[i].tt;
		avgwt=avgwt+p[i].wt;
	}
	avgtt=avgtt/n;
	avgwt=avgwt/n;
	printf("\n");
	printf("\nAverage Turnaroundtime=%f",avgtt);
	printf("\nAverage Waitingtime=%f",avgwt);
	printf("\n");	
}