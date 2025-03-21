#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct node {
    int d,m,yyyy;
    int value;
    struct node *next, *prev;

}*head[4], *tail[4];
int stock[4]= {0};




struct node *newnode(int value, int d, int m, int yyyy){
    struct node *tmp = (struct node*)malloc(sizeof(struct node));
    tmp->next = tmp->prev = NULL;
    tmp->value = value;
    tmp->d = d;
    tmp->m = m;
    tmp->yyyy = yyyy;
    return tmp;
}


void inHead(int value, int n, int d, int m, int yyyy){
    struct node *tmp = newnode(value, d, m, yyyy);
    if(head[n] == NULL){
        head[n] = tail[n] = tmp;
    }else{
        tmp->next = head[n];
        head[n]->prev = tmp;
        head[n] = tmp;
    }
}

void insert(){
    int d,m,yyyy;
    int value;
    char diamond[10];
    while (true)
    {
        scanf("%d-%d-%d %s %d", &d,&m,&yyyy, diamond, &value);
        if(strcmp(diamond, "100D") == 0){
            inHead(value, 1, d, m, yyyy);
            stock[1] += value;
            printf("value %d\n", value);
            break;
        }else if(strcmp(diamond, "500D") == 0){
            inHead(value, 2, d, m, yyyy);
            stock[2] += value;
            break;
        }else if(strcmp(diamond, "1000D") == 0){
            inHead(value, 3, d, m, yyyy);
            stock[3] += value;
            break;
        }else{
            printf("Invalid diamond");
        }
        
    }

}

void display(){
    for (int i = 1; i < 4; i++)
    {
        char diamond[10];
        if(i == 1){
            strcpy(diamond, "100D");
        }else if(i==2){
            strcpy(diamond, "500D");
            printf("\nACC\n\n");
        }else if(i==3){
            strcpy(diamond, "1000D");
        }else{
            printf("Invalid!");
        }
        struct node *curr = head[i];
        printf("%s Stock: %d\n", diamond,stock[i]);
        while(curr!=NULL){
            printf("%s : %d item (%d-%d-%d)\n",diamond,  curr->value, curr->d, curr->m, curr->yyyy);
            curr = curr->next;
        }
        
    }
    
}


void delVal(struct node *curr){
    if(curr == NULL){
        return;
    }
    delVal(curr->next);
    free(curr);
    curr = NULL ;
}

int main(){

    int tc;
    scanf("%d", &tc);
    for(int i = 0; i < tc; i++){
        insert();
    }
    display();
    char diamond[10]; 
    scanf("%s", diamond);
    if(strcmp(diamond, "100D") == 0){
        delVal(head[1]);
        display();
    }else if(strcmp(diamond, "500D") == 0){
        delVal(head[2]);
        display();
    }else if(strcmp(diamond, "1000D") == 0){
        delVal(head[3]);
        display();
    }else{
        printf("Invalid diamond");
    }


    return 0; 
}