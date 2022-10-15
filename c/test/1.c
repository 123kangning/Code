#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
#define N 100
typedef int element;
typedef struct ArrayList ArrayList;
typedef struct LinkedList LinkedList;
struct ArrayList
{
    int index;
    element num[MAX];
};
struct LinkedList
{
    element data;
    struct LinkedList* next;
};
void ArrayReverse(ArrayList* list){
    for(int i=0;i<N/2;i++){
        int index=N-i-1;
        int temp=list->num[i];
        list->num[i]=list->num[index];
        list->num[index]=temp;
    }
}
void LinkedReverse(LinkedList** list1){
    LinkedList*list=*list1,*last=NULL,*current=list;
    while(current){
        LinkedList*next=current->next;
        current->next=last;
        last=current;
        current=next;
    }
    *list1=last;
}

int main(void){
    int count=0;
    ArrayList array;
    LinkedList* list=(LinkedList*)malloc(sizeof(LinkedList)),*last=list,*current=NULL;
    for(int i=0;i<N;i++){
        array.num[count++]=i;
        if(i==0){
            list->data=i;
            list->next=NULL;
            last=list;
        }else{
            current=(LinkedList*)malloc(sizeof(LinkedList));
            current->data=i;
            current->next=NULL;
            last->next=current;
            last=current;
        }
    }
    for(int i=0;i<N;i++){
        printf("%d ",array.num[i]);
    }printf("\n");
    current=list;
    while(current){
        printf("%d ",current->data);
        current=current->next;
    }printf("\n");
    ArrayReverse(&array);
    LinkedReverse(&list);
    printf("------------------------------reverse------------------------------\n");
    for(int i=0;i<N;i++){
        printf("%d ",array.num[i]);
    }printf("\n");
    current=list;
    for(int i=0;i<N;i++){
        printf("%d ",current->data);
        current=current->next;
    }printf("\n");

}