#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#define INF 100
//#define MIN(a,b) ((a<b)?a:b)

int node_num;
int **adj_mat, **wt_mat;
int **pi_mat, **D_mat;

int sum(int a,int b)
{
    if(a==INF || b==INF)
    {
        return INF;
    }
    else
    {
        return a+b;
    }
}

int MIN(int a,int b)
{
    if(a<=b)
    return a;
    else
    return b;
}

void pi_D_mat_calc(int iter)
{
    //printf("Hi\n" );
    int **mat,**mat1;
    int pred;
    mat=(int **)malloc(node_num*sizeof(int *));
    mat1=(int **)malloc(node_num*sizeof(int *));
	for(int i=0;i<node_num;i++)
	{
		mat[i]= (int *)malloc(node_num*sizeof(int));
		assert(mat[i] != NULL);
        mat1[i]= (int *)malloc(node_num*sizeof(int));
		assert(mat1[i] != NULL);
	}
    mat1=pi_mat;
    printf("D_mat :\n" );
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            printf("%5d  ",D_mat[i][j]);
        }
        printf("\n");
    }

    printf("pi_mat: \n" );
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            printf("%5d  ",pi_mat[i][j]);
        }
        printf("\n");
    }

    //update part
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            mat[i][j]=MIN(D_mat[i][j],sum(D_mat[i][iter],D_mat[iter][j]));
            if(mat[i][j]!=D_mat[i][j])
            {
                pred=iter;
                if(mat1[iter][j]!=pred)
                {
                    pred=mat1[iter][j];
                    mat1[i][j]=pred;
                }
            }
        }
    }
    D_mat=mat;
    pi_mat=mat1;
}

void pi_D_mat_calc_0()
{
    int **mat,**mat1;
    mat=(int **)malloc(node_num*sizeof(int *));
    mat1=(int **)malloc(node_num*sizeof(int *));
    D_mat=(int **)malloc(node_num*sizeof(int *));
    pi_mat=(int **)malloc(node_num*sizeof(int *));
	for(int i=0;i<node_num;i++)
	{
		mat[i]= (int *)malloc(node_num*sizeof(int));
		assert(mat[i] != NULL);
        mat1[i]= (int *)malloc(node_num*sizeof(int));
		assert(mat1[i] != NULL);
        D_mat[i]= (int *)malloc(node_num*sizeof(int));
		assert(D_mat[i] != NULL);
        pi_mat[i]= (int *)malloc(node_num*sizeof(int));
		assert(pi_mat[i] != NULL);
	}
    for(int i=0;i<node_num;i++)
	{
		for(int j=0;j<node_num;j++)
		{
			if(i==j)
            {
                mat[i][j]=0;
                mat1[i][j]=INF;
            }
            else if(adj_mat[i][j]==1)
            {
                mat[i][j]=wt_mat[i][j];
                mat1[i][j]=i;
            }
            else
            {
                mat[i][j]=INF;
                mat1[i][j]=INF;
            }
		}
	}
    D_mat=mat;
    pi_mat=mat1;
}

void Floyd_Warshall()
{
    pi_D_mat_calc_0();
    //printf("Hiiii\n");
    //printf("%d\n", node_num);
    for(int count=0;count<node_num;count++)
    {
        //printf("Haaa\n" );
        pi_D_mat_calc(count);
    }
}
int main()
{
	int start_node,end_node;

	printf("Enter node_num : " );
	scanf("%d", &node_num);
    //adj_mat
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
    //wt_mat
    wt_mat=(int **)malloc(node_num*sizeof(int *));
	for(int i=0;i<node_num;i++)
	{
		wt_mat[i]= (int *)malloc(node_num*sizeof(int));
		assert(wt_mat[i] != NULL);
	}
	printf("Enter adj_mat :\n" );
	for(int i=0;i<node_num;i++)
	{
		for(int j=0;j<node_num;j++)
		{
			scanf("%d", &wt_mat[i][j]);
		}
	}

    Floyd_Warshall();

    printf("D_mat :\n" );
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            printf("%5d  ",D_mat[i][j]);
        }
        printf("\n");
    }

    printf("pi_mat: \n" );
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            printf("%5d  ",pi_mat[i][j]);
        }
        printf("\n");
    }
    return 0;
}
