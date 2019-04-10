#include "primlib.h"
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_TOWERS 3
#define NUMBER_OF_CIRCLES 4

const int CHEIGHT = (150+NUMBER_OF_CIRCLES*3)/NUMBER_OF_CIRCLES;
int CINTERVAL;

enum color Color[] = {RED, GREEN, BLUE, CYAN, YELLOW};
int FindBestInterval(int, int);
void DrawPlatform(int, int);
void StartGame(int, int, int[][NUMBER_OF_CIRCLES]);
void MoveCircle(int, int, int, int, int[][NUMBER_OF_CIRCLES]);
int CheckWin(int, int, int[][NUMBER_OF_CIRCLES]);
void WinScreen(void);

    char Moves1=' ';
    char Moves2=' ';
    char Moves3='0';

int main(int argc, char* argv[])
{
    
    CINTERVAL = FindBestInterval(NUMBER_OF_TOWERS, NUMBER_OF_CIRCLES);
    
    int TowerArray[NUMBER_OF_TOWERS][NUMBER_OF_CIRCLES];
    
	if(initGraph())
	{
		exit(3);
	}
	/* clear screen */ 
        filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);
        
        if(NUMBER_OF_TOWERS<=10) DrawPlatform(NUMBER_OF_TOWERS, NUMBER_OF_CIRCLES);
            else 	
            {
                printf("Too big value entered.");
                DrawPlatform(3, NUMBER_OF_CIRCLES);
                
            }
            
        StartGame(NUMBER_OF_CIRCLES, NUMBER_OF_TOWERS, TowerArray);
        
        textout(screenWidth()/2-45, 20,"TOWER OF HANOI",YELLOW);
        
        char MovesText[] = {'M', 'o', 'v', 'e', 's', ':', ' ', Moves1 , Moves2, Moves3, '\0'};
        
        textout(30, 20, MovesText, WHITE);
        
        int i;
        int j;
        int MoveFrom, MoveTo;
        updateScreen();
        do{
        for(i=0;i<NUMBER_OF_CIRCLES;i++)
        {
            for(j=0;j<NUMBER_OF_TOWERS;j++)
            {
                printf("%d..Tower: %d | ",j+1,TowerArray[j][i]);
            }
            printf("\n");
        }
        printf("-----------------------\n");
        MoveFrom = getkey()-48;
        MoveTo = getkey()-48;
        if(MoveFrom-1==-1)
        {
            MoveFrom=10;
        }
        if(MoveTo-1==-1)
        {
            MoveTo=10;
        }

        if((MoveFrom>=0 && MoveFrom<=NUMBER_OF_TOWERS) && (MoveTo>=0 && MoveTo<=NUMBER_OF_TOWERS))
        {
        MoveCircle(MoveFrom-1, MoveTo-1, NUMBER_OF_CIRCLES, NUMBER_OF_TOWERS, TowerArray);
        }
        printf("\n\n %d ---> %d \n",MoveFrom, MoveTo);
        if(CheckWin(NUMBER_OF_CIRCLES, NUMBER_OF_TOWERS, TowerArray)==1)
        {
            WinScreen();
            break;
        }
        }while(1);
	//updateScreen();
	//getkey();
	return 0;
}

int FindBestInterval(int NumberOfTowers, int NumberOfCircles)
{
    int Interval;
    int Difference=0;
    switch(NumberOfTowers)
    {
        case 4:
        {
            Difference=5;
            break;
        }
        case 5:
        {
            Difference=8;
            break;
        }
        case 6:
        {
            Difference=10;
            break;
        }
        case 7:
        {
            Difference=12;
            break;
        }
        case 8: case 9: case 10:
        {
            Difference=15;
            break;
        }
        default:
        {
            break;
        }
    }
    
            if(NumberOfCircles>40) Interval=1;
            else if(NumberOfCircles>30) Interval=2-Difference;
            else if(NumberOfCircles>22) Interval=3-Difference;
            else if(NumberOfCircles>16) Interval=5-Difference;
            else if(NumberOfCircles>10) Interval=8-Difference;
            else if(NumberOfCircles>8) Interval=13-Difference;
            else if(NumberOfCircles>6) Interval=15-Difference;
            else if(NumberOfCircles>5) Interval=20-Difference;
            else if(NumberOfCircles>4) Interval=25-Difference;
            else Interval=35-Difference;

        if(Interval<1) Interval=1;

    
    return Interval;
    
}

void DrawPlatform(int NumberOfTowers, int NumberOfCircles)
{
	int CurrentTower;
        
	for(CurrentTower = 1; CurrentTower<=NumberOfTowers; CurrentTower++)
        {
	filledRect(screenWidth()/(NumberOfTowers+1)*CurrentTower, 
                   screenHeight() - 1 - 10, 
                   screenWidth()/(NumberOfTowers+1)*CurrentTower+5, 
                   screenHeight() - 1 - (NumberOfCircles*(CHEIGHT+2)+10), 
                   MAGENTA);	
        }

	filledRect(0, screenHeight() - 1 - 10 + 1, screenWidth() - 1, screenHeight() - 1, MAGENTA);
}

void StartGame(int NumberOfCircles, int NumberOfTowers, int TowerArr[][NumberOfCircles])
{
    int CurrentCircle;
    int CurrentColor;
    int CurrentTower;

    for(CurrentCircle=NumberOfCircles; CurrentCircle>0; CurrentCircle--)
    {
        TowerArr[0][CurrentCircle-1]=NumberOfCircles-CurrentCircle+1;
    }

    for(CurrentTower=1;CurrentTower<NumberOfTowers;CurrentTower++)
    {
        for(CurrentCircle=NumberOfCircles; CurrentCircle>0; CurrentCircle--)
        {
            TowerArr[CurrentTower][CurrentCircle-1]=0;
        }
    }
    

for(CurrentCircle=1, CurrentColor=0; CurrentCircle<=NumberOfCircles; CurrentCircle++, CurrentColor++)
    {
        filledRect(screenWidth()/(NumberOfTowers+1)-((NumberOfCircles*CINTERVAL+10)-CurrentCircle*CINTERVAL)+4, 
                   screenHeight() - 1 - 10 - ((CHEIGHT+1)*CurrentCircle) + CHEIGHT, 
                   screenWidth()/(NumberOfTowers+1)+((NumberOfCircles*CINTERVAL+10)-CurrentCircle*CINTERVAL), 
                   screenHeight() - 1 - 10 - ((CHEIGHT+1)*CurrentCircle), 
                   Color[CurrentColor%5]);
    }
    
for(CurrentCircle=1, CurrentColor=0; CurrentCircle<=NumberOfCircles; CurrentCircle++, CurrentColor++)
    {
        rect(screenWidth()/(NumberOfTowers+1)-((NumberOfCircles*CINTERVAL+10)-CurrentCircle*CINTERVAL)+4, 
                   screenHeight() - 1 - 10 - ((CHEIGHT+1)*CurrentCircle) + CHEIGHT, 
                   screenWidth()/(NumberOfTowers+1)+((NumberOfCircles*CINTERVAL+10)-CurrentCircle*CINTERVAL), 
                   screenHeight() - 1 - 10 - ((CHEIGHT+1)*CurrentCircle), 
                   BLACK);
    }
}

void MoveCircle(int FromTower, int ToTower, int NumberOfCircles, int NumberOfTowers, int TowerArr[][NumberOfCircles])
{
    char MovesText[] = {'M', 'o', 'v', 'e', 's', ':', ' ', Moves1 , Moves2, Moves3, '\0'};
    
    int FromTowerID = 0, ToTowerID = 0;
    int CurrentCircle;
    for(CurrentCircle=0; CurrentCircle<NumberOfCircles; CurrentCircle++)
    {
        if(TowerArr[FromTower][CurrentCircle] != 0)
            FromTowerID=CurrentCircle;
    }
    printf("\nTower %d FromTowerID = %d\n", FromTower, FromTowerID);
    for(CurrentCircle=0; CurrentCircle<NumberOfCircles; CurrentCircle++)
    {
        if(TowerArr[ToTower][CurrentCircle] != 0)
            ToTowerID=CurrentCircle+1;
    }
    printf("Tower %d ToTowerID = %d\n", ToTower, ToTowerID);

    if((TowerArr[ToTower][ToTowerID]==0 && (ToTowerID-1) != -1 && TowerArr[FromTower][FromTowerID]<TowerArr[ToTower][ToTowerID-1]) || ToTowerID==0)
    {
        if(ToTower!=FromTower && (TowerArr[ToTower][ToTowerID]+TowerArr[FromTower][FromTowerID]!=0))
        {
        //MOVES COUNT START
        textout(30, 20,MovesText,BLACK);
        Moves3++;
        if(Moves3=='9'+1)
        {
            if(Moves2==' ') Moves2='1';
            else Moves2++;
        Moves3='0';
        }
        if(Moves2=='9'+1)
        {
            if(Moves1==' ') Moves1='1';
            else Moves1++;
        Moves2='0';
        }
        MovesText[9] = Moves3;
        MovesText[8] = Moves2;
        MovesText[7] = Moves1;
        textout(30, 20,MovesText,WHITE);
        updateScreen();
        //MOVES COUNT STOP

        TowerArr[ToTower][ToTowerID] = TowerArr[FromTower][FromTowerID];
        TowerArr[FromTower][FromTowerID] = 0;
        printf("Changed!\n");
        
        //---------------ANIMATION
    int CirclesOnFromTower=1, CirclesOnToTower=0;
    int CurrentCircle;
    for(CurrentCircle=0; CurrentCircle<NumberOfCircles; CurrentCircle++)
    {
        if(TowerArr[FromTower][CurrentCircle] != 0) CirclesOnFromTower++;
    }
    for(CurrentCircle=0; CurrentCircle<NumberOfCircles; CurrentCircle++)
    {
        if(TowerArr[ToTower][CurrentCircle] != 0) CirclesOnToTower++;
    }

    int Movement;
    
    for(Movement=0; screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnFromTower) - Movement > 30; Movement=Movement+2)
    {
        filledRect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4, 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnFromTower) + CHEIGHT - Movement, 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL), 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnFromTower) - Movement, 
               Color[((NumberOfCircles-TowerArr[ToTower][ToTowerID]))%5]);
        
        rect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4, 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnFromTower) + CHEIGHT - Movement, 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL), 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnFromTower) - Movement, 
               BLACK);
        
        updateScreen();
        SDL_Delay(1);
        filledRect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4, 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnFromTower) + CHEIGHT - Movement, 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL), 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnFromTower) - Movement, 
               BLACK);
        updateScreen();
        
        filledRect(screenWidth()/(NumberOfTowers+1)*(FromTower+1), 
                   screenHeight() - 1 - 10 - (CHEIGHT * (CirclesOnFromTower-1) + CirclesOnFromTower), 
                   screenWidth()/(NumberOfTowers+1)*(FromTower+1)+5, 
                   screenHeight() - 1 - (NumberOfCircles*(CHEIGHT+2)+10), 
                   MAGENTA);	
        
    }
    // to right 
    if(FromTower<ToTower)
    {
    for(Movement=0; screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4 + Movement < screenWidth()/(NumberOfTowers+1)*(ToTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4; Movement=Movement+2)
    {
        filledRect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4 + Movement, 
               (30+CHEIGHT), 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL) + Movement, 
               30, 
               Color[((NumberOfCircles-TowerArr[ToTower][ToTowerID]))%5]);
        
        rect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4 + Movement, 
               (30+CHEIGHT), 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL) + Movement, 
               30, 
               BLACK);
        
        updateScreen();
        SDL_Delay(1);
        filledRect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4 + Movement, 
               (30+CHEIGHT), 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL) + Movement, 
               30, 
               BLACK);
        updateScreen();
    }
    }
    // to left
    else
    {
        for(Movement=0; screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4 - Movement > screenWidth()/(NumberOfTowers+1)*(ToTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4; Movement=Movement+2)
    {
        filledRect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4 - Movement, 
               (30+CHEIGHT), 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL) - Movement, 
               30, 
               Color[((NumberOfCircles-TowerArr[ToTower][ToTowerID]))%5]);
        
        rect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4 - Movement, 
               (30+CHEIGHT), 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL) - Movement, 
               30, 
               BLACK);
        
        updateScreen();
        SDL_Delay(1);
        filledRect(screenWidth()/(NumberOfTowers+1)*(FromTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4 - Movement, 
               (30+CHEIGHT), 
               screenWidth()/(NumberOfTowers+1)*(FromTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL) - Movement, 
               30, 
               BLACK);
        updateScreen();
    }
    }
    
    for(Movement=0; (30+CHEIGHT) + Movement < screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnToTower) + CHEIGHT; Movement=Movement+2)
    {
        filledRect(screenWidth()/(NumberOfTowers+1)*(ToTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4, 
               (30+CHEIGHT) + Movement, 
               screenWidth()/(NumberOfTowers+1)*(ToTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL), 
               30 + Movement, 
               Color[((NumberOfCircles-TowerArr[ToTower][ToTowerID]))%5]);
        
        rect(screenWidth()/(NumberOfTowers+1)*(ToTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4, 
               (30+CHEIGHT) + Movement, 
               screenWidth()/(NumberOfTowers+1)*(ToTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL), 
               30 + Movement, 
               BLACK);
        
        updateScreen();
        SDL_Delay(1);
        filledRect(screenWidth()/(NumberOfTowers+1)*(ToTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4, 
               (30+CHEIGHT) + Movement, 
               screenWidth()/(NumberOfTowers+1)*(ToTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL), 
               30 + Movement, 
               BLACK);
        updateScreen();
        
        filledRect(screenWidth()/(NumberOfTowers+1)*(ToTower+1), 
                   screenHeight() - 1 - 10 - (CHEIGHT * (CirclesOnToTower-1) + CirclesOnToTower), 
                   screenWidth()/(NumberOfTowers+1)*(ToTower+1)+5, 
                   screenHeight() - 1 - (NumberOfCircles*(CHEIGHT+2)+10), 
                   MAGENTA);	
        
    }
    
    filledRect(screenWidth()/(NumberOfTowers+1)*(ToTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4, 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnToTower) + CHEIGHT, 
               screenWidth()/(NumberOfTowers+1)*(ToTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL), 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnToTower), 
               Color[((NumberOfCircles-TowerArr[ToTower][ToTowerID]))%5]);
    
    rect(screenWidth()/(NumberOfTowers+1)*(ToTower+1)-((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL)+4, 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnToTower) + CHEIGHT, 
               screenWidth()/(NumberOfTowers+1)*(ToTower+1)+((NumberOfCircles*CINTERVAL+10)-(NumberOfCircles-TowerArr[ToTower][ToTowerID]+1)*CINTERVAL), 
               screenHeight() - 1 - 10 - ((CHEIGHT+1)*CirclesOnToTower), 
               BLACK);

    updateScreen();
        //---------------
        }
    }
}

int CheckWin(int NumberOfCircles, int NumberOfTowers, int TowerArr[][NUMBER_OF_CIRCLES])
{
    int Win = 0;
    int CurrentCircle;
    for(CurrentCircle=NumberOfCircles; CurrentCircle>0; CurrentCircle--)
    {
        printf("\n %d = %d \n", TowerArr[NumberOfTowers-1][CurrentCircle-1], NumberOfCircles-CurrentCircle+1);
        if(TowerArr[NumberOfTowers-1][CurrentCircle-1]==NumberOfCircles-CurrentCircle+1)
            Win = 1;
        else
        {
            Win = 0;
            break;
        }
    }
    return Win;
}

void WinScreen(void)
{
    //1300x480
    int CoordX, CoordY;
    int GoQuit=0;
    SDL_Delay(1000);
    SDL_Event ButtonPressed;
    srand(time(NULL));
    do{
        filledRect(0, 0, screenWidth() - 1, screenHeight() - 1, BLACK);
        CoordX=rand()%900+50;
        CoordY=rand()%400+50;
        textout(CoordX, CoordY,"YOU WON!!!", RED); 
        textout(20,20,"Press ESC to quit.", CYAN);
        updateScreen();
        SDL_Delay(1000);
        while(SDL_PollEvent(&ButtonPressed))
        {
            if(ButtonPressed.type == SDL_QUIT || ButtonPressed.key.keysym.sym == SDLK_ESCAPE)
            {
                GoQuit=1;
                break;
            }

        }

    }while(GoQuit==0);

}


