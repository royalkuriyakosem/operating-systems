//RoYaL-_
#include<stdio.h>
#include<string.h>
struct process
{
	char name[10];
	int at;
	int bt;
	int pr;
	int ct;
	int tt;
	int wt;
    int completed;
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
		printf("\nPriority: ");
		scanf("%d",&p[i].pr);
        p[i].completed = 0;
	}
}
void sort(int n)
{
	int i,j;
	struct process temp;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(p[j].at > p[j+1].at)
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
	printf("\n________________________");
	printf("\nPname|AT|BT|PR|CT|TT|WT|");
	printf("\n________________________");
	for(i=0;i<n;i++)
	{
		printf("\n%s   |%d |%d |%d |%d |%d |%d |",p[i].name,p[i].at,p[i].bt,p[i].pr,p[i].ct,p[i].tt,p[i].wt);
	}
	printf("\n________________________");
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
	int n,i,j=0,num,time=0,completed=0,min_pr,idx;
	float avgtt=0,avgwt=0;
	printf("\nEnter the number of process: ");
	scanf("%d",&n);
	read(n);
	sort(n);
    
    // Time starts at the first arrival time if implementation allows or 0. 
    // User's FCFS main loop logic was manual. 
    // I will use a loop until all completed.
    
    // First skip time to first arrival if needed (handled in logic or pre-loop)
    // But since I need to fill gaps with IDLE, I'll track time carefully.
    
    // To match user style, I will iterate. 
    // User's logic: loop i=0 to n. 
    // Priority non-preemptive requires selection at each step.
    
    while(completed < n)
    {
        idx = -1;
        min_pr = 10000;
        
        // Find process with min priority value (highest priority) arrived by current time
        for(i=0;i<n;i++)
        {
            if(p[i].at <= time && p[i].completed == 0)
            {
                if(p[i].pr < min_pr)
                {
                    min_pr = p[i].pr;
                    idx = i;
                }
                else if(p[i].pr == min_pr)
                {
                    if(p[i].at < p[idx].at) // FCFS within same priority implicitly by sort? or explicit
                        idx = i;
                }
            }
        }
        
        if(idx != -1)
        {
            // Execute process
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].completed = 1;
            
            strcpy(g[j].name, p[idx].name);
            g[j].ct = time;
            j++;
            completed++;
        }
        else
        {
            // No process available, idle
            // If there are process pending but not arrived, jump to next arrival
            // or increment time.
            // IDLE block
            /* Check if we need to insert idle logic carefully to match user style */
             // Find next arrival
             int next_at = 10000;
             for(i=0;i<n;i++)
             {
                 if(p[i].completed == 0 && p[i].at < next_at)
                    next_at = p[i].at;
             }
             
             if(next_at < 10000 && next_at > time)
             {
                 strcpy(g[j].name, "idle");
                 g[j].ct = next_at;
                 j++;
                 time = next_at;
             }
             else
             {
                 // Should not happen if completed < n
                 time++;
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
