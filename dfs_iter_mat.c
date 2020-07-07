#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int **adj_mat;
int *start_time,*finish_time;//array contains start_time for each node
int *visit;//array; 0 if unvisited
int current_time,*step,r=1;

//for printing a dashed line
void line_print(int num)
{
    for(int i=0;i<num;i++)
        putchar('-');
    printf("\n");
}

//stack data structure
struct data_structure_stack
{
    int val_at_stack;
    struct data_structure_stack *bottom;
};
typedef struct data_structure_stack stack;
stack *node1,*node2;
//stack methods
void push(int i,stack **node)
{
    //printf("HiPush\n" );
    stack *new_node;
    new_node=(stack *)malloc(sizeof(stack));
	assert(new_node != NULL);
    new_node -> val_at_stack = i;
    //printf("%d\n", new_node -> val_at_stack);
    new_node -> bottom = (*node);//old top
    *node = new_node;
    //printf("%d\n", (*node) -> val_at_stack);
    //printf("%s  %d\n", "abcd",(node1->val_at_stack));
}
int pop(stack **node)
{
    int k;
    k=(*node) -> val_at_stack;
    (*node) = (*node) -> bottom;
    return k;
}
// end of stack data structure
 void dfs(int n)
 {
     int number,flag,count,data_at_temp;
     stack *temp;
     while(node1!=NULL)
     {
         number=pop(&node1);
         if(visit[number]==0)
         {
             start_time[number]=current_time;
             current_time++;
             push(number,&node2);
             visit[number]=1;
             flag=1;
             for(count=0;count<n;count++)
             {
                 if(adj_mat[number][count]==1 && visit[count]==0)
                 {
                     push(count,&node1);
                     flag=0;
                 }
             }
             if(flag==1)
             {
                 visit[number]=2;
                 step[number]=r;
                 finish_time[number]=current_time;
                 current_time++;
                 node2=node2->bottom;
                 temp=node2;
                 while(temp!=NULL)
                 {
                     data_at_temp=temp->val_at_stack;
                     for(count=0;count<n;count++)
                     {
                         if(adj_mat[data_at_temp][count]==1 && visit[count]==0)
                         {
                             current_time++;
                             break;
                         }
                     }
                     if(count==n)
                     {
                         temp=temp->bottom;
                         node2=temp;
                         visit[data_at_temp]=2;
                         step[data_at_temp]=r;
                         finish_time[data_at_temp]=current_time;
                         current_time++;
                     }
                     else
                        temp=NULL;
                 }
             }
         }
     }
 }

int main()
{
    int node_num,start_node,temp_node_num;
	int how_many_visited;
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
	// start time of discovery
	start_time=(int *)malloc(node_num*sizeof(int));
	assert(start_time != NULL);
	// finsh time
	finish_time=(int *)malloc(node_num*sizeof(int));
	assert(finish_time != NULL);
	// whether visited 0,1,2
    // 0: ~visited; 1: discoved; 2: visited
	visit=(int *)malloc(node_num*sizeof(int));
	assert(visit != NULL);
	step=(int *)malloc(node_num*sizeof(int));
	assert(step != NULL);
	for(int i=0;i<node_num;i++)
	{
		*(step+i)=0;
		*(visit+i)=0;
	}
	current_time=0;
    temp_node_num=node_num;
    printf("\n\n" );
    line_print(50);
    printf("%-15s%-15s%-15s\n", "Node","start_time","finish_time");
    line_print(50);
    while(temp_node_num>0)
    {
        push(start_node,&node1);
        dfs(node_num);
        for(int i=0;i<node_num;i++)
        {
            if(visit[i]=2 && step[i]==r)
            {
                printf("%-15d%-15d%-15d\n",i,start_time[i],finish_time[i]);
                how_many_visited++;
            }
            if(visit[i]==0)
                start_node=i;
        }
        printf("\n" );
        r++;
        temp_node_num=node_num-how_many_visited;
    }
    line_print(50);
    printf("\n" );
    return 0;
}
