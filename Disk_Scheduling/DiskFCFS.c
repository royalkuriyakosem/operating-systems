//RoYaL-_
#include<stdio.h>
#include<stdlib.h>
int req[100], n, head;
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
}
int main()
{
    int i, seek=0, diff;
    read();
    
    printf("Sequence of movement: ");
    printf("%d", head);
    for(i=0;i<n;i++)
    {
        diff = abs(req[i] - head);
        seek += diff;
        head = req[i];
        printf(" -> %d", head);
    }
    
    printf("\n\nTotal Seek Time: %d\n", seek);
}
