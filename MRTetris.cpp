#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

/*
menu utama

 register
 exit
 user page
admin page
 bikin block
menu game
 block to linkedlist
 stat menu
 game over menu

 

*/
struct block{
    char map[7][7];
    struct block *next, *prev;
}*head = NULL, *tail = NULL;

struct block *newBlock(char arr[7][7]){
    struct block *tmp = (struct block*)malloc(sizeof(struct block));
    tmp->next = tmp->prev = NULL;
    for(int i = 0; i<7 ;i++){
        for(int j = 0; j<7; j++){
            tmp->map[i][j] = arr[i][j];
        }
    }
    return tmp;
}

void inTail(char arr[7][7]){
    struct block *tmp = newBlock(arr);
    if(tail==NULL){
        tail = head = tmp;
    }else{
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
    }
}

char inputUsername(){
    printf("Username: ('0' to back)\n");
    printf("--------------------------");
    // scanf("");
    printf("--------------------------");

}



void printMenu(){
    puts("\n___  _________     _____  _____  _____ ______  _____  _____");
    puts("|  \\/  || ___ \\   |_   _||  ___||_   _|| ___ \\|_   _|/  ___|");
    puts("| .  . || |_/ /     | |  | |__    | |  | |_/ /  | |  \\ `--.");
    puts("| |\\/| ||    /      | |  |  __|   | |  |    /   | |   `--. \\");
    puts("| |  | || |\\ \\  _   | |  | |___   | |  | |\\ \\  _| |_ /\\__/ /");
    puts("\\_|  |_/\\_| \\_|(_)  \\_/  \\____/   \\_/  \\_| \\_| \\___/ \\____/");
    printf("\n\n1. Play\n2. View User\n3. Exit\n>> ");


}


int main(){
    int menu = 0;
    printMenu();
    scanf("%d", &menu);
    switch (menu)
    {
    case 1:
        //
        break;
    case 2:
        //
        break;
    case 3:
        //
        break;
    default:
        break;
    }


}