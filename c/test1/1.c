#include <stdio.h>
#include <stdlib.h>

#define MAXVEX 10001
typedef int Vextype;
typedef struct {
    int**arcs;
    Vextype vex[MAXVEX + 1];
    int vexnum;
    int arcnum;
} AdjMatrix;

void Creat_AdjMatrix(AdjMatrix *G); //创建邻接矩阵
int LocateVex_AdjMatrix(AdjMatrix *G, Vextype v);
void test(AdjMatrix M);

int main() {
    AdjMatrix gM;
    Creat_AdjMatrix(&gM);
    test(gM);
    return 0;
}

void Creat_AdjMatrix(AdjMatrix *G) //创建邻接矩阵
{
    int i, j, k;
    Vextype v1, v2;
    scanf("%d %d", &(G->vexnum), &(G->arcnum));
    G->arcs=(int**)malloc(sizeof(int*)*(G->vexnum+1));
    if(G->vexnum>=1500)while(1);
    for (i = 1; i <= G->vexnum; i++) {
        G->arcs[i]=(int*)malloc(sizeof(int)*(G->vexnum+1));
        for (j = 1; j <= G->vexnum; j++)
            G->arcs[i][j] = 0;
    }
    for (k = 1; k <= G->arcnum; k++) {
        scanf("%d %d", &v1, &v2);
        G->arcs[v1][v2] = 1;
        G->arcs[v2][v1] = 1;
    }
}

int LocateVex_AdjMatrix(AdjMatrix *G, Vextype v) //输出邻接表
{
    int i;
    for (i = 1; i <= G->vexnum; i++)
        if (G->vex[i] == v)
            return i;
    return 0;
}
/* 请在这里填写答案 */
int min(int a,int b){
    return a>b?b:a;
}
void test(AdjMatrix G) {
    int n=0;
    scanf("%d",&n);
    int*num=(int*)malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&num[i]);
        //printf("%d ",num[i]);
    }//printf("\n");
    for(int i=1;i<=G.vexnum;i++){
        for(int j=1;j<=G.vexnum;j++){
            if(G.arcs[i][j]){
                for(int k=1;k<=G.vexnum;k++){
                    if(G.arcs[j][k]){
                        if(G.arcs[i][k]==0)
                            G.arcs[i][k]=G.arcs[i][j]+G.arcs[j][k];
                        else
                            G.arcs[i][k]=min(G.arcs[i][k],G.arcs[i][j]+G.arcs[j][k]);
                    }

                }
            }
        }
    }
//         for(int i=1;i<=G.vexnum;i++){
//         for(int j=1;j<=G.vexnum;j++)printf("%d ",G.arcs[i][j]);
//         printf("\n");
//     }
    int sign=0;//sign==1时，非连通
    for(int i=1;i<=G.vexnum;i++){
        for(int j=1;j<=G.vexnum;j++){
            if(!G.arcs[i][j]){
                sign=1;
                goto here;
            }
        }
    }
    here:
    for(int i=0;i<n;i++){
        double sum=0;
        for(int j=1;j<=G.vexnum;j++){
            sum+=G.arcs[num[i]][j];
        }
        sum=(G.vexnum-1)/(sum-G.arcs[num[i]][num[i]]);
        if(sign)sum=0;
        printf("Cc(%d)=%.2lf\n",num[i],sum);
    }
}