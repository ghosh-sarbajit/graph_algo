#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//RC4 rand_num
#define PERMU_ARRAY_SIZE 2048
#define KEY_LENGTH 16
int s[PERMU_ARRAY_SIZE],key[KEY_LENGTH];
int i_rc4=0,j_rc4=0,value1=0,value2=0;
int rc4_rand()
{
    float value;//this value will returned
    int temp;
    i_rc4=(i_rc4 + 1)%PERMU_ARRAY_SIZE;
    j_rc4=(j_rc4 + s[i_rc4])%PERMU_ARRAY_SIZE;
    temp=s[i_rc4];
    s[i_rc4]=s[j_rc4];
    s[j_rc4]=temp;
    value1=(s[i_rc4]+s[j_rc4])%PERMU_ARRAY_SIZE;
    value2=s[value2];
    //value=(float)value2/PERMU_ARRAY_SIZE;
    return value2;
}


//visited used for coloring
void DFS(int starting_node,int node_num,int *adj_mat,int *visited)
{
    printf("%d\n", starting_node);
    visited[starting_node]=1;
    for (int i = 0; i < node_num; i++)
    {
        if(!*(visited + i) && *(adj_mat + starting_node*node_num + i) == 1)
        {
            DFS(i,node_num,adj_mat,visited);
        }
    }
}

int main()
{
    srand(time(NULL));
    for(int i=0;i< KEY_LENGTH;i++)
        key[i]=rand()%PERMU_ARRAY_SIZE;
    for (int i = 0; i < PERMU_ARRAY_SIZE; i++)
        s[i] = i;
    //initial random permutation of s[]
    for(int i=0;i<PERMU_ARRAY_SIZE;i++)
    {
        static int j=0,temp;
        j=(j + s[i] + key[i%KEY_LENGTH])%PERMU_ARRAY_SIZE;
        temp=s[i];
        s[i]=s[j];
        s[j]=temp;
    }


    int node_num;
    printf("Enter number of nodes : " );
    scanf("%d",&node_num);
    int *adj_mat;
    adj_mat=(int *)malloc(node_num * node_num * sizeof(int));
    if(adj_mat == NULL)
    {
        printf("Error1 !!\n" );
    }
    for (int i = 0; i < node_num; i++)
    {
        for (int j = i; j < node_num; j++)
        {
            if(i==j)
            {
                *(adj_mat + i*node_num + j)=rc4_rand()%2;
            }
            else
            {
                *(adj_mat + i*node_num + j)=rc4_rand()%2;
                *(adj_mat + j*node_num + i) = *(adj_mat + i*node_num + j);
            }
        }
    }
    //printf("Enter adj_mat : \n");
    /*for (int i = 0; i < node_num; i++)
    {
        for (int j = i; j < node_num; j++)
        {
            if(i==j)
            {
                scanf("%d",(adj_mat + i*node_num + j));
            }
            else
            {
                scanf("%d", (adj_mat + i*node_num + j));
                *(adj_mat + j*node_num + i) = *(adj_mat + i*node_num + j);
            }
        }
    }*/

    printf("Generated matrix : \n" );
    for (int i = 0; i < node_num; i++)
    {
        for (int j = 0; j < node_num; j++)
        {
            printf("%d\t", *(adj_mat + i*node_num + j));
        }
        printf("\n" );
    }
    int *visited;
    visited=(int *)calloc(node_num , sizeof(int));
    if(visited == NULL)
    {
        printf("Error2 !!\n" );
    }
    printf("\n\n" );
    DFS(0,node_num,adj_mat,visited);
    return 0;
}
