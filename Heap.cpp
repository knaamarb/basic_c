#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NAMESIZE 100



struct Patient
{
    int patientID;
    char name[NAMESIZE];
    int priority; 

}*heap[1000] = {NULL};
int lastIdx = 0;

struct Patient *createPatient(int patientID, const char name[], const int priority){
    struct Patient *newPatient = (struct Patient *) malloc (sizeof(struct Patient));
    newPatient->patientID = patientID;
    newPatient->priority = priority;
    strcpy(newPatient->name, name);
    return newPatient;
}


void swap(struct Patient *a, struct Patient *b){
    struct Patient tmp = *a;
    *a = *b;
    *b = tmp;

}


void upHeap(int idx){
    if (idx == 1)
    {
        return;
    }else{
        int parentIdx = idx/2;
        if (heap[idx]->priority < heap[parentIdx]->priority)
        {
            swap(heap[idx], heap[parentIdx]);
            upHeap(parentIdx);
        }
    }
}

void downHeap(int idx){
    int leftIdx = idx *2;
    int rightIdx = idx *2 +1;
    
    if (rightIdx <= lastIdx)
    {
        if(heap[rightIdx]->priority < heap[idx]->priority || heap[leftIdx]->priority < heap[idx]->priority){
            if (heap[leftIdx]->priority < heap[rightIdx]->priority)
            {
                swap(heap[leftIdx], heap[idx]);
                downHeap(leftIdx);
            }else{
                swap(heap[rightIdx], heap[idx]);
                downHeap(rightIdx);
            }
        }
    }
    else if(leftIdx<= lastIdx){
        if (heap[leftIdx]->priority < heap[idx]->priority)
        {
            swap(heap[leftIdx], heap[idx]);
            downHeap(leftIdx);
        }
    }
}

void addPatient(int patientID, const char name[], int priority){
    lastIdx++;
    heap[lastIdx] = createPatient(patientID, name, priority);
    upHeap(lastIdx);
}
void treatNextPatient(){
    if(lastIdx == 0){
        return;
    }

    struct Patient *tmp = heap[1];
    printf("Patient %s with ID %d was treated.", tmp->name, tmp->patientID);
    heap[1] = heap[lastIdx];
    lastIdx--;
    if (lastIdx>0)
    {
        downHeap(1);
        
    }
    
    free(heap[1]);
}
void peekNextPatient(){
    printf("\nPatient ID: %d\nPatient Name: %s\nPriority: %d\n", heap[1]->patientID, heap[1]->name, heap[1]->priority);
}
void print(){
	for(int i = 1; i <= lastIdx; i++){
		printf("\nIndex |%d|\nPatient ID: %d\nPatient Name: %s\nPriority: %d\n",i, heap[i]->patientID, heap[i]->name, heap[i]->priority);
	}
	puts("");
}

int main(){
    addPatient(2802, "Edward Sebastian", 2);
    addPatient(2802, "Edward Seb", 2);
    addPatient(2802, "Edward mei", 2);
    addPatient(2802, "Edward kocak", 2);
    addPatient(2802, "Edward byan", 2);
    addPatient(2802, "Edward harjuno", 1);
    print();
    peekNextPatient();
    treatNextPatient();
    
    print();

    return 0;
}