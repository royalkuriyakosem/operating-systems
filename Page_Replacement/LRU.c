//RoYaL-_
#include<stdio.h>
int pages[50], frames[10], time[10], n_p, n_f;
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
    {
        frames[i] = -1; 
        time[i] = 0;
    }
}
void display(int p_idx)
{
    int i;
    printf("\n%d\t\t",pages[p_idx]);
    for(i=0;i<n_f;i++)
    {
        if(frames[i] != -1)
            printf("%d\t",frames[i]);
        else
            printf("-\t");
    }
}
int findLRU(int current_time)
{
    int i, min = time[0], pos = 0;
    for(i=1;i<n_f;i++)
    {
        if(time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}
int main()
{
    int i, j, k, avail, count=0, t=1;
    read();
    printf("\nRef String\tFrames\n");
    printf("__________________________");
    
    for(i=0;i<n_p;i++)
    {
        avail = 0;
        for(k=0;k<n_f;k++)
        {
            if(frames[k] == pages[i])
            {
                avail = 1;
                time[k] = t++; // Update usage time
                break;
            }
        }
        
        if(avail == 0) // Fault
        {
            // Check for empty slots first
            int empty = 0;
            for(k=0;k<n_f;k++)
            {
                if(frames[k] == -1)
                {
                    frames[k] = pages[i];
                    time[k] = t++;
                    empty = 1;
                    break;
                }
            }
            
            if(!empty)
            {
                int pos = findLRU(t);
                frames[pos] = pages[i];
                time[pos] = t++;
            }
            count++;
            display(i);
        }
        else
        {
            // Hit
             printf("\n%d\t\t",pages[i]);
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
