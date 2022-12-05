#include <iostream>
#include <string.h>
#include <random>
#include <stdlib.h>
using namespace std;

class game
{
private:
    char grid[3][3];
    int number = 1;
    char ai = 'X';
    char peo = 'O';
    int temp;
    int countmove = 9;
    char board[3][3] = { {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'} };
    int input;
    int row, column;
    char turn = 'X';
    bool draw = false;

public:
    void Game_Display()
    {
        cout << "\tPLAYER - 1 [X]\t PLAYER - 2 [O]\n";
        cout << "\t\t  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << " \n";
        cout << "\t\t     |     |     \n";
        cout << "\t\t  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << " \n";
        cout << "\t\t     |     |     \n";
        cout << "\t\t  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << " \n";
        cout << "\t\t     |     |     \n";
    }

    void player_turn()
    {
        if (turn == 'X')
        {
            cout << "\tPlayer - 1 [X] turn : ";
        }
        else if (turn == 'O')
        {
            cout << "Player - 2 [O] turn : ";
        }
        cin >> input;

        switch (input)
        {
        case 1: row = 0; column = 0; break;
        case 2: row = 0; column = 1; break;
        case 3: row = 0; column = 2; break;
        case 4: row = 1; column = 0; break;
        case 5: row = 1; column = 1; break;
        case 6: row = 1; column = 2; break;
        case 7: row = 2; column = 0; break;
        case 8: row = 2; column = 1; break;
        case 9: row = 2; column = 2; break;
        default: cout << "Invalid Move\n";
        }

        if (turn == 'X' && (board[row][column] != 'X' && board[row][column] != 'O'))
        {
            board[row][column] = 'X';
            turn = 'O';
        }
        else if (turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O')
        {
            board[row][column] = 'O';
            turn = 'X';
        }
        else
        {
            cout << "Box already filled!\n Please choose another!!\n\n";
            player_turn();
        }
        Game_Display();
    }

    bool gameover() {
        // checking the win for Simple Rows and Simple Column
        for (int i = 0; i < 3; i++)
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
                return false;

        // checking the win for both diagonal

        if (board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
            return false;

        // Checking the game is in continue mode or not
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] != 'X' && board[i][j] != 'O')
                    return true;

        // Checking the if game already draw
        draw = true;
        return false;
    }

    struct move
    {
        int r, c, score;
    };

    void start()
    {
        cout << "\n-------------\n";
        for (int x = 0; x < 3; x++)
        {
            cout << "| ";
            for (int y = 0; y < 3; y++)
            {
                cout << number << " | ";
                number++;
            }
            cout << "\n-------------\n";
        }
    }

    bool win()
    {
        int win_states[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };
        for (int i = 0; i < 8; i++)
        {
            bool win = true;
            int first_r = win_states[i][0] / 3, first_c = win_states[i][0] % 3;
            for (int j = 0; j < 3; j++)
            {
                int r = win_states[i][j] / 3, c = win_states[i][j] % 3;
                if (grid[first_r][first_c] == ' ' || grid[first_r][first_c] != grid[r][c])
                {
                    win = false;
                }
            }
            if (win)
                return true;
        }
        return false;
    }

    bool tie()
    {
        if (win())
            return false;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }

    void checker()
    {
        const char* winning_moves[8] = { "123", "456", "789", "147", "258", "369", "159", "753" };
        // Loop
        for (int a = 0; a < 8; a++)
        {
            bool winner = true;
            char previous = '0';
            const char* winning_move = winning_moves[a];

            for (int index = 0; index < 3; index++)
            {
                char character = winning_move[index];
                int entered_number = character - '0';
                int grid_space = entered_number - 1;
                int row = grid_space / 3;
                int col = grid_space % 3;

                char grid_char = grid[row][col];

                if (previous == '0')
                {
                    previous = grid_char;
                }
                else if (previous == grid_char)
                {
                    continue;
                }
                else
                {
                    winner = false;
                    break;
                }
            }
            if (winner)
            {
                puts("*********** We have a WINNER!!! ***********");
                printf("Looks like %c won, congratulation\n", previous);
            }
        }
    }

    void user()
    {
        string input;
        while (true)
        {
            puts("where would you like to play:");
            cin >> input;

            if (input != "")
            {
                // 1,2,3,4,5,6,7,8,9
                char entered = input.c_str()[0];
                if (entered >= '1' && entered <= '9')
                {
                    int entered_num = entered - '0';
                    int index = entered_num - 1;

                    int row = index / 3;
                    int column = index % 3;
                    char grid_position = grid[row][column];
                    if (grid_position == 'X' || grid_position == 'O')
                    {
                        puts("That grid positon is already taken!");
                    }
                    else
                    {
                        grid[row][column] = 'O';
                        break;
                    }
                }
                else
                {
                    puts("You have to play in range 1 - 9 :");
                }
            }
            else
            {
                puts("You must enter something!");
            }
        }
    }

    void generate()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                grid[i][j] = ' ';
            }
        }
    }

    void showgrid()
    { // Display the grid and content in the grid
        cout << "\n-------------\n";
        for (int x = 0; x < 3; x++)
        {
            cout << "| ";
            for (int y = 0; y < 3; y++)
            {
                cout << grid[x][y] << " | ";
            }
            cout << "\n-------------\n";
        }
    }

    void AI()
    {
        move best_move = minimax();
        grid[best_move.r][best_move.c] = 'X';
    }

    void AI_random() {
        while (true)
        {
            int pc_choice = (rand() % 9) + 1;

            int row = (pc_choice - 1) / 3;
            int column = (pc_choice - 1) % 3;
            char postion = grid[row][column];
            if (postion == 'X' || postion == 'O')
            {
                // postion is been taken already !!! check another loaction
                continue;
            }
            else
            {
                cout << "Computer Choice " << pc_choice << " as there turn.\n"
                    << endl;
                grid[row][column] = 'X';
                break;
            }
        }
    }

    move minimax(bool maximizing_player = true)
    {
        move best_move;
        if (win())
        {
            if (maximizing_player)
            {
                best_move.score = -1;
            }
            else
            {
                best_move.score = 1;
            }
            return best_move;
        }
        else if (tie())
        {
            best_move.score = 0;
            return best_move;
        }

        best_move.score = maximizing_player ? -2 : 2;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == ' ')
                {
                    grid[i][j] = maximizing_player ? ai : peo;
                    move board_state = minimax(!maximizing_player);
                    if (maximizing_player)
                    {
                        if (board_state.score > best_move.score)
                        {
                            best_move.score = board_state.score;
                            best_move.r = i;
                            best_move.c = j;
                        }
                    }
                    else
                    {
                        if (board_state.score < best_move.score)
                        {
                            best_move.score = board_state.score;
                            best_move.r = i;
                            best_move.c = j;
                        }
                    }
                    grid[i][j] = ' ';
                }
            }
        }
        return best_move;
    }

    game(string aisecond, string first, string asfasd, string asdas) {
        generate();
        showgrid();
        do
        {
            user();
            showgrid();
            if (win()) {
                break;
            }
            AI_random();
            showgrid();
            
        } while (!win());
        if (countmove == 1)
        {
            cout << "\n\n TIE \n\n";
        }else{
            checker();
        }
    }

    game(string aisecond, string first, string asfsd) {
        generate();
        showgrid();
        do
        {
            AI_random();
            showgrid();
            if (win()) {
                break;
            }
            user();
            showgrid();
            
        } while (!win());
        if (countmove == 1)
        {
            cout << "\n\n TIE \n\n";
        }else{
            checker();
        }
    }

    game(string aisecond, string first)
    {
        start();
        generate();
        do
        {
            user();
            countmove--;
            showgrid();
            if (win()) {
                break;
            }
            AI();
            countmove--;
            showgrid();
        } while (!win() && (countmove != 1));
        if (countmove == 1)
        {
            cout << "\n\n TIE \n\n";
        }
        else {
            checker();
        }
    };

    game(string aifir)
    {
        start();
        generate();
        do
        {
            AI();
            countmove--;
            showgrid();
            if (win()) {
                break;
            }
            user();
            countmove--;
            showgrid();
            
        } while (!win() && (countmove != 1));
        if (countmove == 1)
        {
            cout << "\n\n TIE \n\n";
        }else{
            checker();
        }
    };

    game()
    {
        Game_Display();
        while (gameover())
        {
            player_turn();
            gameover();
        }
        if (turn == 'X' && draw == false)
        {
            cout << "\n\nCongratulations!Player with 'O' has won the game";
        }
        else if (turn == 'O' && draw == false)
        {
            cout << "\n\nCongratulations!Player with 'X' has won the game";
        }
        else
            cout << "\n\nGAME DRAW!!!\n\n";
    }
};

int main(int argc, char* argv[])
{
    cout << "\n--------Welcome--------\n" << endl;
    cout << "Hey! Up for a Game (Y/N):  " << endl;
    string take;
    cin >> take;
    do {
        int choice;
        cout << "Enter Your Choice: " << endl;
        cout << "1.Multiplayer: " << endl;
        cout << "2.Play with AI:: AI First - " << endl;
        cout << "3.Play with AI:: AI second - " << endl;
        cout << "4.Play with AI-Easy mode:: AI Fisrt - " << endl;
        cout << "5.Play with AI-Easy mode:: AI second - " << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            game();
            break;

        case 2:
            game("firsttt");
            break;

        case 3:
            game("secondd", "firsttt");
            break;

        case 4:
            game("secondd", "firsttt", "firsttt");
            break;

        case 5:
            game("secondd", "firsttt", "firsttt", "firsttt");
            break;

        default:
            cout << "Invalid Choice" << endl;
            break;
        }
        cout << "\n------------PLAY AGAIN------------\n " << endl;

        cout << "Hey! Up for a Game (Y/N):  " << endl;
        cin >> take;
    } while (take == "Y" || take == "y" || take == "Yes" || take == "yes");
    return 0;
}
