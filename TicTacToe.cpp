#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <windows.h>

#define startX 1
#define startY 1
#define TurnWait 1                 // how many seconds computer waits to move
#define ExitWaitPerDot 0.5
#define ExitNoOfDots 5

using namespace std ;

const char PLAYER = 'x' ;
const char COMP = 'o' ;
const char P1 = 'x' ;
const char P2 = 'o' ;
const char VERTICAL = '|' ;
const char HORIZONTAL = '-' ;
const char INTERSECTION = '+' ;

int ctr;          		// Global counter

char pos[9] ;
int any_player[9] ;
int p1[9], p2[9];

int type = 0 ;			// 1-> one player vs computer
						// 2-> two players
int start = 0 ;			// 1-> player/player1 starts
						// 2-> computer/player2 starts
enum difficulty {easy=1,medium,hard} ;
				// Hard not available right now


//List of function prototypes
void Intro(void);
void RunGame(int); 			// not completed logically
void PrintBoard(void);
void Result(int,int);
void ContGame(void);
void TellExiting(void);


void Intro()
{
    system("CLS");
    srand( (unsigned)time(0) ) ;
    for (ctr=0; ctr<9; ctr++)
    {	
		pos[ctr] = ' ';
		any_player[ctr] = 0 ;
		p1[ctr] = 0 ;
		p2[ctr] = 0 ;
    }
    cout<<"\nTic Tac Toe\n\n"
		<<"Enter 1 for single player (against computer) and 2 for "
		<<"multiplayer (two players against each other)\n\n" ;
    cin>>type ;
    while (type!=1 && type!=2)
    {   
		cout<<"Wrong choice ! Re enter . . .   ";
		cin>>type;
    }
    RunGame(type);
}

void RunGame(int type)
{
    int turn = 1, winner=0, move ;
    bool over = false, flag = false ;
    difficulty dl;
    char level[6] ;
    if (type==1)
    {
		cout<<"\nNow enter the difficulty level :\n\n\tEasy\t\tMedium\t\tHard\n\n\t" ;
		gets(level) ;
		while ( !(strcmpi(level,"easy")==0 || strcmpi(level,"medium")==0) )
		{	
			while ( strcmpi(level,"Easy") && strcmpi(level,"Medium") && strcmpi(level,"Hard") )
			{	
				cout<<"\n\nWrong . . . Re enter      " ;
				gets(level) ;
			}
			while ( strcmpi(level,"Hard") == 0 )
			{   
				cout<<"\n\nThis option is not available right now, but "
					<<"will soon be updated\nMeanwhile, you can try "
					<<"the other two options\n\n"
					<<"Enter the difficulty level :\n\n"
					<<"\t\tEasy\t\tMedium\n\n\t" ;
			    gets(level) ;
			}
		}
		if ( strcmpi(level,"Easy") == 0 )
			dl = easy ;
		else if ( strcmpi(level,"Medium") == 0 )
			dl = medium ;
		else if ( strcmpi(level,"Hard") == 0 )
			dl = hard ;
		cout<<"\n\n\t"<<PLAYER<<" = Player,\t"<<COMP<<" = Computer\n\n"
		    <<"If you want to take the first turn, enter 1, and if "
		    <<"you want computer to take\nthe first chance, enter 2\n\n";
		cin>>start;
		while (start!=1 && start!=2)
		{   
			cout<<"\nInvalid.... enter again    ";
		    cin>>start;
		}
		turn = start;
		do
		{
		    flag = false ;
		    PrintBoard();
		    if (turn==1)
		    {	    
				cout<<"\n\n\tPlayer --> "<<PLAYER<<"\tComputer--> "<<COMP
					<<"\nIts your turn \n"
					<<"\nEnter the position in which you want to move (from 1 to 9)\n\n" ;
			    cin>>move;
			    while (move<1 || move>9)
			    {   
					cout<<"\nInvalid move .... enter again    ";
					cin>>move;
			    }
			    move--;
			    while (any_player[move]==1)
			    {	
					cout<<"Cannot move, already done at that position...\nEnter again      ";
					cin>>move;
					move--;
			    }
			    any_player[move] = 1;
			    pos[move] = PLAYER;
			    p1[move] = 1;
			    ++turn;
		    }
		    else if(turn==2)
		    {
				move=-1;
				while ( move<0 || move>8 || any_player[move]==1 )
					move = ( (rand()/100) % 9 ) ;
				if ( dl==medium )
				{
				    // to block the opponent
				    if (p1[0]&&p1[2]&&any_player[1]==0)	  move=1;
				    if (p1[0]&&p1[1]&&any_player[2]==0)   move=2;
				    if (p1[1]&&p1[2]&&any_player[0]==0)   move=0;
				    if (p1[3]&&p1[5]&&any_player[4]==0)   move=4;
				    if (p1[3]&&p1[4]&&any_player[5]==0)   move=5;
				    if (p1[4]&&p1[5]&&any_player[3]==0)   move=3;
				    if (p1[6]&&p1[7]&&any_player[8]==0)   move=8;
				    if (p1[6]&&p1[8]&&any_player[7]==0)   move=7;
				    if (p1[7]&&p1[8]&&any_player[6]==0)   move=6;
				    if (p1[0]&&p1[3]&&any_player[6]==0)   move=6;
				    if (p1[0]&&p1[6]&&any_player[3]==0)   move=3;
				    if (p1[3]&&p1[6]&&any_player[0]==0)   move=0;
				    if (p1[1]&&p1[4]&&any_player[7]==0)   move=7;
				    if (p1[1]&&p1[7]&&any_player[4]==0)   move=4;
				    if (p1[4]&&p1[7]&&any_player[1]==0)   move=1;
				    if (p1[2]&&p1[5]&&any_player[8]==0)   move=8;
				    if (p1[2]&&p1[8]&&any_player[5]==0)   move=5;
				    if (p1[5]&&p1[8]&&any_player[2]==0)   move=2;
				    if (p1[0]&&p1[4]&&any_player[8]==0)   move=8;
				    if (p1[0]&&p1[8]&&any_player[4]==0)   move=4;
				    if (p1[4]&&p1[8]&&any_player[0]==0)   move=0;
				    if (p1[2]&&p1[4]&&any_player[6]==0)   move=6;
				    if (p1[2]&&p1[6]&&any_player[4]==0)   move=4;
				    if (p1[4]&&p1[6]&&any_player[2]==0)   move=2;
		
				    // to win remaining block in row, column, or diagonal
				    if (p2[0]&&p2[2]&&any_player[1]==0)	  move=1;
				    if (p2[0]&&p2[1]&&any_player[2]==0)   move=2;
				    if (p2[1]&&p2[2]&&any_player[0]==0)   move=0;
				    if (p2[3]&&p2[5]&&any_player[4]==0)   move=4;
				    if (p2[3]&&p2[4]&&any_player[5]==0)   move=5;
				    if (p2[4]&&p2[5]&&any_player[3]==0)   move=3;
				    if (p2[6]&&p2[7]&&any_player[8]==0)   move=8;
				    if (p2[6]&&p2[8]&&any_player[7]==0)   move=7;
				    if (p2[7]&&p2[8]&&any_player[6]==0)   move=6;
				    if (p2[0]&&p2[3]&&any_player[6]==0)   move=6;
				    if (p2[0]&&p2[6]&&any_player[3]==0)   move=3;
				    if (p2[3]&&p2[6]&&any_player[0]==0)   move=0;
				    if (p2[1]&&p2[4]&&any_player[7]==0)   move=7;
				    if (p2[1]&&p2[7]&&any_player[4]==0)   move=4;
				    if (p2[4]&&p2[7]&&any_player[1]==0)   move=1;
				    if (p2[2]&&p2[5]&&any_player[8]==0)   move=8;
				    if (p2[2]&&p2[8]&&any_player[5]==0)   move=5;
				    if (p2[5]&&p2[8]&&any_player[2]==0)   move=2;
				    if (p2[0]&&p2[4]&&any_player[8]==0)   move=8;
				    if (p2[0]&&p2[8]&&any_player[4]==0)   move=4;
				    if (p2[4]&&p2[8]&&any_player[0]==0)   move=0;
				    if (p2[2]&&p2[4]&&any_player[6]==0)   move=6;
				    if (p2[2]&&p2[6]&&any_player[4]==0)   move=4;
				    if (p2[4]&&p2[6]&&any_player[2]==0)   move=2;
		
				}
				any_player[move] = 1 ;
				pos[move] = COMP;
				p2[move] = 1;
				--turn;
				Sleep(TurnWait*1000);
			}
			for (ctr=0; ctr<9; ctr++)
			{	
				if( any_player[ctr]==0 )
				{	
					flag = true;
					break;
				}
			}
		    if (!flag)
		    {	
				over = true;
				winner = 3 ;
		    }
		    if ( (p1[0]&&p1[1]&&p1[2]) || (p1[3]&&p1[4]&&p1[5]) )
				winner = 1;
		    else if ( (p1[6]&&p1[7]&&p1[8]) || (p1[0]&&p1[3]&&p1[6]) )
				winner = 1;
		    else if ( (p1[1]&&p1[4]&&p1[7]) || (p1[2]&&p1[5]&&p1[8]) )
				winner = 1;
		    else if ( (p1[0]&&p1[4]&&p1[8]) || (p1[2]&&p1[4]&&p1[6]) )
				winner = 1;
		    else if ( (p2[0]&&p2[1]&&p2[2]) || (p2[3]&&p2[4]&&p2[5]) )
				winner = 2;
		    else if ( (p2[6]&&p2[7]&&p2[8]) || (p2[0]&&p2[3]&&p2[6]) )
				winner = 2;
		    else if ( (p2[1]&&p2[4]&&p2[7]) || (p2[2]&&p2[5]&&p2[8]) )
				winner = 2;
		    else if ( (p2[0]&&p2[4]&&p2[8]) || (p2[2]&&p2[4]&&p2[6]) )
				winner = 2;
		}while (!over && !winner) ;  // note semicolon at the end of do-while
	
		Result(type,winner);
		ContGame();
	    }
    else									// type = 2 (two players)
    {
		cout<<"\n\n\t"<<P1<<" = Player 1,\t"<<P2<<" = Player 2\n\n"
		    <<"Which player should start? (1 or 2)    ";
		cin>>start;
//		turn = start;
		while (start!=1 && start!=2)
		{   cout<<"\nInvalid.... enter again    ";
		    cin>>start;
		}
		turn = start ;
		do
		{
		    flag = false ;
		    PrintBoard();
		    cout<<"\n\n\tPlayer 1 --> "<<P1<<"\tPlayer 2 --> "<<P2
				<<"\nIts player "<<turn<<"'s turn \n"
				<<"\nEnter the position in which you want to move (from 1 "
				<<"to 9)\n\n";
	    	cin>>move;
	    	while (move<1 || move>9)
	    	{   cout<<"\nInvalid move .... enter again    ";
				cin>>move;
	    	}
	    	move--;
	    	while (any_player[move]==1)
	    	{	cout<<"Cannot move, already done at that position...\n"
				    <<"Enter again      ";
				cin>>move;
				move--;
		    }
		    any_player[move] = 1;
		    if (turn==1)
		    {   pos[move] = P1;
				p1[move] = 1;
				++turn;
	    	}
	    	else if(turn==2)
	    	{   pos[move] = P2;
				p2[move] = 1;
				--turn;
	    	}
	    	for (ctr=0; ctr<9; ctr++)
	    	{	if( any_player[ctr]==0 )
				flag = true;
		    }
		    if (!flag)
		    {	over = true;
				winner = 3 ;
		    }
	    	if ( (p1[0]&&p1[1]&&p1[2]) || (p1[3]&&p1[4]&&p1[5]) )
				winner = 1;
	    	else if ( (p1[6]&&p1[7]&&p1[8]) || (p1[0]&&p1[3]&&p1[6]) )
				winner = 1;
	    	else if ( (p1[1]&&p1[4]&&p1[7]) || (p1[2]&&p1[5]&&p1[8]) )
				winner = 1;
	    	else if ( (p1[0]&&p1[4]&&p1[8]) || (p1[2]&&p1[4]&&p1[6]) )
				winner = 1;
	    	else if ( (p2[0]&&p2[1]&&p2[2]) || (p2[3]&&p2[4]&&p2[5]) )
				winner = 2;
	    	else if ( (p2[6]&&p2[7]&&p2[8]) || (p2[0]&&p2[3]&&p2[6]) )
				winner = 2;
	    	else if ( (p2[1]&&p2[4]&&p2[7]) || (p2[2]&&p2[5]&&p2[8]) )
				winner = 2;
	    	else if ( (p2[0]&&p2[4]&&p2[8]) || (p2[2]&&p2[4]&&p2[6]) )
				winner = 2;
		}while (!over && !winner) ;  // note semicolon at the end of do-while

		Result(type,winner);
		ContGame();
    }
}

void PrintBoard()
{
	system("CLS") ;
	int i,a=0 ;
	for (i=1; i<startY; i++)
		cout<<endl ;
	for (i=1; i<startX; i++)
		cout<<" " ;
	for (i=1; i<=11; i++)
	{
		if (i%2)
		{
			cout<<"   " ;
			cout<<VERTICAL ;
			cout<<"   " ;
			cout<<VERTICAL ;
		}
		if ( (i%2==0) && (i%4!=0) )
		{
			cout<<" " ;
			if ( any_player[a] == 0 )
				cout<<(a+1);
			else
				cout<<pos[a];
			a++ ;
			cout<<" "<<VERTICAL<<" " ;
			if ( any_player[a] == 0 )
				cout<<(a+1);
			else
				cout<<pos[a];
			a++ ;
			cout<<" "<<VERTICAL<<" " ;
			if ( any_player[a] == 0 )
				cout<<(a+1);
			else
				cout<<pos[a];
			a++ ;
		}
		if (i%4==0)
			for (int j=1; j<=11; j++)
				if ( j==4 || j==8 )
					cout<<INTERSECTION ;
				else
					cout<<HORIZONTAL ;
		cout<<endl ;
	}
}

/*
void PrintBoard()
{
    system("CLS");
    gotoxy(startX+3,startY);	cout<<VERTICAL;
    gotoxy(startX+7,startY);	cout<<VERTICAL;
    gotoxy(startX+1,startY+1);
	if ( any_player[0] == 0 )
		cout<<"1";
	else
		cout<<pos[0];
    gotoxy(startX+3,startY+1);	cout<<VERTICAL;
    gotoxy(startX+5,startY+1);
	if ( any_player[1] == 0 )
		cout<<"2";
	else
		cout<<pos[1];
    gotoxy(startX+7,startY+1);	cout<<VERTICAL;
    gotoxy(startX+9,startY+1);
	if ( any_player[2] == 0 )
		cout<<"3";
	else
		cout<<pos[2];
    gotoxy(startX+3,startY+2);	cout<<VERTICAL;
    gotoxy(startX+7,startY+2);	cout<<VERTICAL;
    gotoxy(startX,startY+3);
    for (ctr=0;ctr<11;ctr++)
    {	
		if(ctr==3 || ctr==7)
			cout<<INTERSECTION;
		else
			cout<<HORIZONTAL;
    }
    gotoxy(startX+3,startY+4);	cout<<VERTICAL;
    gotoxy(startX+7,startY+4);	cout<<VERTICAL;
    gotoxy(startX+1,startY+5);
	if ( any_player[3] == 0 )
		cout<<"4";
	else
		cout<<pos[3];
    gotoxy(startX+3,startY+5);	cout<<VERTICAL;
    gotoxy(startX+5,startY+5);
	if ( any_player[4] == 0 )
		cout<<"5";
	else
		cout<<pos[4];
    gotoxy(startX+7,startY+5);	cout<<VERTICAL;
    gotoxy(startX+9,startY+5);
	if ( any_player[5] == 0 )
		cout<<"6";
	else
		cout<<pos[5];
    gotoxy(startX+3,startY+6);	cout<<VERTICAL;
    gotoxy(startX+7,startY+6);	cout<<VERTICAL;
    gotoxy(startX,startY+7);
    for (ctr=0;ctr<11;ctr++)
    {	
		if(ctr==3 || ctr==7)
			cout<<INTERSECTION;
		else
			cout<<HORIZONTAL;
    }
    gotoxy(startX+3,startY+8);	cout<<VERTICAL;
    gotoxy(startX+7,startY+8);	cout<<VERTICAL;
    gotoxy(startX+1,startY+9);
	if ( any_player[6] == 0 )
		cout<<"7";
	else
		cout<<pos[6];
    gotoxy(startX+3,startY+9);	cout<<VERTICAL;
    gotoxy(startX+5,startY+9);
	if ( any_player[7] == 0 )
		cout<<"8";
	else
		cout<<pos[7];
    gotoxy(startX+7,startY+9);	cout<<VERTICAL;
    gotoxy(startX+9,startY+9);
	if ( any_player[8] == 0 )
		cout<<"9";
	else
		cout<<pos[8];
    gotoxy(startX+3,startY+10);	cout<<VERTICAL;
    gotoxy(startX+7,startY+10);	cout<<VERTICAL;
    cout<<"\n";
}
*/

void Result(int t, int w)
{
    PrintBoard() ;
    if(t==1)
    {
		if (w==3)
			cout<<"\n\nDraw . . .";
		else if (w==1)
			cout<<"\n\nYou won the game";
		else if (w==2)
			cout<<"\n\nYou lost the game";
    }
    else if (t==2)
    {
		if (w==3)
			cout<<"\n\nDraw . . .";
		else
			cout<<"\n\nPlayer "<<w<<" won the game";
    }
}

void ContGame()
{
    char rep = 'a' ;
    cout<<"\n\n\nOkay, do u wanna play another game?(y/n)     " ;
    cin>>rep;
    if (rep=='n' || rep=='N')
		TellExiting();
    else
		Intro();
}

void TellExiting()
{
    cout<<"\n\n\nExiting ! ! !" ;
    for (ctr=0; ctr<ExitNoOfDots; ctr++)
    {	
		Sleep (1000*ExitWaitPerDot);
		cout<<" . ";
    }
    Sleep (1000*ExitWaitPerDot);
}

int main()
{   
	Intro();
	exit(0) ;
}
