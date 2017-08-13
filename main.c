/* 
 * File:   main.c
 * Author: Andrey Obogrelov
 *
 * Created on 31 марта 2017 г., 0:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char fieldDot='*';
char userDot='X';
char compDot='O';
char battleField[3][3];

void clearField()
{
       for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            battleField[i][j]=fieldDot;
        }
    }
}

void printField()
{
     for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf("%c ",battleField[i][j]);
        }
        printf("\n");
    }
     printf("\n");
}

int checkFieldForTurn(int q, int w) //проверить клетку на занятость
{
    if (battleField[q-1][w-1] == fieldDot ) 
    {
        return 1;
    }
    else
    {
         return 0;
    }
}

int isThereEmptyCell()
{
    int oneMore=0;
    for (int x=0;x<3;x++)
        for(int y=0; y<3; y++)
        {
            if (battleField[x][y] == fieldDot)
                oneMore++; 
        }
    if (oneMore>0)
        return 1;
    else return 0;
}

int checkForWin(char *a)
{
    int win;
    for (int x=0;x<3;x++)
        for(int y=0, win=0; y<3; y++)
        {
            if (battleField[x][y]==*a)
                win++;
            if (win==3)
                return 1;        
        }
    
    
    for (int y=0;y<3;y++)
        for(int x=0, win=0; x<3; x++)
        {
            if (battleField[x][y]==*a)
                win++;
            if (win==3)
                return 1;        
        }
        
    for (int x=0, y=0, win=0; x < 3; x++, y++) 
    {
        if (battleField[x][y]==*a)
            win++;
        if (win==3)
            return 1;
    }    
        
    for (int x=2, y=0, win=0; y <3; x--, y++) 
    {
        if (battleField[x][y]==*a)
            win++;
        if (win==3)
            return 1;
    }
    return 0;

}

int playerTurn()
{
    int q;
    int w;
    printf("enter your turn with two digits\n");
    scanf("%i",&q);
    scanf("%i",&w);
    if (checkFieldForTurn(q,w)== 1)
    {    
        battleField[q-1][w-1]=userDot;
    }
    else 
    {
        printf("you can use it? use another one !\n");
        playerTurn();
    }
    printField();
   
}

int aiTurn()
{
    int al, ac;
        
    al = rand() % 3 +1;  //line
    ac = rand() % 3 +1 ; //colomuns   
    
    if (checkFieldForTurn(al,ac)== 1)
    {    
        battleField[al-1][ac-1]=compDot;
    }
    else 
    {
        aiTurn();
    }
    printField();  
    
}

void greetingPlayer()
{
    printf("Let`s play TicToc\n");
    clearField();
    printField();
    
}
void goodByePlayer()
{
printf("See you!\n");
}


int playGame()
{
    int non=0;
    while (isThereEmptyCell()!= 0)
    {
     playerTurn();
     non++;
     if (checkForWin(&userDot)==1)
    {
         printf("You WIN!\n");
        return 1;
    }
     if (non == 5)
     {
         printf("NO ONE WIN!\n");
         return 0;
     }
     
    aiTurn();
     if (checkForWin(&compDot)==1)
    {
        printf("AI WIN!\n");
        return 2;
    }
    }
    printf("NO ONE WIN!\n");
    return 0;
}


int playAgain()
{
    int repeat;
    printf("if you want play more press 1. If exit press 0\n");    
    scanf("%i", &repeat);
    return repeat;

}
void theGame()
{     
    greetingPlayer();
    playGame();
    while (playAgain()!=0)
    {
    greetingPlayer();
    playGame();
    }
    goodByePlayer();
    
}

int main(int argc, char** argv) {
    srand (time(NULL));
    theGame();     
    return (EXIT_SUCCESS);
}

