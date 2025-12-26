#include<stdio.h>
int alloc[30][30];
int max[30][30];
int need[30][30];
int instance[30][30];
int available[30][30];
int total_alloc,safety[10];
void readalloc(int pr,int r)
{
	int i,j;
	printf("\n");
	for(i=0;i<pr;i++)
	{
		printf("proces:%d\n",i);
		for(j=0;j<r;j++)
		{
			scanf("%d",&alloc[i][j]);
		}
	}
}
void readmax(int pr,int r)
{
	int i,j;
	printf("\n");
	for(i=0;i<pr;i++)
	{
		printf("proces:%d\n",i);
		for(j=0;j<r;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
}
void readinstance(int r)
{
	int j;
	printf("\n");
	for(j=0;j<r;j++)
	{
		scanf("%d",&instance[0][j]);
	}
}

void find_need(int pr,int r)
{
	int i,j;
	printf("\n");
	for(i=0;i<pr;i++)
	{
		for(j=0;j<r;j++)
		{
			need[i][j]=max[i][j]-alloc[i][j];
		}
	}
	for(i=0;i<pr;i++)
	{
		need[i][r]=0;	
	}
}
void display_table(int pr,int r)
{
	int i,j,flag;
    printf("\n-------------------Resource Allocation Table----------------------\n");
    printf("Process\tAllocated\tMaximum\t\tNeed\t\tAvailable\n");
    for(i = 0; i < pr; i++) 
    {
        printf("P%d\t", i);
        for(j = 0; j < r; j++) 
        {
            printf("%d ", alloc[i][j]);
        }
        printf("\t\t");
        for(j = 0; j < r; j++) 
        {
            printf("%d ", max[i][j]);
        }
        printf("\t\t");
        for(j = 0; j < r; j++) 
        {
            printf("%d ", need[i][j]);
        }
        printf("\t\t");
        if(i == 0) 
        {
            for(j = 0; j < r; j++) 
            {
                printf("%d ", available[0][j]);
            }
        }
        printf("\n");
    }
}
void main()
{
	int pr,r,i,j,req_pr,finish=0,flag,k,l,m;
	printf("\nEnter the number of processes: ");
	scanf("%d",&pr);
	printf("\nEnter the number of resources: ");
	scanf("%d",&r);
	printf("Enter the process allocations: \n");
	readalloc(pr,r);
	printf("Enter the maximum allocations: \n");
	readmax(pr,r);
	find_need(pr,r);
	printf("Enter the instances of resources: \n");
	readinstance(r);
	printf("\n");
	for(j=0;j<r;j++)
	{
		for(i=0,total_alloc=0;i<pr;i++)
		{
			total_alloc=total_alloc+alloc[i][j];
		}
		available[0][j]=instance[0][j]-total_alloc;
	}
	display_table(pr,r);
	printf("\nEnter the requesting process: ");
	scanf("%d",&req_pr);
	flag=0;
	for(j=0;j<r;j++)
	{
		if(available[0][j]<need[req_pr][j])
		{
			flag=1;
			break;
		}
	}
	if(flag==1)
	{
		printf("\nProcess cannot be executed.");
	}
	else
	{	
		i=req_pr,l=0,m=0;
		while (finish!=pr && m<(pr*pr) )
		{
			flag=0;
			for(j=0;j<r;j++)
			{
				if(available[0][j]<need[i][j])
				{
					i=(i+1)%pr;
					flag=1;
					break;
				}
			} 
			if(flag==0 && need[i][r]==0)
			{
				for(j=0;j<r;j++)
				{
					available[0][j]=available[0][j]+alloc[i][j];
				}
				need[i][r]=1;
				safety[l++]=i;
				i=(i+1)%pr;
			}
			if(need[i][r]==1)
			{
				i=(i+1)%pr;
			}
			finish=0;
			for(k=0;k<pr;k++)
			{
				finish=finish+need[k][r];	
			}
			m=m+1;
		}
		if(m==(pr*pr))
		{
			printf("\nDEADLOCK");
		}
		display_table(pr,r);
		printf("\nSafety sequence=");
		for(i=0;i<l;i++)
		{
			printf("p%d-->",safety[i]);
		}
		printf("\n");
		
	}
	
}
