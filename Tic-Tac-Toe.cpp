#include <iostream>

using namespace std;

char board[3][3];
bool endgame;
int winner;

int row, col;

char player = 'x', AI = 'o';


//Initialize
void initBoard()
{
	for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = '_';
        }
    }
}

//Draw the board
void draw()
{
    cout<<endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout<<board[i][j]<<" | ";
        }
        cout<<endl;
    }
    cout<<endl;
}

//Check for moves left
bool isMovesLeft()
{
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(board[i][j] == '_')	return true;
		}
	}
	return false;
}

void checkWin()
{
	char key = '_';
	winner = 0;
	endgame = false;
 
    for (int i = 0; i < 3; i++)
    	if (board [i] [0] == board [i] [1] && board [i] [0] == board [i] [2] && board [i] [0] != '_') key = board [i] [0];
       
	for (int i = 0; i < 3; i++)
        if (board [0] [i] == board [1] [i] && board [0] [i] == board [2] [i] && board [0] [i] != '_') key = board [0] [i];
             
	if (board [0] [0] == board [1] [1] && board [1] [1] == board [2] [2] && board [1] [1] != '_') key = board [1] [1];
	if (board [0] [2] == board [1] [1] && board [1] [1] == board [2] [0] && board [1] [1] != '_') key = board [1] [1];
           
    if (key == player)
    {
      winner = 1;
      endgame = true;
    }
    if (key == AI)
    {
      winner = 2;
      endgame = true;
    }
 
    if (isMovesLeft() == false)
    {                      
        endgame = true;
    }
}

//Evaluation
int evaluate(char b[3][3])
{
	//Check for winning rows
	for(int row = 0; row < 3; row++)
	{
		if(b[row][0] != '_' && b[row][0] == b[row][1] && b[row][0] == b[row][2])
		{
			if(b[row][0] == player)
			{
				return 10;
			}
				
			else if(b[row][0] == AI)
			{
				return -10;
			}
		}
	}
	
	//Check for winning columns
	for(int col = 0; col < 3; col++)
	{
		if(b[0][col] != '_' && b[0][col] == b[1][col] && b[0][col] == b[2][col])
		{
			if(b[0][col] == player)
			{
				return 10;
			}
					
			else if(b[0][col] == AI)
			{
				return -10;
			}
		}
	}
	
	//Check for wining diagonals
	if(b[0][0] == b[1][1] && b[1][1] == b[2][2])
	{
		if(b[0][0] == player)
		{
			return 10;
		}
				
		else if(b[0][0] == AI)
		{
			return -10;
		}
	}
		
	if(b[0][2] == b[1][1] && b[1][1] == b[2][0])
	{
		if(b[0][2] == player)
		{
			return 10;
		}
				
		else if(b[0][2] == AI)
		{
			return -10;
		}
	}
		
	//If no one wins
	return 0;
}

//MiniMax algorithm
//The Computer calculates possible moves and return the best move
int minimax(int depth, int Player)
{
	int score = evaluate(board);
	
	// If Max won the game
	if (score == 10)
		return score - depth;
	
	// If Min won the game
	if (score == -10)
		return score + depth;
	
	if (isMovesLeft() == false)
		return 0;
	
	// if this is the Maximizer's move
	if (Player == -1)
	{
		int best = -1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == '_')
				{
					// Make the move
					board[i][j] = player;

					// Call minimax recursively and choose the maximum value
					best = max( best, minimax(depth+1, Player * -1) );

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}

	// if this is the Minimizer's move
	else
	{
		int best = 1000;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (board[i][j] == '_')
				{
					// Make the move
					board[i][j] = AI;

					// Call minimax recursively and choose the minimum value
					best = min( best, minimax(depth+1, Player * -1) );

					// Undo the move
					board[i][j] = '_';
				}
			}
		}
		return best;
	}
}

void computerMove()
{
	cout<<"=> The Computer's turn:"<<endl;
	int aiRow = -1;
	int aiCol = -1;
	
	int aiVal = -1000;
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == '_')
			{
				board[i][j] = AI;
				
				// Calculate this move
				int moveVal = -minimax(0, -1);
				
				board[i][j] = '_';
				
				if (moveVal > aiVal)
				{
					aiRow = i;
					aiCol = j;
					aiVal = moveVal;
				}
			}
		}
	}
	
	board[aiRow][aiCol] = AI;
	
	draw();
	checkWin();
}

void playerMove()
{
	int move = 0;
	
	start:
	cout<<"=> Make your move [1...9]: ";
	cin>>move;
	
	if (move > 0 && move <= 9)
	{
		switch(move)
		{
			case 1:
				{
					if(board[0][0] == '_')
					{
						board[0][0] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
			case 2:
				{
					if(board[0][1] == '_')
					{
						board[0][1] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
			case 3:
				{
					if(board[0][2] == '_')
					{
						board[0][2] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
			case 4:
				{
					if(board[1][0] == '_')
					{
						board[1][0] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
			case 5:
				{
					if(board[1][1] == '_')
					{
						board[1][1] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
			case 6:
				{
					if(board[1][2] == '_')
					{
						board[1][2] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
			case 7:
				{
					if(board[2][0] == '_')
					{
						board[2][0] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
			case 8:
				{
					if(board[2][1] == '_')
					{
						board[2][1] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
			case 9:
				{
					if(board[2][2] == '_')
					{
						board[2][2] = player;
						break;
					}
					else
					{
						cout<<"\nERROR: Occupied! Make your move again!\n"<<endl;
						goto start;
					}
				}
		}
		draw();
		checkWin();
	}
	else
	{
		cout<<"\nERROR: Wrong input!\n"<<endl;
		goto start;
	}
}

void playGame()
{
    cout<<"Player: X, Computer: O"<<endl;
    
    init:
    cout<<"\n--> Player goes first(1) or second(2)? ";
    unsigned turn;
    cin>>turn;
    
    if(turn == 1)
    {
    	draw();
		while (endgame == false)
    	{
    		if(endgame == false)
				playerMove();
			
    		if(endgame == false)
    			computerMove();
		}
	}
	else if(turn == 2)
	{
		draw();
		while (endgame == false)
    	{
    		if(endgame == false)
				computerMove();
    		
    		if(endgame == false)
    			playerMove();
		}
	}
	else
	{
		cout<<"\nERROR: Wrong input!"<<endl;
		goto init;
	}
	
	printf("\n-----Match ends!-----\n");
    switch(winner)
    {
    case 0:
        printf("\n--> Draw!\n"); break;
    case 1:
        printf("\n--> Player wins!\n"); break;
    case 2:
        printf("\n--> Computer wins!\n"); break;
    }
}
 
int main()
{
    initBoard();
    playGame();
    
    return 0;
}
