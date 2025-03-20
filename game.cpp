#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>

const int sizeMapX = 11, sizeMapY = 11;
char map[sizeMapX][sizeMapY] = {
    {"##########"},
    {"##########"},
    {"##########"},
    {"##########"},
    {"##########"},
    {"##########"},
    {"##########"},
    {"##########"},
    {"##########"},
    {"##########"},
};

void displayMap(){
    for (int i = 0; i < sizeMapX; i++)
    {
        for (int j = 0; j < sizeMapY;  j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}


void gameMenu(){
    char key;
    int x = 0, y = 0;
    bool stop = 0;
    while(1){
        char buff = map[x][y];
        int oldX = x, oldY = y;
        if (kbhit()){
            key = tolower(getch());
            
            switch (key)
            {
            case 's':
                if(x!= sizeMapX) x++;
                break;
            case 'w':
                if(x!= 0)x--;
                break;
            case 'd':
                if(y!= sizeMapY)y++;
                break;
            case 'a':
                if(x!= 0)y--;
                break;
            case '0':
                stop = 1;
                break;
            default:
                break;
            }
            if(oldX == x&&oldY == y){

            }
            map[x][y] = 'p';
            printf("\e[1;1H\e[2J");
            displayMap();
            printf("\n<%d, %d>\n", x, y);
        }   
        if (stop) break;        
    }
}

int main(){
    displayMap();
    gameMenu();

    return 0;
}