#include <iostream>
#include <time.h>
#define CAPACITY 100
using namespace std;

enum TYPE { HUMAN, COMPUTER };

void init(char Board[][CAPACITY], int& dim, char pName[2][30], char pSym[], int& turn, int& winCount)
{
	cout << "Dimension: ";
	cin >> dim;
	cout << "Win Count: ";
	cin >> winCount;

	cout << "Enter player's name: ";
	cin >> pName[0];
	cout << "Enter player's symbol: ";
	cin >> pSym[0];
	pSym[1] = (pSym[0] == 'X' || pSym[0] == 'x') ? 'O' : 'X';

	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			Board[ri][ci] = '-';
		}
	}
	turn = rand() % 2;
}
void printBoard(char Board[][CAPACITY], int  dim)
{
	system("clear");
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			cout << Board[ri][ci] << "   ";
		}
		cout << endl;
	}
}
void userInput(int& ri, int& ci, char pName[], char pSym)
{
	cout << pName << "'s Turn to place '" << pSym << " ' (ri, ci): ";
	cin >> ri;
	cin >> ci;
	ri--;
	ci--;
}
bool validInput(int ri, int ci, const char Board[][CAPACITY], int dim)
{
	return ((ri >= 0 && ci >= 0) && (ri <= dim && ci <= dim) && Board[ri][ci] == '-');
}
void updateBoard(char Board[][CAPACITY], int  dim, int ri, int ci, char pSym)
{
	Board[ri][ci] = pSym;
}
bool horizontalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci)
{
	if (ci + winCount - 1 >= dim)
		return false;
	for (int i = 0; i < winCount; i++)
	{
		if (Board[ri][ci + i] != pSym)
			return false;
	}
	return true;
}
bool verticalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci)
{
	if (ri + winCount - 1 >= dim)
		return false;
	for (int i = 0; i < winCount; i++)
	{
		if (Board[ri + i][ci] != pSym)
			return false;
	}
	return true;
}
bool rightDiagonalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci)
{
	if (ri + winCount - 1 >= dim)
		return false;
	for (int i = 0; i < winCount; i++)
	{
		if (Board[ri + i][ci + i] != pSym)
			return false;
	}
	return true;
}
bool leftDiagonalCheck(char Board[][CAPACITY], int dim, int winCount, char pSym, int ri, int ci)
{
	if (ci - (winCount - 1) < 0)
		return false;
	for (int i = 0; i < winCount; i++)
	{
		if (Board[ri + i][ci - i] != pSym)
			return false;
	}
	return true;

}
bool isWinHere(char Board[][CAPACITY], int  dim, int winCount, char pSym, int ri, int ci)
{
	bool horizontal = horizontalCheck(Board, dim, winCount, pSym, ri, ci);
	bool vertical = verticalCheck(Board, dim, winCount, pSym, ri, ci);
	bool leftDiagonal = leftDiagonalCheck(Board, dim, winCount, pSym, ri, ci);
	bool rightDiagnal = rightDiagonalCheck(Board, dim, winCount, pSym, ri, ci);
	return (horizontal || vertical || leftDiagonal || rightDiagnal);
}
bool isWin(char Board[][CAPACITY], int  dim, int winCount, char pSym)
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (isWinHere(Board, dim, winCount, pSym, ri, ci))
				return true;
		}
	}

	return false;
}
bool isDraw(char Board[][CAPACITY], int dim)
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (Board[ri][ci] == '-')
				return false;
		}
	}
	return true;
}
void turnChange(int& turn)
{
	turn = (turn + 1) % 2;
}

void HvsC(const char Board[][CAPACITY], int& ri, int& ci, int dim, char pSym, int winCount, char CS, char HS)
{
	// creating an array for a new board
	char T[CAPACITY][CAPACITY];
	// copying the symbols from the board 'Board' to board 'T'
	for (int r = 0; r < dim; r++)
	{
		for (int c = 0; c < dim; c++)
		{
			T[r][c] = Board[r][c];
		}
	}

	for (int WC = winCount; WC > 1; WC--) {
		// Iterate over all positions in the board
		for (int r = 0; r < dim; r++)
		{
			for (int c = 0; c < dim; c++)
			{
				// If the position (r, c) is valid
				if (validInput(r, c, T, dim))
				{
					// Place computer's symbol
					T[r][c] = CS;
					// If the computer wins
					if (isWinHere(T, dim, WC, pSym, r, c))
					{
						// Remove computer's symbol from the board
						T[r][c] = '-';
						// Return the computer's move coordinates
						ri = r;
						ci = c;
						return;
					}
					else
					{
						// Remove computer's symbol from the board
						T[r][c] = '-';
					}
				}
			}
		}

		// Iterate over all positions in the board
		for (int r = 0; r < dim; r++)
		{
			for (int c = 0; c < dim; c++)
			{
				// If the position (r, c) is valid
				if (validInput(r, c, T, dim))
				{
					// Place human's symbol
					T[r][c] = HS;
					// If the human wins
					if (isWinHere(T, dim, WC, pSym, r, c))
					{
						// Remove human's symbol from the board
						T[r][c] = '-';
						// Return the human's move coordinates
						ri = r;
						ci = c;
						return;
					}
					else
					{
						// Remove human's symbol from the board
						T[r][c] = '-';
					}
				}
			}
		}
	}

	do {
		ri = rand() % dim;
		ci = rand() % dim;
	} while (!validInput(ri, ci, Board, dim));
}

int main()
{
	cout << "\n\n\t\t\tThe Game of Gomoku\n\n";
	cout << "\n\n\t\t\t    Let's begin!\n\n" << endl;
	srand(time(0));
	char choice;
	char Board[CAPACITY][CAPACITY];
	char pName[2][30] = { "Human", "Computer" };
	// "Human" will be replaced by the name of the player in init function
	char pSym[2];
	int turn, ri, ci, dim, winCount;
	bool gameOver = false;
	int winner = -1;

	cout << "Initializing..." << endl << endl;
	init(Board, dim, pName, pSym, turn, winCount);
	do
	{
		printBoard(Board, dim);
		if (turn == HUMAN)
		{
			do
			{
				userInput(ri, ci, pName[turn], pSym[turn]);
				if (!validInput(ri, ci, Board, dim))
				{
					cout << "Invalid Input" << endl;

				}
			} while (!validInput(ri, ci, Board, dim));
		}
		else
		{
			cout << "Computer's turn..." << endl;
			HvsC(Board, ri, ci, dim, winCount, pSym[turn], pSym[COMPUTER], pSym[HUMAN]);
		}

		updateBoard(Board, dim, ri, ci, pSym[turn]);
		printBoard(Board, dim);

		gameOver = isWin(Board, dim, winCount, pSym[turn]);
		if (gameOver)
			winner = turn;
		if (!isDraw(Board, dim))
			gameOver = true;
		if (!gameOver)
			turnChange(turn);
	} while (!gameOver);
	cout << endl;
	if (winner == -1)
		cout << "Game Draw!" << endl;
	else
	{
		cout << pName[turn] << " has won!" << endl;
	}

	return 0;
}



