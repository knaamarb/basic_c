#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<ctype.h>
#include<wchar.h>
#include<math.h>
#include<locale.h>

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


const int TABLE_SIZE = 27;
const int sizeBalokX = 7,sizeBalokY = 7;
const int gmenuX = 56, gmenuY = 25;


// Console manipulation
	void moveCursor(int x, int y){
		int abs_x = abs(x), abs_y = abs(y);
		if(x<0)printf("\033[%dD", abs_x);
		if(y<0)printf("\033[%dA", abs_y);
		if(y>0)printf("\033[%dB", y);
		if(x>0)printf("\033[%dC", x);
		 //A Move up X lines;
		 //B Move down X lines;
		 //C Move right X column;
		 //D Move left X column;
	}
	void moveCursorto(int row, int col){
		printf("\033[%d;%dH", row, col);
	}
	
	void printColor(){
		
	}
// END

// Other Function

	void toLowerCase(char *str) {
	    while (*str) {
	        *str = tolower(*str);
	        str++;
	    }
	}
	
	void printf_c(const char str[]){
		int padding = (gmenuX - strlen(str))/2;
		for (int i = 0; i < padding; i++) {
        	printf(" ");
    	}
		printf("%s", str);
	}

//END


// Print Menu
	void printHeader(){
	    puts("\n ___  _________     _____  _____  _____ ______  _____  _____");
	    puts(" |  \\/  || ___ \\   |_   _||  ___||_   _|| ___ \\|_   _|/  ___|");
	    puts(" | .  . || |_/ /     | |  | |__    | |  | |_/ /  | |  \\ `--.");
	    puts(" | |\\/| ||    /      | |  |  __|   | |  |    /   | |   `--. \\");
	    puts(" | |  | || |\\ \\  _   | |  | |___   | |  | |\\ \\  _| |_ /\\__/ /");
	    puts(" \\_|  |_/\\_| \\_|(_)  \\_/  \\____/   \\_/  \\_| \\_| \\___/ \\____/");	
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
	}*head[TABLE_SIZE] = {NULL};

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
	    char tmp[21]; strcpy(tmp, username);
	    toLowerCase(tmp);
	    return (tmp[0]+11)%TABLE_SIZE;
	}
	// Insert linked list;
	
	void pushHead(char *username, char *password, int score, int cleared_row, int total_block){
	    struct node *tmp = newNode(username, password, score, cleared_row, total_block);
	    int i = hash_division(username);
	    
	    if(head[i] == NULL){
	        head[i] = tmp;
	        return;
	    }else{// collision control
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
			while(curr->next->score >= score){
				curr = curr->next;
			}
			curr2 = curr->next;
			curr->next = tmp;
			tmp->next = curr2;
		}
	}
	
	bool search(char *username){
		int i = hash_division(username);
		struct node *tmp = head[i];
		while(tmp != NULL){
			if(tmp->username == username){
				return 1;
			}else{
				tmp = tmp->next;
			}
		}
		return 0;
	}

	bool search_pass(char *username, char *password){
		int i = hash_division(username);
		struct node *tmp = head[i];
		while(tmp != NULL){
			if(tmp->username == username){
				
				if(strcmp(password, tmp->password) == 0){
					return 1;
				}else{
					return 0;
				}
			}else{
				tmp = tmp->next;
			}
		}
		return 0;

	}

	void printTable(){ // for debug
		for(int i = 0; i<TABLE_SIZE;i++){
			printf("%d : ", i);
			if(head[i]==NULL){
				printf("Line is Empty\n");
				continue;
			}
			struct node *curr = head[i];
			while(curr->next!=NULL){
				printf("%s %s -> ", curr->username, curr->password);
				curr = curr->next;
			}
			printf("\n");
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

	bool valUsername(char *username){
		int len = strlen(username);
		int validate = strspn(username, ".-_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
		if(validate<len){
			return 0;
		}
		return 1;
	}

	// void inputUserData(){
	// 	printf("");
	// }

// END

// Game Menu


	struct block{
		char block[sizeBalokY][sizeBalokX];
		struct block *next, *prev;
	}*bhead=NULL, *btail=NULL;
	
	struct block *newBlock(char block[sizeBalokY][sizeBalokX]){
		struct block *tmp = (struct block*)malloc(sizeof(struct block));
		tmp->next = NULL;
		tmp->prev = NULL;
		memcpy(tmp->block, block, sizeof(char) * sizeBalokX *sizeBalokY);
		return tmp;
	}
	

	void inHead(char block[sizeBalokY][sizeBalokX]) {
	    struct block* newNode = newBlock(block);
	    if (bhead == NULL) {
	        bhead = btail = newNode;
	        return;
	    }
	    bhead->prev = newNode;
	    newNode->next = bhead;
	    bhead = newNode;
	}
	
	
	void inTail(char block[sizeBalokY][sizeBalokX]) {
	    struct block* newNode = newBlock(block);
	    if (bhead == NULL) {
	        bhead = btail = newNode;
	        return;
	    }
	    btail->next = newNode;
	    newNode->prev = btail;
	    btail = newNode;
	}
	
	void printBlock(){ // for debug
	    struct block *tmp = bhead;
	    while(tmp!=NULL){
	
			for(int i = 0; i<sizeBalokY-1; i++){
				printf("%s\n", tmp->block[i]);
			}
			
	        if(tmp->next != NULL){
	        	printf(" \n\nNext block:\n");	
			}
	        tmp = tmp->next;
	    }
	}

	void importBlock(){
		FILE *file = fopen("block.txt", "r");
		char tmp[sizeBalokY][sizeBalokX];
		
		if(file == NULL){
			system("cls");
			printHeader();
			printf("\n\n");
			printf_c("Wait for Admin to add Block\n");
			printf_c("Press any key to continue...");
			while(1){
				if(kbhit())return;
			}	
		}
		
		while(!feof(file)){
			for(int i = 0, j= 0; i<sizeBalokY-1;i++, j++){
				fscanf(file, "%s\n", tmp[i]);
				if(tmp[i][0]=='='){
					fscanf(file, "=\n");
					break;
				}
				inTail(tmp);
			}
			/*
			for(int i = 0, j= 0; i<sizeBalokY-1;i++, j++){
				printf("\n%d: %s-%s", i,tmp[i], block[i]);
			}
			*/
		}
		fclose(file);
		return;
	}
	
	void printGame(){
		char menu[gmenuY][gmenuX] = {
			"\nScore                                       ==========",
			" ===========                                |  Next  |",
			" |       0 |                                ==========",
			" ===========                                |........|",
			"             |............................| |........|",
			" Clear Row   |............................| |........|",
			" =========== |............................| |........|",
			" |       0 | |............................| |........|",
			" =========== |............................| |........|",
			"             |............................| ==========",
			" Block       |............................|",
			" =========== |............................|  notes:",
			" |       0 | |............................| -----------",
			" =========== |............................| > Press 'p'",
			"             |............................|   to pause",
			" Controls:   |............................|   the game",
			"-----------  |............................| > Press 'l'",
			" 'a' left    |............................|   to move",
			" 'd' right   |............................|   the next",
			" 's' down    |............................|   Block",
			" 'w' rotate  |............................|",
			" ' ' hard    |............................|",
			" drop        =============================="
		};
		for(int i = 0; i< 22;i++){
			for(int j = 0; j<55;j++){
				printf("%c", menu[i][j]);
			}
			puts("");
		}
		
	}
	const int height_container1 = 18, width_container1 = 28, height_container2 = 6, width_container2 = 8, koorX_container1 = 4, koorY_container1 = 4;

	bool canMoveY(struct block *tmp, int x, int y, char board[18][28]) {
		// Check each column of the block
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 6; j++) {
				// Check if the block cell is filled
				if (tmp->block[j][i] == '#') {
					// Calculate the position on the board
					int boardX = x + i; // Column position
					int boardY = y + j + 1; // Row position below the block
					
					// Check if the position is within the board boundaries
					if (boardX < 0 || boardX >= width_container1 || boardY >= height_container1) {
						return false; // Out of bounds
					}
					
					// Check for obstruction
					if (boardY >= 0 && board[boardY][boardX] != '.') {
						return false; // There is an obstruction
					}
				}
			}
		}
		return true; // No obstructions below the block
	}

	
	// bool canMoveY(struct block *tmp, int x, int y){
	// 	for (int i = 0; i < 6; i++)
	// 	{
	// 		if(tmp->block[5][i] == '#'){
				
	// 		}
	// 		// for (int j = 0; j < 6; j++)
	// 		// {
				
	// 		// }
			
	// 	}
		
	// 	return true;
	// }

	void rotate(){

	}
	
	void print_container1(int height_container1, int width_container1, int koorX_container1, int koorY_container1, int relativeX, int relativeY){
		const int speed = 1000;
		char key;
		char container1[18][28];
		memset(container1, '.', sizeof(container1));
		int pX = (width_container1 - 6)/2, pY = koorY_container1;
		struct block *curr = bhead;
		while(curr!=NULL){
			do{
				for (int i = 0; i < 6; i++)
				{
					for (int j = 0; j < 6; j++)
					{
						if(curr->block[i][j]=='#'){
							moveCursorto(pY,pX);
							printf("%c", curr->block[i][j]);
						}
					}
					printf("\n");
					
				}
				if(kbhit()){
					key = getch();
					switch (tolower(key)) {
						case 'a': // Move left
							if (canMoveY(curr, pX - 1, pY, container1)) {
								pX--;
							}
							break;
						case 'd': // Move right
							if (canMoveY(curr, pX + 1, pY, container1)) {
								pX++;
							}
							break;
						case 's': // Move down
							if (canMoveY(curr, pX, pY + 1, container1)) {
								pY++;
							}
							break;
						case 'w': // Rotate (implement rotation logic)
							// Rotate the block (not implemented here)
							break;
						default:
							break;
					}
				}
				
				if (canMoveY(curr, pX, pY + 1, container1)) {
					pY++; // Move down if possible
				} else {
					// Place the block on the board
					for (int i = 0; i < 6; i++) {
						for (int j = 0; j < 6; j++) {
							if (curr->block[i][j] == '#') {
								container1[pY + i][pX + j] = '#'; // Place block on the board
							}
						}
					}
					break; // Exit the loop to get the next block
				}

				Sleep(950);
			}while (1);
			//canMoveY(curr, pX, pY, container1)

			curr = curr->next;
		}
	}
	
	
	void game_page(){
		int koorX_block, koorY_block;
		importBlock();
		printGame();

	}
	
	
// END

// Login/Register

void validateNewPass(char *pass, int i, bool *length, bool *hasUpper, bool *hasLower, bool *hasSym){
    int len = i;
    *length = false;
    *hasUpper = false;
    *hasLower = false;
    *hasSym  = false;
    if(len > 8 && len < 24) *length = true;
    for(int i = 0;i<len;i++){
        if(isupper(pass[i])) *hasUpper = true;
        if(islower(pass[i])) *hasLower = true;
        if(pass[i] < 65 && pass[i] > 32) *hasSym = true;
    }
}

void printCheck(bool length, bool hasUpper, bool hasLower, bool hasSym){
	if(length){
		moveCursorto(15,15);
		printf("V");				
	}else{
		moveCursorto(15,15);
		printf(" ");
	}
	if(hasUpper){
		moveCursorto(16,15);
		printf("V");				
	}else{
		moveCursorto(16,15);
		printf(" ");
	}			
	if(hasLower){
		moveCursorto(17,15);
		printf("V");				
	}else{
		moveCursorto(17,15);
		printf(" ");
	}			
	if(hasSym){
		moveCursorto(18,15);
		printf("V");				
	}else{
		moveCursorto(18,15);
		printf(" ");
	}
}

void regis(char *username, bool *continue_game){
	system("cls");
	printHeader();
	printf("\n\n");
	printf_c("Password: ('0' to back)\n");
	printf_c("--------------------------\n\n");
	printf_c("--------------------------\n\n");
	printf("             [ ] Length 8-24 (inclusive)\n");
	printf("             [ ] contains upper case character\n");
	printf("             [ ] contains lower case character\n");
	printf("             [ ] contains symbol or numeric character\n");
	
	int index = 0, px = 15,py = 12; 
	bool length, hasupper, haslower, hassym;
	char key;
	char pass[25];
	moveCursorto(py,px);
	while(1){
		if(kbhit()){
			key = getch();
			if(key == '\n'||key == '\r'){
				if(pass[index-1]=='0')break;
				if(length && hasupper && haslower && hassym){
					*continue_game=true;
					break;
				}
				pass[index] = '\0';
			} else if((key == 127) || (key == 8)){
				if(px==15)continue;
				moveCursor(-1,0);
				printf(" ");
				moveCursor(-1,0);
				px--;
				pass[index] = '\0';
				index--;
			}else if(index<=24){
				pass[index] = key;
				printf("*");
				px++;
				index++;
			}else{
				continue;
			}
			validateNewPass(pass, index, &length, &hasupper, &haslower, &hassym);
			printCheck(length, hasupper, haslower, hassym);
			moveCursorto(py,px);
		}

		
		Sleep(10);
	}

	pushTail(username, pass, 0, 0, 0);
}

void login(char *username, bool *continue_game){
	system("cls");
	printHeader();
	printf("\n\n");
	printf_c("Password: ('0' to back)\n");
	printf_c("--------------------------\n\n");
	printf_c("--------------------------\n\n");
	moveCursorto(12,15);
	char pass[25];
	do
	{
		scanf("%s",pass);
		if(strcmp(pass,"0")==0)return;
	} while (search_pass(username, pass));

	while(1){
		scanf("%s",pass);
		if(strcmp(pass,"0")==0)return;
		if(search_pass(username, pass)) *continue_game = true;
	}
	
}
// END

void menu_1(){
	
	// pre-game
		// input username
	system("cls");
	printHeader();	
	printf("\n\n\n\n                 Username: ('0' to back)\n");
	printf("                --------------------------\n\n");
	printf("                --------------------------");
	// moveCursor(-25,-1);
	// printf("\033[%d;%dH", 16, 16);
	char username[101];
	do
	{
		moveCursorto(14,17);
		scanf("%[^\n]",username); getchar();
		if(strcmp(username, "Admin") == 0){ // if "Admin", masuk admin page;
			// admin page
			printf("Admin page");
			Sleep(10000);
			return;
				
		}
		if(strcmp(username, "0") == 0){ // if "0", back to home page;
			return;
		}
		if(search(username)){
			moveCursorto(14,0);
			printf_c("User already registered! Want to login [Y]? ");
			char tmp[12];
			scanf("%c", tmp);
			if(strcmp(tmp, "Y")){
				bool continue_game = false;
				login(username, &continue_game);
				if(continue_game){
					game_page();
				}else{
					return;
				}
			}
			return;
		}
		if(valUsername(username)){
			system("cls");
			printHeader();
			moveCursorto(14,2);
			printf_c("Register new user! Want to Register [Y]? ");
			char tmp;
			scanf("%c", &tmp);
			if(tmp == 'Y'){
				bool continue_game = false;
				regis(username, &continue_game);
				if(continue_game){
					game_page();
				}else{
					return;
				}
			}
			return;
		}
		moveCursorto(14,17);
		printf("                         ");
		moveCursorto(17, 8);
		printf("*username must only alphanumeric, '.', '-', and '_' character");
	} while(!valUsername(username));
	

	printf("udah bener bro !!!");	
		
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

	int menu = 0;
	while(menu!=3){
	    // game_menu();
		system("cls");
	    printHeader();
	    printf("\n\n 1. Play\n 2. View User\n 3. Exit\n >> ");
	    
	    scanf("%d", &menu);getchar();
	    switch (menu){
	    case 1:{
			menu_1();
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
