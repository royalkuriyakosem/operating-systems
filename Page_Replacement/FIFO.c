//RoYaL-_
#include<stdio.h>
int pages[50], frames[10], n_p, n_f;
void read()
{
    int i;
    printf("\nEnter the number of pages: ");
    scanf("%d",&n_p);
    printf("\nEnter the pages: ");
    for(i=0;i<n_p;i++)
        scanf("%d",&pages[i]);
    printf("\nEnter the number of frames: ");
    scanf("%d",&n_f);
    for(i=0;i<n_f;i++)
        frames[i] = -1; // Initialize frames as empty
}
void display(int time)
{
    int i;
    printf("\n%d\t\t",pages[time]);
    for(i=0;i<n_f;i++)
    {
        if(frames[i] != -1)
            printf("%d\t",frames[i]);
        else
            printf("-\t");
    }
}
int main()
{
    int i, j, k, avail, count=0;
    read();
    printf("\nRef String\tFrames\n");
    printf("__________________________");
    
    j=0; // Frame pointer for FIFO
    for(i=0;i<n_p;i++)
    {
        avail = 0;
        for(k=0;k<n_f;k++)
        {
            if(frames[k] == pages[i])
            {
                avail = 1;
                break; // Hits
            }
        }
        
        if(avail == 0) // Page Fault
        {
            frames[j] = pages[i];
            j = (j+1)%n_f;
            count++;
            display(i);
        }
        else
        {
            // Hit, uncomment to display also on hit if needed
            // display(i);
            // User usually sees faults in simple tables
             printf("\n%d\t\t",pages[i]); // Show ref
             // Show frames (unchanged)
             for(k=0;k<n_f;k++)
             {
                 if(frames[k] != -1)
                     printf("%d\t",frames[k]);
                 else
                     printf("-\t");
             }
        }
    }
    printf("\n\nTotal Page Faults = %d\n",count);
}
