
#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
    int data;
    int bf;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}BiTNode,*Bitree;

void inlist(Bitree T);
void R_rotate(Bitree *p);
void L_rotate(Bitree *p);
void LeftBalance(Bitree *T);
void RightBalance(Bitree *T);
int InsertAVL(Bitree *T,int e,int *taller);


int main(void)
{
    int i,n,e,taller;
    int a[]={3,2,1,4,5,6,7,10,9,8};
    Bitree T=NULL;
    for(i=0;i<10;i++)
    {
        InsertAVL(&T,a[i],&taller);
    }
    inlist(T);
    return 0;
}

void inlist(Bitree T)
{
    if(!T)
    return;
    printf(" %d ",T->data);
    inlist(T->lchild);
    inlist(T->rchild);
}

void R_rotate(Bitree *p)
{
    Bitree L=(*p)->lchild;
    (*p)->lchild=L->rchild;
    L->rchild=(*p);
    *p=L;
}

void L_rotate(Bitree *p)
{
    Bitree R=(*p)->rchild;
    (*p)->rchild=R->lchild;
    R->lchild=(*p);
    *p=R;
}

void LeftBalance(Bitree *T)
{
    Bitree L,Lr;
    L=(*T)->lchild;
    switch(L->bf)
    {
        case 1:
            (*T)->bf=L->bf=0;
            R_rotate(T);
            break;
        case -1:
            Lr=L->rchild;
            switch(Lr->bf)
            {
                case 1:
                    L->bf=0;
                    (*T)->bf=-1;
                    break;
                case -1:
                    L->bf=1;
                    (*T)->bf=0;
                    break;
                case 0:
                    L->bf=0;
                    (*T)->bf=0;
                    break;
            }
            Lr->bf=0;
            L_rotate(&(*T)->lchild);
            //L_rotate(&L);
            R_rotate(T);
    }
}
void RightBalance(Bitree *T)
{
    Bitree R,Rl;
    R=(*T)->rchild;
    switch(R->bf)
    {
        case -1:
            (*T)->bf=R->bf=0;
            L_rotate(T);
            break;
        case 1:
            Rl=R->lchild;
            switch(Rl->bf)
            {
                case -1:
                    R->bf=0;
                    (*T)->bf=1;
                    break;
                case 1:
                    R->bf=-1;
                    (*T)->bf=0;
                    break;
                case 0:
                R->bf=(*T)->bf=0;
                    break;
            }
            Rl->bf=0;
            R_rotate(&(*T)->rchild);
            L_rotate(T);
    }
}
int InsertAVL(Bitree *T,int e,int *taller)//?????????1???????????????taller???1??????AVL?????????
{
    if(!*T)//??????
    {
        *T=(Bitree)malloc(sizeof(BiTNode));
        (*T)->data=e;
        (*T)->lchild=(*T)->rchild=NULL;
        (*T)->bf=0;
        *taller=1;
    }
    else//?????????
    {
        if(e==(*T)->data)
        {
            *taller=0;
            return 0;
        }
        if(e<(*T)->data)//????????????????????????
        {
            if(!InsertAVL(&(*T)->lchild,e,taller))
            {
                return 0;
            }
            if(*taller)//????????????????????????
            { 
                switch((*T)->bf)
                {
                    case 1:
                        LeftBalance(T);
                        *taller=0;
                        break;
                    case 0:
                        (*T)->bf=1;
                        *taller=1;
                        break;
                    case -1:
                        (*T)->bf=0;
                        *taller=0;
                        break;
                }
            }
        }
        else//????????????????????????
        {
            if(!InsertAVL(&(*T)->rchild,e,taller))
            {
                return 0;
            }
            if(*taller)//????????????????????????
            {
                switch((*T)->bf)
                {
                    case -1:
                        RightBalance(T);
                        *taller=0;
                        break;
                    case 0:
                        (*T)->bf=-1;
                        *taller=1;
                        break;
                    case 1:
                        (*T)->bf=0;
                        *taller=0;
                        break;
                }
            }
        }
    }
    return 1;
}
