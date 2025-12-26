//RoYaL-_
#include<stdio.h>
#include<stdlib.h>
int req[100], n, head, max_range;
void read()
{
    int i;
    printf("\nEnter the number of requests: ");
    scanf("%d",&n);
    printf("\nEnter the requests: ");
    for(i=0;i<n;i++)
        scanf("%d",&req[i]);
    printf("\nEnter the initial head position: ");
    scanf("%d",&head);
    printf("\nEnter the disk size (max range): ");
    scanf("%d",&max_range);
}
void sort()
{
    int i, j, temp;
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(req[j] > req[j+1])
            {
                temp = req[j];
                req[j] = req[j+1];
                req[j+1] = temp;
            }
        }
    }
}
int main()
{
    int i, seek=0, temp, move, idx;
    read();
    sort();
    
    printf("\nEnter direction (0 for Low, 1 for High): ");
    scanf("%d",&move);
    
    // Find Position
    for(i=0;i<n;i++)
    {
        if(req[i] >= head)
        {
            idx = i;
            break;
        }
    }
    
    printf("Sequence provided: ");
    if(move == 1) // Towards High
    {
         for(i=idx;i<n;i++)
         {
             seek += abs(req[i] - head);
             head = req[i];
             printf("%d -> ", head);
         }
         // Go to max end
         seek += abs((max_range-1) - head);
         head = max_range-1;
         printf("%d -> ", head);
         
         // Reverse
         for(i=idx-1;i>=0;i--)
         {
             seek += abs(req[i] - head);
             head = req[i];
             printf("%d -> ", head);
         }
    }
    else // Towards Low
    {
        for(i=idx-1;i>=0;i--)
        {
            seek += abs(req[i] - head);
            head = req[i];
            printf("%d -> ", head);
        }
        // Go to 0
        seek += abs(0 - head);
        head = 0;
        printf("%d -> ", head);
        
        // Reverse
        for(i=idx;i<n;i++)
        {
            seek += abs(req[i] - head);
            head = req[i];
            printf("%d -> ", head);
        }
    }
    
    printf("END\nTotal Seek Time: %d\n", seek);
}
