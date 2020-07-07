#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define INF 5000

// Define macro to swap
#define SWAP(x, y) (x ^= y ^= x ^= y)

//for printing a line
void line_print(int num)
{
    for(int i=0;i<num;i++)
        putchar('*');
    printf("\n");
}


typedef struct{
    int pred, cost;
}node;

typedef struct{
    int node_no;
    node *node1;
}queue;

int **adj_mat;
int **wt_mat;
int queue_length;
queue *q;
node *ver;
int node_num,start_node;

void relax(int i,int j)
{
    int mod_cost;
    mod_cost = ver[i].cost + wt_mat[i][j];
    if(ver[j].cost > mod_cost)
    {
        ver[j].cost=mod_cost;
        ver[j].pred=i;
    }
}

void swap_stack_node(int i, int j)
{
    int temp_int;
    node *temp;
    temp_int=q[i].node_no;
    q[i].node_no=q[j].node_no;
    q[j].node_no=temp_int;
    temp=q[i].node1;
    q[i].node1=q[j].node1;
    q[j].node1=temp;
}

void minheapify()
{
    int k,j;
    for(int i=1;i<queue_length;i++)
    {
        k=i;
        do
        {
            j=(k-1)/2;
            if(q[k].node1->cost < q[j].node1->cost)
            {
                swap_stack_node(k,j);
            }
            k=j;
        } while(j!=0);
    }
}


void build_priority_queue()
{
        queue_length=node_num;
        for(int i=0;i<node_num;i++)
        {
            q[i].node_no=i;
            q[i].node1=&ver[i];
        }
        minheapify();
}

int extractmean()
{
    swap_stack_node(0,queue_length-1);
    queue_length--;
    minheapify();
    return q[queue_length].node_no;
}

void dijksta()
{
    int min;
    build_priority_queue();
    while(queue_length!=0)
    {
        min=extractmean();
        //printf("%d\t", min);
        for(int j=0;j<node_num;j++)
        {
            if(adj_mat[min][j]==1)
                relax(min,j);
        }
    }
}

char *string_filp(char *arg)
{
    if(strlen(arg)<=1)
        return arg;
    int i=0,j=strlen(arg)-1;
    while(i<j)
    {
        SWAP(arg[i],arg[j]);
        i++;
        j--;
    }
}

char *path(int i, int node_num)
{
    char *str = (char *)malloc(20*node_num*sizeof(char));
    int k=i;
    while(ver[i].pred != -1)
    {
        sprintf(str,"%s==> %d ",str,ver[i].pred);
        i=ver[i].pred;
    }
    string_filp(str);
    sprintf(str,"%s%2d",str,k);
    return str;
}

int main()
{
    printf("Enter node_num : " );
	scanf("%d", &node_num);
	adj_mat=(int **)malloc(node_num*sizeof(int *));
	for(int i=0;i<node_num;i++)
	{
		adj_mat[i]= (int *)malloc(node_num*sizeof(int));
		assert(adj_mat[i] != NULL);
	}
    wt_mat=(int **)malloc(node_num*sizeof(int *));
    for(int i=0;i<node_num;i++)
    {
        wt_mat[i]= (int *)malloc(node_num*sizeof(int));
        assert(wt_mat[i]!=NULL);
    }
	printf("Enter adj_mat :\n" );
	for(int i=0;i<node_num;i++)
	{
		for(int j=0;j<node_num;j++)
		{
			scanf("%d", &adj_mat[i][j]);
		}
	}
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            if(adj_mat[i][j]==1)
            {
                printf("Enter weight between: (%d,%d) : ", i,j);
                scanf("%d", &wt_mat[i][j]);
                if(wt_mat[i][j] < 0)
                {
                    fprintf(stderr, "Negative Edge Taboo !!" );
                    return 1;
                }
            }
            else
            {
                wt_mat[i][j]=INF;
            }
        }
    }
    printf("Enter start_node : " );
    scanf("%d", &start_node);
    q=(queue *)malloc(node_num*sizeof(queue));
    assert(q!=NULL);
    ver= (node *)malloc(node_num*sizeof(node));
    assert(ver!=NULL);
    for(int i=0;i<node_num;i++)
    {
        ver[i].pred=-1;
        ver[i].cost=INF;
    }
    ver[start_node].cost=0;

    dijksta(start_node);
    printf("optimal cost vector by dijksta:\t" );
    for(int i=0;i<node_num;i++)
        printf("%d\t", ver[i].cost);
    printf("\n" );
    line_print(50);
    printf("\t\t%s\n","Optimal paths are" );
    line_print(50);
    for(int i=0;i<node_num;i++)
    {
        printf("path %d to %d : %s\n", start_node,i,path(i,node_num));
    }
    line_print(50);
    return 0;
}
