//RoYaL-_
#include<stdio.h>
#include<string.h>
struct process
{
	char name[10];
	int at;
	int bt;
    int rem;
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
}g[100]; // Increased size for preemptive switches
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
        p[i].rem = p[i].bt;
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
    
    // Priority Preemptive Logic
    int prev_idx = -1;
    
    // To handle initial gap
    if (p[0].at > 0)
    {
        strcpy(g[j].name, "idle");
        g[j].ct = p[0].at;
        j++;
        time = p[0].at;
    }
    
    while(completed < n)
    {
        idx = -1;
        min_pr = 10000;
        
        for(i=0;i<n;i++)
        {
            if(p[i].at <= time && p[i].completed == 0)
            {
                if(p[i].pr < min_pr)
                {
                    min_pr = p[i].pr;
                    idx = i;
                }
                else if(p[i].pr == min_pr) // FCFS tie breaking
                {
                   // If multiple same priority, stick to current if it's one of them to minimize switching?
                   // Or just FCFS based on AT/index
                   // Usually FCFS for same priority.
                   if(idx == -1 || p[i].at < p[idx].at)
                        idx = i;
                }
            }
        }
        
        if(idx != -1)
        {
            // Execute for 1 unit
            p[idx].rem--;
            time++;
            
            // Check if we switched process or just continuing
            if(idx != prev_idx)
            {
                // New gantt entry
                 /* Wait, if I do gantt for EVERY second it's huge. 
                    I should update the last gantt entry if it's the same process?
                    Or create new one only on switch.
                 */
                 if(j > 0 && strcmp(g[j-1].name, p[idx].name) == 0)
                 {
                     g[j-1].ct = time;
                 }
                 else
                 {
                    strcpy(g[j].name, p[idx].name);
                    g[j].ct = time;
                    j++;
                 }
                 prev_idx = idx;
            }
            else
            {
                // Same process continued, update ct of current gantt block
                g[j-1].ct = time;
            }

            if(p[idx].rem == 0)
            {
                p[idx].completed = 1;
                p[idx].ct = time;
                completed++;
                // prev_idx can stay, next loop will find optimal or switch
            }
        }
        else
        {
            // IDLE
             time++;
             if(j>0 && strcmp(g[j-1].name, "idle") == 0)
             {
                 g[j-1].ct = time;
             }
             else
             {
                 strcpy(g[j].name, "idle");
                 g[j].ct = time;
                 j++;
             }
             prev_idx = -1;
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
