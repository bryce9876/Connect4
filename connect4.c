//Connect 4 game by Bryce Matheson for linux


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 7

typedef enum player_turn{
	player1 = 1, 
	player2 = 2, 
} player_turn_t;


//Initialise board
void initBoard(char board[SIZE][SIZE]){
	int i,j; 
	char c;

	//Clears board
	for (i=0; i<SIZE; i++){
		for (j=0; j<SIZE; j++){
			board[i][j] = 0;
		}
	}
}

void printInstructions(){
	char c;

	//Instructions
	printf("\nINSTRUCTIONS:\n\n");
	printf("Press 1 then enter to put counter in 1st column, press 2 then enter to put counter in second column etc.\n");
	printf("Players alternate putting a single counter into board until a line of 4 is achieved\n");
	printf("The player who achives this line of 4 wins\n");

	printf("\nPress any key and then enter to continue\n");
	c = getchar();
}


//Draws board
void drawBoard(char board[SIZE][SIZE], player_turn_t turn){
	int i,j;
	
	//Clear screen
	system("cls"); 

	//Print player turn info
	printf("PLAYER TURN = Player %d\n\n", turn);


	//Print top 2 rows
	for (i=1; i<=SIZE; i++) printf("  %d  ", i);
	printf("\n");
	for (i=0; i<SIZE; i++) printf(" ____");
	printf("\n");


	for (i=0; i<SIZE; i++){

		for (j=0; j<SIZE; j++) printf("|    ");
		printf("|\n");


		for (j=0; j<SIZE; j++){
			if (board[i][j]) printf("| %c  ", board[i][j]);
			else printf("|    ");
		}
		printf("|\n");


		for (j=0; j<SIZE; j++) printf("|____");
		printf("|\n");
	}
	printf("'q' then enter at anytime to quit or 'r' then enter to restart\n");
}

bool executeMove(char board[SIZE][SIZE], char c, player_turn_t turn){
	int i=SIZE-1;
	int j = c - 49; //Converts to int from ASCII
	bool success = false;

	//Checks that a valid column number is entered
	if (j < 0 || j > 6){
		return success = false;
	}

	while (board[i][j] == 'R' || board[i][j] == 'Y'){
		i--;
		//If i<0, the column is full and thus a coutner can't be placed there
		if (i < 0){
			return success = false;
		}
	}

	//Places a Y or R depending on players turn
	if (turn == player1){
		board[i][j] = 'R';
	} 
	else board[i][j] = 'Y';

	return success = true;
}

//Checks if current configuration is a winning one
bool win(char board[SIZE][SIZE]){
	int i,j;
	char c;

	//Starts at bottom and goes upwards as wins are more likely to occur at lower
	for (i=SIZE-1; i>=0; i--){
		for (j=0; j<SIZE; j++){

			//Checks if counter is present
			if (board[i][j] == 'R' || board[i][j] == 'Y'){
				char c = board[i][j];

				//Checks vertical
				if (board[i-1][j] == c && board[i-2][j] == c && board[i-3][j] == c) return true;
				//Checks horizontal
				if (board[i][j-1] == c && board[i][j-2] == c && board[i][j-3] == c) return true;
				//Checks diagonal
				if (board[i-1][j+1] == c && board[i-2][j+2] == c && board[i-3][j+3] == c) return true;
			}
		}
	}
	return false;
}

//Gets the next character from stdin that isn't a newline character
char getCharNoNewLine(){
	char c;

	c = getchar();
	while ('\n' == c){
		c = getchar();
	}

	return c;
}


int main(int argc, char *argv[]) {

	char board[SIZE][SIZE];
	char c;
	player_turn_t turn = player1;
	bool success = false;

	printInstructions();
	initBoard(board);

	//Game continues until player exits
	while (true){
		drawBoard(board, turn);

		c = getCharNoNewLine();        //Gets player input

		//If player wants to quit:
		if (c == 'q'){

			printf("QUIT? (y/n) ");
			c = getCharNoNewLine();

			if (c == 'y') return(EXIT_SUCCESS);
			//else:
			continue;
		}

		//If player wants to restart:
		else if (c == 'r'){

			printf("RESTART? (y/n) ");
			c = getCharNoNewLine();

			if (c == 'y') initBoard(board); //Resets board
			continue;
		}

		//Tries to execute move
		success = executeMove(board, c, turn);

		//If move executed is invalid:
		if (!success){
			printf("Please enter a valid move");
			sleep(1);
			continue;
		}

		//If a player wins
		if (win(board)){
			drawBoard(board, turn);
			printf("\n**** PLAYER %d HAS WON!!! ****\n", turn);
			printf("\n Press 'q' then enter to quit or 'r' then enter to restart\n");

			c = getchar();

			//Waits for player to press either q or c
			while (c != 'q' || c != 'r'){
				if (c == 'q') return(EXIT_SUCCESS);     //Quits
				else if (c == 'r'){					    //Restarts
					initBoard(board); 
					break;
				}
				
				c = getchar();
			}
		}

		//Changes player 
		if (turn == player1){
			turn = player2;
		}
		else turn = player1;
	}

	return EXIT_SUCCESS;
}

/*

		for (j=0; j<SIZE; j++){
			//If no value on this tile:
			if (board[i][j]){
				printf("|   |\n");
			}
			//If value on this tile:
			else{
				printf("| %c |\n", board);
			}
			printf("|___|\n");
		}
*/