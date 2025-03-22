#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>

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

// Console manipulation
	void moveCursor(){
		printf("\033[XA"); // Move up X lines;
	printf("\033[XB"); // Move down X lines;
	printf("\033[XC"); // Move right X column;
	printf("\033[XD"); // Move left X column;
	}
	
	void printColor(){
		
	}
// END

//LOGIN/REGISTER
	struct node{
		int *key;
		char username[21];
		char password[21];
		int score;
		int cleared_row;
		int total_block;
		node *next;
	}*head[27] = {NULL};

	struct node *newNode(char *username, char *password, int score, int cleared_row, int total_block){
		struct node *tmp = (struct node*)malloc(sizeof(struct node));
		tmp->next = NULL;
		strcpy(tmp->username, username);
		strcpy(tmp->password, password);
		tmp->score = score;
		tmp->cleared_row = cleared_row;
		tmp->total_block = total_block;		
		return tmp;		
	}
	
	// if username start with symbol, key = 26
	int hash_division(char *username){
	    if(username[0]<65) return 26;
	    return tolower(username[0])%27;
	}
	// Insert linked list;
	
	void pushHead(char *username, char *password, int score, int cleared_row, int total_block){
	    struct node *tmp = newNode(username, password, score, cleared_row, total_block);
	    int i = hash_division(username);
	    
	    if(head[i] == NULL){
	        head[i] = tmp;
	        return;
	    }else{
	        tmp->next = head[i];
	        head[i] = tmp;
	        return;
	    }
	}
		
	void pushTail(char *username, char *password, int score, int cleared_row, int total_block){
	    struct node *tmp = newNode(username, password, score, cleared_row, total_block);
	    int i = hash_division(username);
	    
		if(head[i]==NULL){
	        head[i] = tmp;
	        return;
	    }else{
	    	struct node *curr = head[i];
	    	while(curr->next!= NULL){
	    		curr = curr->next;
			}
	        curr->next = tmp;
	        return;
	    }
	}	
	
	void pushMid(char *username, char *password, int score, int cleared_row, int total_block){
	    int i = hash_division(username);
	    struct node *tmp = newNode(username, password, score, cleared_row, total_block);
	    
	    if(head[i]==NULL){
	    	head[i] = tmp;
		}
	    
	    // menentukan tail
	    struct node *tail = head[i];
	    while(tail->next != NULL){
	    	tail = tail->next;
		}
	    //urut sesuai score secara decending
		if(score >= head[i]->score){
			pushHead(username, password, score, cleared_row, total_block);
			return;
		}else if(score<tail->score){
			pushTail(username, password, score, cleared_row, total_block);
			return;
		}else{
			struct node *curr = head[i];
			struct node *curr2 = head[i];
			while(curr->score > score){
				curr = curr->next;
				if(curr->next->score > score) curr2->score;
			}
			curr2->next = tmp;
			tmp->next = curr;
		}
	}
	
	// read player's data di "user.txt"
	void readPlayersData(){
		FILE *file_read = fopen("user.txt","r");
		if (file_read ==NULL){
			printf("File not opended!\n");
			return;
		}
		
		char username[21], password[21];
		int score, cleared_row, total_block;
		
		while(feof(file_read)){
			fscanf(file_read, "%s,%s,%d,%d,%d\n", username, password, &score, &cleared_row, &total_block);
			pushMid(username, password, score, cleared_row, total_block);
		}
	}

	bool valUsername(username){
		int len = strlen(username);
		bool flag = true;
		for(int i = 0; i<len;i++){
			if(username[i] == ' ') return 0;
			if(username[i] == '.'||username[i]=='-'||username[i]=='_'){
				continue
			}else{
				return 0
			}
		}
		return 1;
	}

	void inputUserData(){
		printf("")
	}

// END


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



	void printHomePage(){
	    puts("\n ___  _________     _____  _____  _____ ______  _____  _____");
	    puts(" |  \\/  || ___ \\   |_   _||  ___||_   _|| ___ \\|_   _|/  ___|");
	    puts(" | .  . || |_/ /     | |  | |__    | |  | |_/ /  | |  \\ `--.");
	    puts(" | |\\/| ||    /      | |  |  __|   | |  |    /   | |   `--. \\");
	    puts(" | |  | || |\\ \\  _   | |  | |___   | |  | |\\ \\  _| |_ /\\__/ /");
	    puts(" \\_|  |_/\\_| \\_|(_)  \\_/  \\____/   \\_/  \\_| \\_| \\___/ \\____/");
	    printf("\n\n 1. Play\n 2. View User\n 3. Exit\n >> ");
	
	}




void menu_1(){
	
	// pre-game
		// input username
			// if "Admin", masuk admin page;
			// if "0", back to home page;
			// validate text, 
				// x empty
				// length 4-20
				// special character only "."(titik), "-"(dash), "_"(underscore).
				// jika tidak sesuai aturan,  berikan peringatan apa saja yang semestinya dibenarkan.
			// validate is username already exist, jika ya, tanya apakah mau login, jika tidak tanya apakah mau register.
				// jika tidak menekan "Y" maka akan balik ke home page
				// jika ya lanjut ke menu password
	// 
	
}


int main(){
	while(1){
	    system("cls");
	    printHomePage();
	    
	    int menu = 0;
	    scanf("%d", &menu);
	    switch (menu){
	    case 1:{
	    	
			break;
		}
	    case 2:{
	    	
			break;
		}
	    case 3:{
			break;
		}
	    default:
	        break;
	    }
	}
}
