#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
    int priotity;
    struct node *prev, *next;
};
struct node *head = NULL, *tail = NULL;

struct node *newNode(int priority){
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->priotity = priority;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void inHead(int priority){
    struct node *tmp = newNode(priority);
    if(head == NULL){
        head = tail = tmp;
    }else{
        head->prev = tmp;
        tmp->next = head;
        head = tmp;
    }
}


void inTail(int priority){
    struct node *tmp = newNode(priority);
    if(tail==NULL){
        tail = head = tmp;
    }else{
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
    }
}

void popHead(){
    struct node *tmp = head;
    head = head->next;
    head->prev = NULL;
    free(tmp);
}

void popTail(){
    struct node *tmp = tail;
    tail = tail->prev;
    tail->next = NULL;
    free(tmp);
}

struct node *search(int priority){
    struct node *curr = head;
    while (curr!=NULL&&curr->priotity != priority)
    {
        curr = curr->next;
    }
    if (curr == NULL) return NULL;    
    return curr;
    
}


void printAll(){
    struct node *tmp = head;
    while(tmp!=NULL){
        printf("%d ",tmp->priotity);
        tmp = tmp->next;
    }
}

int main(){
    inTail(10);
    inTail(20);
    printAll();
    return 0;
}
