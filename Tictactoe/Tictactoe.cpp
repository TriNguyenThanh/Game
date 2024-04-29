#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define GREEN 2
#define BLUE 9
#define BLACK 0
#define YELLOW 14

char board[3][3] = {
	{ '1', '2', '3' },
	{ '4', '5', '6' },
	{ '7', '8', '9' },
};

char playerX = 'X';
char playerO = 'O';

void printBoard();
int check();
int updateBoard(int choose, int player);
void set_color( int code );
void resetBoard();

int main() {
	system("color 0A");
	int end, choose, player;
	char Y = 'y';

	while(Y == 'y'){
		resetBoard();
		player = 0;
		do{
			system("cls");
			player++;
			if (player > 2){
				player = 1;
			}
			printBoard();
			bool input = true;
			do{
				printf("\nplayer %d choose: ", player);
				scanf("%d", &choose);
				if (1 <= choose && choose <= 9){
					int y = (choose+2)/3 - 1;
					int x = (choose-y*3) - 1;
					if(board[y][x] == 'X' || board[y][x] == 'O')
						printf("\n</> Invalid input.");
					else
						input = false;
				}else{
					printf("\n</> Invalid input.");
					system("pause");
				}
			}while (input);
			updateBoard(choose, player);
			end = check();
		}while(end == -1);

		if (end == 1){
			system("cls");
			printBoard();
			printf("\n\n</> Player %d is the winner!", player);
		}else{
			system("cls");
			printBoard();
			printf("\n\n</> Game draw");
		}

		system("echo. &pause");
		//printf("\n</> Do you want continue? (y/n): ");
	}

	return 0;
}

void printBoard() {
	printf("\n\tTic Tac Toe\n\n");
	printf("Player 1: X\t|\tPlayer 2: O\n\n");
	for(int i = 0; i < 3; i++){
		printf("\t+---+---+---+\n\t|");
		for (int j = 0; j < 3; j++){
			if (board[i][j] == 'X')
				set_color(BLACK * 16 + BLUE);
			if (board[i][j] == 'O')
				set_color(BLACK * 16 + YELLOW);
			printf(" %c", board[i][j]);
			set_color(BLACK * 16 + GREEN);
			printf(" |");
		}
		printf("\n");
	}
	printf("\t+---+---+---+\n");
}
int check(){
	bool draw = true;
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
		return 1;
	if (board[2][0] == board[1][1] && board[1][1] == board[0][2])
		return 1;
	for(int i = 0; i < 3; i++){
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
			return 1;
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
			return 1;
		if (draw)
			for (int j = 0; j < 3; j++)
				if ('1' <= board[i][j] && board[i][j] <= '9')
					draw = false;
	}
	if (draw)
		return 0;
	return -1;
}
int updateBoard(int choose, int player){
	char key;
	if(player == 1)
		key = 'X';
	else
		key = 'O';
	int y = (choose+2)/3 - 1;
    int x = (choose-y*3) - 1;
	board[y][x] = key;
	return 0;
}
void resetBoard(){
	for(int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			board[i][j] = i * 3 + j + 1 + '0';
		}
	}
}
void set_color( int code ) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}