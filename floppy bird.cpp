/*
* Created by Ali khaleghi - 12/18/2017
*/

#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

void initialize();
void board();
void drawBoard();
void drawBird();
void gotoxy(int, int);
void shiftLeft(int[]);
void lose();

int birdY = 10, score = 0;
int bottomWall[40], topWall[40];
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int main() {
	int input;
	
	initialize();
	
	while (true) {
		if(kbhit())
		{
			input=getch();
			switch(input)
			{
				case 'w':
				case '8':
				case 'W':
				case 'H':
				case ' ':
					gotoxy(3, birdY-1);
					printf("%c", 255);
					if (birdY - 7 > topWall[2]){
						gotoxy(3, birdY-7);
						birdY -= 6 ;
						printf("%c", 2);
					}
					else {
						gotoxy(3, topWall[2]+1);
						birdY = topWall[2]+1 ;
					    SetConsoleTextAttribute(console, 14);
						printf("%c", 2);	
					    SetConsoleTextAttribute(console, 7);
						lose();
					}
				break;			
			}
		}
		board();
		Sleep(50);
	}	
}

void initialize() {
	CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);
   
	for (int i=0; i<40; i++) {
		bottomWall[i] = 0;
		topWall[i] = 0;
	}
	printf("\npress any key to start");
	getch();
	system("cls");
}

void board() {
	drawBoard();
	drawBird();
}

void drawBoard() {
	
	
	for (int i=0; i<40; i++){	//draw top wall
		for (int j=topWall[i]; j<10; j++) {
			gotoxy(i, j);
			printf("%c", 255);
		}
		for (int j=0; j<topWall[i]+1; j++) {
			gotoxy(i, j);
			printf("%c", 219);
		}
	}
	
	for (int i=0; i<40; i++){	//draw bottom wall
		for (int j=bottomWall[i]; j<10; j++) {
			gotoxy(i, 20 - j + 1);
			printf("%c", 255);
		}
		for (int j=0; j<bottomWall[i]+1; j++) {
			gotoxy(i, 20 - j + 1);
			printf("%c", 219);
		}
	}
	
	shiftLeft(bottomWall);
	shiftLeft(topWall);
}

void drawBird() {
	if(birdY <= topWall[2]-1){
		lose();
	}
	if(birdY >= 20 - bottomWall[2] + 1){
		lose();
	}
	if(birdY != topWall[2]) {
		gotoxy(3, birdY-1);
		printf("%c", 255);
	}
	gotoxy(3, birdY);
	
    SetConsoleTextAttribute(console, 14);
	printf("%c", 2);	
    SetConsoleTextAttribute(console, 7);
	
	if(birdY++ == 20 - bottomWall[2]){
		lose();
	}
	score++;
	gotoxy(0, 23);
	printf("score: %d", score);
	gotoxy(40, 20);
}

void gotoxy(int x, int y) 
{ 
	CursorPosition.X = x; // Locates column
	CursorPosition.Y = y; // Locates Row
	SetConsoleCursorPosition(console,CursorPosition); // Sets position for next thing to be printed 
}

void shiftLeft(int input[]){
	srand(time(NULL));
	for (int i = 0; i <39; i++)        
    	input[i]=input[i+1];
	input[39] = rand()%7;
}

void lose(){
	gotoxy(0, 23);
	printf("score: %d", score);
	getch();
	getch();
	system("cls");
	birdY = 10;
	score = 0;
	main();
}
