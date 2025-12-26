//RoYaL-_
#include<stdio.h>
int pages[50], frames[10], freq[10], time[10], n_p, n_f;
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
        freq[i] = 0;
        time[i] = 0; // FIFO tie break
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
int findLFU()
{
    int i, min = freq[0], pos = 0;
    // Find min freq
    for(i=1;i<n_f;i++)
    {
        if(freq[i] < min)
        {
            min = freq[i];
            pos = i;
        }
        else if (freq[i] == min) // Tie breaking: FIFO (by time loaded/used?)
        {
            if (time[i] < time[pos]) // Oldest loaded
            {
                 min = freq[i]; // Same min
                 pos = i;
            }
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
                freq[k]++;
                // time[k] = t++; // Usually for LFU-LRU tie break? Or just LFU? Standard LFU keeps old time for FIFO tie break.
                // If just LFU, we usually don't update time on hit if using FIFO for tie break.
                break;
            }
        }
        
        if(avail == 0) // Fault
        {
            int empty = 0;
            for(k=0;k<n_f;k++)
            {
                if(frames[k] == -1)
                {
                    frames[k] = pages[i];
                    freq[k] = 1;
                    time[k] = t++;
                    empty = 1;
                    break;
                }
            }
            
            if(!empty)
            {
                int pos = findLFU();
                frames[pos] = pages[i];
                freq[pos] = 1;
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
