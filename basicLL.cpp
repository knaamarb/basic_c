#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
    int key;
    struct node *prev, *next;
}*head = NULL, *tail = NULL;

struct node *newNode(int key){
    // memory allocation
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
    // isi data
	new_node->key = key;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void pushHead(int key){
    struct node *tmp = newNode(key);
    if(head == NULL){
        head = tail = tmp;
        return;
    }else{
        head->prev = tmp;
        tmp->next = head;
        head = tmp;
        return;
    }
}


void pushTail(int key){
    struct node *tmp = newNode(key);
    if(tail==NULL){
        tail = head = tmp;
        return;
    }else{
        tail->next = tmp;
        tmp->prev = tail;
        tail = tmp;
        return;
    }
}

void pushMid_sortA(int key){
	struct node *tmp = newNode(key);
    if(tail==NULL){
        tail = head = tmp;
        return;
    }
	
	if(key<=head->key){
    	pushHead(key);
    	return;
	}else if(key>tail->key){
		pushTail(key);
		return;
	}else{
		struct node *curr = head;
		while(curr->key < key){
			curr = curr->next;
		}
		tmp->next = curr;
		curr->prev->next = tmp;
		curr->prev = tmp;
		tmp->prev = curr->prev;
		
	}
}

void popHead(){
    if(head==NULL)return;
    if(head->next == NULL){
    	free(head);
    	head = tail = NULL;
    	return;
	}else{
	    struct node *tmp = head;
		head = head->next;
	    head->prev = NULL;
	    tmp->next = NULL;
	    free(tmp);
	    tmp = NULL;
	    return;
	}
	
}

void popTail(){
    if(tail==NULL)return;
    if(head->next == NULL){
    	free(head);
    	head = tail = NULL;
    	return;
	}else{
    	struct node *tmp = tail;
	    tail = tail->prev;
	    tail->next = NULL;
	    tmp->prev = NULL;
	    free(tmp);
	    tmp = NULL;
	    return;
	}
}

void popMid(int key){
    if(tail==NULL)return;
    if(key==head->key) {
		popHead();return;
	}else if(key==tail->key){
		popTail();return;
		
	}else{
		struct node *curr = head;
		while(key!=curr->key){
			struct node *tmp = curr;
			curr = curr->next;
			curr->prev = tmp;
		}
		struct node *tmp = curr;
		tmp->next->prev = curr->prev;
		tmp->prev->next = curr->next;
		free(tmp);
		tmp = NULL;
		curr=NULL;
		return;
	}
    
    
    
	struct node *tmp = tail;
}

struct node *search(int key){
    if (head == NULL) return NULL;
	struct node *curr = head;
    while (curr!=NULL){
    	if(curr->key == key)return curr;
        curr = curr->next;
    }
	return NULL;
    
}


void printAll(){
    struct node *tmp = head;
    while(tmp!=NULL){

		printf("%d",tmp->key);
		
        if(tmp->next != NULL){
        	printf(" -> ");	
		}
        tmp = tmp->next;
    }
}

int main(){
    pushMid_sortA(10);
    pushMid_sortA(20);
    pushMid_sortA(15);
    pushMid_sortA(100);
    pushMid_sortA(17);
    printAll();
    puts("");
    popMid(17);
	printAll();
        
        
    return 0;
}
