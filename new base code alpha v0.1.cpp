#include <iostream>
#include <stdlib.h>

using namespace std;
bool checkWinP1(char value[3][3])
{
	bool playerWin = 0;
	for (int i = 0; i < 3; i++)
	{
		if (value[i][0] == value[i][1] && value[i][1] == value[i][2] && value[i][0] == 'X')
		{
				playerWin = 1;
				break;	
		}
		if (value[0][i] == value[1][i]&& value[1][i] == value[2][i]&& value[2][i] == 'X')
		{
				playerWin = 1;
				break;
		}
	}
	if (value[0][0] == value[1][1]&& value[1][1] == value[2][2]&& value[2][2] == 'X')
	{
			playerWin = 1;
	}
	if (value[0][2] == value[1][1]&& value[1][1] == value[2][0]&& value[2][0] == 'X')
	{
			playerWin = 1;
	}
	return playerWin;
}

bool checkWinP2(char value[3][3])
{
	bool playerWin=0;
	for (int i = 0; i < 3; i++)
	{
		if (value[i][0] == value[i][1] && value[i][1] == value[i][2] && value[i][0] == 'O')
		{

				playerWin = 1;
				break;
		
		}
		if (value[0][i] == value[1][i] && value[1][i] == value[2][i] && value[2][i] == 'O')
		{
				playerWin = 1;
				break;
		}	
	}
	if (value[0][0] == value[1][1] && value[1][1] == value[2][2] && value[2][2] == 'O')
	{
			playerWin = 1;
	}
	if (value[0][2] == value[1][1] && value[1][1] == value[2][0] && value[2][0] == 'O')
	{
			playerWin = 1;
	}
	return playerWin;
}

void viewXO(char value[3][3])
{
	system("CLS");
	cout << "-------" << endl;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			cout << "|" << value[x][y];
		}
		cout << "|" << endl << "-------" << endl;
	}
}

int main()
{
	cout << " This is an ordinary 2 players tic tac toe game prototype" << endl;
	char value[3][3] = {};
	int i1, j1, i2, j2;
	bool player1win = 0, player2win = 0;
	cout << "Player 1 = X, Player 2 = O" << endl << "Lets start" << endl;
	cout << "Press Y to continue" << endl;
	char prompt;
	cin >> prompt;
	while (prompt != 'y' && prompt != 'Y')
	{
		cout << "Just enter Y, Could you?";
		cin >> prompt;
	}
		
	

	do
	{
	viewXO(value);
	rePlayer1:
		cout << " Player 1 X , input row and colomn to mark it" << endl;
		cin >> i1 >> j1;
		i1--;
		j1--;

		if (value[i1][j1] == 'X' || value[i1][j1] == 'O')
		{
			cout << "this space is already taken" << endl;
			goto rePlayer1;
		}

		value[i1][j1] = 'X';
		viewXO(value);
		player1win = checkWinP1(value);
		if (player1win == true)
		{
			viewXO(value);
			break;
		}
	rePlayer2:
		cout << " player 2 O , input row and colomn to mark it" << endl;
		cin >> i2 >> j2;
		i2--;
		j2--;

		if (value[i2][j2] == 'X' || value[i1][j1] == 'O')
		{
			cout << "this space is already taken" << endl;
			goto rePlayer2;
		}
		value[i2][j2] = 'O';
		
		player2win = checkWinP2(value);
		if (player2win == true)
		{
			viewXO(value);
			break;
		}
			
	} while (1);

	if (player1win == 1)
		cout << "player 1 wins" << endl;
	if (player2win == 1)
		cout << "player 2 wins" << endl;
}
