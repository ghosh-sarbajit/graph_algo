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


int **adj_mat;
int **wt_mat;
int node_num,start_node;
int *pred;
int *cost_vec;

void relax(int i,int j)
{
    int mod_cost;
    mod_cost=cost_vec[i] + wt_mat[i][j];
    if(cost_vec[j] > mod_cost)
    {
        cost_vec[j]=mod_cost;
        pred[j]=i;
    }
}

int BellmanFord()
{
    //initializtion done in main_func
    for(int i=0;i<(node_num-1);i++)
    {
        for(int j=0;j<node_num;j++)
        {
            for(int k=0;k<node_num;k++)
            {
                if(adj_mat[j][k]==1)
                    relax(j,k);
            }
        }
    }
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            if(adj_mat[i][j]==1 && cost_vec[j] > cost_vec[i]+wt_mat[i][j])
            {
                return -1;
            }
        }
    }
    return 1;
}

char *path(int i)
{
    char *str = (char *)malloc(20*node_num*sizeof(char));
    int k=i;
    while(pred[i] != -1)
    {
        sprintf(str,"%s==> %d ",str,pred[i]);
        i=pred[i];
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

    //initializtion
    pred=(int *)malloc(node_num*sizeof(int));
    cost_vec=(int *)malloc(node_num*sizeof(int));
    for(int i=0;i<node_num;i++)
    {
        cost_vec[i]=INF;
        pred[i]=-1;
    }
    cost_vec[start_node]=0;
    printf("Hi\n");
    //result print
    if(BellmanFord()==-1)
    {
        printf("Negative cycle !!!\n" );
        return 1;
    }
    printf("\nThe cost_vec :\n");
    for(int i=0;i<node_num;i++)
    {
        printf("%d\t", cost_vec[i]);
    }
    printf("\n" );
    line_print(50);
    printf("\t\t%s\n","Optimal paths are" );
    line_print(50);
    for(int i=0;i<node_num;i++)
    {
        printf("path %d to %d : %s\n", start_node,i,path(i));
    }
    line_print(50);
    return 0;
}
