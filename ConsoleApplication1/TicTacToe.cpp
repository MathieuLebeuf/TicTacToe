#include <iostream>
#include <string>
#include <stdlib.h>

using std::string;

// Class for all information of the board. Define the board array and have the methods to access the information and validate the input. Verify if the board has a winning condition.
class Board
{
    string board[3][3];
    
public:
    //Constructor.
    Board()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                board[i][j] = " ";
            }
        }

    }

    // Verify if a boardtile(row,col)
    bool isTileEmpty(int row, int col)
    {
        if (board[row][col] != " ")
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    // return a tile info.
    string getTileInfo(int row, int col)
    {
        return board[row][col];
    }

    // set a tile info.
    void setTileInfo(int row, int col, string info)
    {
        board[row][col] = info;  
    }

    // verify if one of the winning condition is meet. If a winning condition is meet, return the winning player's mark.
    string isWinning()
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][0] != " " && board[i][0] == board[i][1] && board[i][0] == board[i][2])
            {
                return board[i][0];
            }

            if (board[0][i] != " " && board[1][i] == board[2][i] && board[0][i] == board[2][i])
            {
                return board[i][0];
            }
        }
        if (board[0][0] != " " && board[0][0] == board[1][1] && board[0][0] == board[2][2])
        {
            return board[0][0];
        }

        if (board[0][2] != " " && board[0][2] == board[1][1] && board[0][2] == board[2][0])
        {
            return board[0][2];
        }

        return " ";
    }

};

//Convert the user row choice into an array choice.
int convertChoiceToRow(char rowChoice)
{
    int row = -1;

    if (rowChoice == 'A')
    {
        row = 0;
    }
    else if(rowChoice == 'B')
    {
        row = 1;
    }
    else if(rowChoice == 'C')
    {
        row = 2;
    }

    return row;
}

//Convert the user col choice into an array choice.
int convertChoiceToCol(int colChoice)
{
    return colChoice - '0' - 1;
}

// Display the board and the general information (player turn and information how to quit or restart the game.
void displayBoard(Board* board, string player)
{
    std::cout << "     1     2     3 " << std::endl;
    std::cout << "        |     |         Current player: " << player << std::endl;
    std::cout << " A   " << board->getTileInfo(0, 0) << "  |  " << board->getTileInfo(0, 1) << "  |  " << board->getTileInfo(0, 2) << "      To quit: Q" << std::endl;
    std::cout << "   _____|_____|_____    To restart: R" << std::endl;
    std::cout << "        |     |      " << std::endl;
    std::cout << " B   " << board->getTileInfo(1, 0) << "  |  " << board->getTileInfo(1, 1) << "  |  " << board->getTileInfo(1, 2) << "  " << std::endl;
    std::cout << "   _____|_____|_____   " << std::endl;
    std::cout << "        |     |      " << std::endl;
    std::cout << " C   " << board->getTileInfo(2, 0) << "  |  " << board->getTileInfo(2, 1) << "  |  " << board->getTileInfo(2, 2) << "  " << std::endl;
    std::cout << "        |     |      " << std::endl;
}

bool isChoiceValid(string choice)
{
    string uChoice;
    if (choice.length() == 2)
    {
        string s(1, ::toupper(choice[0]));
        uChoice = s;
        uChoice = uChoice + choice[1];
    }
    else
    {
        return false;
    }

    if (uChoice == "A1" || uChoice == "A2" || uChoice == "A3" || uChoice == "B1" || uChoice == "B2" || uChoice == "B3" || uChoice == "C1" || uChoice == "C2" || uChoice == "C3")
    {
        return true;
    }
       
    return false;

}

int main()
{
    Board* board = new Board();
    bool victory = false;
    string player = "";
    int cmpt = 0;
    int row = -1;
    int col = -1;
    srand(time(0)); // Reseed the random function.
    if((rand() % 100) + 1 > 50)
    {
        player = "X";
    }
    else
    {
        player = "O";
    }
    std::string answer = "";

    // main loop. Cycle the code until the winning condition OR the counter (cmpt) is up to 9, which trigger the draw condition.
    while (victory != true)
    {
        displayBoard(board, player); //display the board at the start of the loop.
        std::cout << "" << std::endl;
        std::cout << "Choose a tile: ";

        std::cin >> answer;
        if (::toupper(answer[0]) == 'Q') // Quit.
        {
            return 0;
        }
        if (::toupper(answer[0]) == 'R') // Restart.
        {
            board = new Board();
            srand(time(0));
            if ((rand() % 100) + 1 > 50)
            {
                player = "X";
            }
            else
            {
                player = "O";
            }
        }
        if (isChoiceValid(answer)) // Verify if choice input is valid.
        {
            // Convert the choice A1, B2, etc. in a row, col data readable for the board object.
            row = convertChoiceToRow(toupper(answer[0]));
            col = convertChoiceToCol(answer[1]);

            if (board->isTileEmpty(row, col)) // Validate that the board tile location is empty.
            {
                board->setTileInfo(row, col, player);
                cmpt++;
                if (board->isWinning() == " ") // Verify the winning conditions.
                {
                    if (cmpt < 9) // Verify that the dray condition is not meet. 
                    {
                        if (player == "X")
                        {
                            player = "O";
                        }
                        else
                        {
                            player = "X";
                        }
                    }
                    else // draw meet.
                    {
                        std::cout << "----------------------------------------" << std::endl;
                        displayBoard(board, player);
                        victory = true;
                    }
                }
                else // victory condition meet.
                {
                    std::cout << "----------------------------------------" << std::endl;
                    displayBoard(board, player);
                    victory = true;
                }
            }
        }
        std::cout << "----------------------------------------" << std::endl;
    }
    if (cmpt < 9) //Winning text.
    {
        std::cout << "Congratz. The winning is player: " << player << std::endl;
    }
    else // Draw text.
    {
        std::cout << "It's a draw! " << std::endl;
    }

    // Restart or not loop.
    while (answer.length() != 1 && toupper(answer[0]) != 'N' || toupper(answer[0]) != 'Y')
    {
        std::cout << "Do you want to restart? (Y/N): ";
        std::cin >> answer;
        if (answer.length() == 1 && toupper(answer[0]) == 'Y')
        {
            main(); //Restart to main.
            return 0;
        }
        else if(answer.length() == 1 && toupper(answer[0]) == 'N')
        {
            return 0;
        }
    }



}

