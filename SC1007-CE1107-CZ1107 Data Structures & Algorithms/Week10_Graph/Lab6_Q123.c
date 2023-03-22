#include <stdio.h>
#include <stdlib.h>

enum GraphType {ADJ_MATRIX, ADJ_LIST}; // Types of Graph Representation

typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;

union GraphForm{
    int **matrix;
    ListNode **list;
};

typedef struct _graph{
    int V;
    int E;
    enum GraphType type;
    union GraphForm adj;
}Graph;

void printGraphMatrix(Graph );
void adjM2adjL(Graph *);
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph,int *);
void printDegreeV(int *,int );

int main()
{
    Graph g;
    int i,j;

    int* degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));

    for(i=0;i<g.V;i++)
        for(j=0;j<g.V;j++)
            g.adj.matrix[i][j] = 0;
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for(i=0;i<g.V;i++)
        degreeV[i]=0;

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d",&V1,&V2)==2)
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else
            break;
        printf("Enter two vertices which are adjacent to each other:\n");
    }

    calDegreeV(g,degreeV);

    printGraphMatrix(g);
    printDegreeV(degreeV,g.V);

    adjM2adjL(&g);

    calDegreeV(g,degreeV);

    printGraphList(g);
    printDegreeV(degreeV,g.V);

    adjL2adjM(&g);
    printGraphMatrix(g);

    return 0;
}

void printGraphMatrix(Graph g)
{
    int i,j;
    if(g.type == ADJ_LIST) {printf("Error"); return;}

    for(i=0;i<g.V;i++){
        for(j=0;j<g.V;j++)
            printf("%d\t",g.adj.matrix[i][j]);
        printf("\n");
    }

}

void adjM2adjL(Graph *g)
{
    int i,j;
    ListNode **list;
    ListNode *temp;

    if(g->type == ADJ_LIST) {printf("Error"); return;}
    if(g->V<=0){printf("Empty graph!"); return;}

    // initialize the adjacency list
    list = (ListNode **) malloc(g->V*sizeof(ListNode *));
    for(i=0;i<g->V;i++)
        list[i] = NULL;

    for(i=0;i<g->V;i++){
        for(j=0;j<g->V;j++){
            if(g->adj.matrix[i][j]==1){
                // insert the vertice j+1 to the LinkedList
                if(list[i]==NULL){
                    list[i] = (ListNode *)malloc(sizeof(ListNode));
                    list[i]->vertex = j+1;  // vertices id/name here
                    list[i]->next = NULL;
                    temp = list[i];
                }
                else{
                    temp->next = (ListNode *)malloc(sizeof(ListNode));
                    temp->next->vertex = j+1;
                    temp->next->next =NULL;
                    temp = temp->next;
                }
            }
        }
    }

    g->type = ADJ_LIST; //change representation form

    //free adjMatrix
    for(i=0;i<g->V;i++)
        free(g->adj.matrix[i]);
    free(g->adj.matrix);

    g->adj.list = list;

}

void adjL2adjM(Graph *g){
    int i,j;
    ListNode *temp;

    if(g->type == ADJ_MATRIX) {printf("Error"); return;}
    if(g->V<=0){printf("Empty graph!"); return;}

    // initialize the adjacency matrix with the size of |V| x |V|
    int ** mat = (int **)malloc(g->V*sizeof(int *));
    for(i=0;i<g->V;i++)
        mat[i] = (int *)malloc(g->V*sizeof(int));

    for(i=0;i<g->V;i++)
        for(j=0;j<g->V;j++)
            mat[i][j] = 0;

    for(i=0;i<g->V;i++){
        temp = g->adj.list[i];
        while(temp!=NULL){
            mat[i][(temp->vertex)-1] = 1;
            temp = temp->next;
        }
    }

    g->type = ADJ_MATRIX;

    for(i=0;i<g->V;i++)
        free(g->adj.list[i]);
    free(g->adj.list);

    g->adj.matrix = mat;

}

void printGraphList(Graph g){
    int i;
    ListNode* temp;

    if(g.type == ADJ_MATRIX) {printf("Error"); return;}

    for(i=0;i<g.V;i++)
    {
        printf("%d:\t",i+1);
        temp = g.adj.list[i];
        while(temp!=NULL){
            printf("%d -> ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void calDegreeV(Graph g, int *degreeV)
{
    int i,j;
    ListNode *temp = NULL;

    if(g.type == ADJ_MATRIX){
        for(i=0;i<g.V;i++){
            degreeV[i] = 0;
            for(j=0;j<g.V;j++){
                degreeV[i] += g.adj.matrix[i][j];  // g.adj.matrix[i][j]: either 0 or 1 here.
            }
        }
    }
    else{
        for(i=0;i<g.V;i++){
            degreeV[i]=0;
            ListNode *temp = g.adj.list[i];
            while(temp != NULL){
                degreeV[i]++;
                temp = temp->next;
            }
        }
    }
}

void printDegreeV(int *degreeV,int V)
{
    int i;
    for(i=0;i<V;i++)
        printf("%d: %d degree\n",i+1,degreeV[i]);
}
