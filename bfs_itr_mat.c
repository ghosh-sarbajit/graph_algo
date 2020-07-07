#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define INF 10000

int **adj_mat;
int *distance, *dist_vec;

// queue data structure
struct node{
    int data;
    struct node *next;
};
typedef struct node queue;
queue *node1=NULL;
void enqueue(int num)
{
    queue *temp, *node2;
    temp=(queue *)malloc(sizeof(queue));
    assert(temp!=NULL);
    temp->data=num;
    temp->next=NULL;
    if(node1==NULL)
        node1=temp;
    else
    {
        node2=node1;
        while(node2->next!=NULL)
            node2=node2->next;
        node2->next=temp;
    }
}
int dequeue()
{
    int K;
    K=node1->data;
    node1=node1->next;
    return K;
}
// end of queue data structure

void bfs_itr(int node_num)
{
    //printf("In func\n" );
    int num;
    while(node1!=NULL)
    {
        num=dequeue();
        printf("%d\n",num );
        for(int i=0;i<node_num;i++)
        {
            if(adj_mat[num][i]==1)
            {
                if(distance[i]==INF)
                {
                    enqueue(i);
                    distance[i]=distance[num]+1;
                    dist_vec[i]=num;
                }
            }
        }
    }
}

int main()
{
	int node_num,start_node,end_node;

	printf("Enter node_num : " );
	scanf("%d", &node_num);
	adj_mat=(int **)malloc(node_num*sizeof(int *));
	for(int i=0;i<node_num;i++)
	{
		adj_mat[i]= (int *)malloc(node_num*sizeof(int));
		assert(adj_mat[i] != NULL);
	}
	printf("Enter adj_mat :\n" );
	for(int i=0;i<node_num;i++)
	{
		for(int j=0;j<node_num;j++)
		{
			scanf("%d", &adj_mat[i][j]);
		}
	}
	printf("Enter start_node : " );
	scanf("%d", &start_node);
    distance=(int *)malloc(node_num*sizeof(int));
    assert(distance != NULL);
    dist_vec=(int *)malloc(node_num*sizeof(int));
    assert(dist_vec != NULL);
    for(int i=0;i<node_num;i++)
        distance[i]=INF;
    distance[start_node]=0;
    //printf("Before func\n" );
    enqueue(start_node);
    bfs_itr(node_num);
    printf("distance to other nodes from start_node : \n" );
    for(int i=0; i<node_num;i++)
        printf("%d <= %d => %d\n",start_node,distance[i],i);
    printf("\n");
    printf("Enter end_node\n" );
    scanf("%d", &end_node);
    printf("distance vecctor : \n" );
    printf("%d\t",end_node);
    while(dist_vec[end_node]!=start_node)
    {
        printf("%d\t", dist_vec[end_node]);
        end_node=dist_vec[end_node];
    }
    return 0;
}
