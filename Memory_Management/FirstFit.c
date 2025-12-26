//RoYaL-_
#include<stdio.h>
struct block
{
    int size;
    int alloc; // -1 if free, process index if allocated
}b[10];
struct process
{
    int i; // process index/id
    int size;
    int b_idx; // block index allocated, -1 if not
}p[10];
void read(int n_b, int n_p)
{
    int i;
    printf("\nEnter the size of blocks:\n");
    for(i=0;i<n_b;i++)
    {
        printf("Block %d: ",i+1);
        scanf("%d",&b[i].size);
        b[i].alloc = -1;
    }
    printf("\nEnter the size of processes:\n");
    for(i=0;i<n_p;i++)
    {
        p[i].i = i+1;
        printf("Process %d: ",i+1);
        scanf("%d",&p[i].size);
        p[i].b_idx = -1;
    }
}
void display(int n_p)
{
    int i;
    printf("\n_____________________________");
    printf("\nProcess|Size|Block No|Block Size|");
    printf("\n_____________________________");
    for(i=0;i<n_p;i++)
    {
        if(p[i].b_idx != -1)
             printf("\n%d      |%d  |%d       |%d        |",p[i].i,p[i].size,p[i].b_idx+1, b[p[i].b_idx].size);
        else
             printf("\n%d      |%d  |Not Alloc| -        |",p[i].i,p[i].size);
    }
    printf("\n_____________________________");
    printf("\n");
}
int main()
{
    int n_b, n_p, i, j;
    printf("\nEnter the number of blocks: ");
    scanf("%d",&n_b);
    printf("\nEnter the number of processes: ");
    scanf("%d",&n_p);
    read(n_b, n_p);
    
    // First Fit Logic
    for(i=0;i<n_p;i++)
    {
        for(j=0;j<n_b;j++)
        {
            if(b[j].alloc == -1 && b[j].size >= p[i].size)
            {
                b[j].alloc = i;
                p[i].b_idx = j;
                break; // Found first fit
            }
        }
    }
    
    display(n_p);
}
