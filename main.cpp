#include<iostream>
#include <fstream>
using namespace std;

//game class contains all the functions you ened to play tic tac toe
class game {
    public:


    //creates a fresh board
    void init_board(string board[3][3]){
        for(int i = 0; i < 3; i++){
            for(int a = 0; a < 3; a++){
                board[i][a] = "-";
            }
        }
    }

    // returns a move chosen by the player
    int move(string player){
        int row;
        int col;
        cout << "what column would player " << player << " use?\n";
        cin >> col;
        cout << "what row would player " << player << " use?\n";
        cin >> row;
        row = (row-1) * 3;
        col -= 1;
        return row + col;
    }

    // alters the board
    void set(string board[][3], int move, string player){
        int row = move/3;
        int column = move%3;
        board[row][column] = player;
    }

    //displays the board to the console
    void display(string board[][3]){
        cout << ("   1   2   3") << "\n";
        cout << "1  " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
        cout << "2  " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
        cout << "3  " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    }

    //checks game end conditions and returns false if the game is over
    bool check(string board[][3]) {
        if(board[0][1] == board[0][0] && board[0][2] == board[0][0] && board[0][0] != "-"){
            return false;
        } if(board[1][1] == board[1][0] && board[1][2] == board[1][0] && board[1][0] != "-"){
            return false;
        } if(board[2][1] == board[2][0] && board[2][2] == board[2][0] && board[2][0] != "-"){
            return false;
        } if(board[1][0] == board[0][0] && board[2][0] == board[0][0] && board[0][0] != "-"){
            return false;
        } if(board[1][1] == board[0][1] && board[2][1] == board[0][1] && board[0][1] != "-"){
            return false;
        } if(board[1][2] == board[0][2] && board[2][2] == board[0][2] && board[0][2] != "-"){
            return false;
        } if(board[0][0] == board[1][1] && board[2][2] == board[1][1] && board[1][1] != "-"){
            return false;
        } if(board[0][3] == board[1][1] && board[3][0] == board[1][1] && board[1][1] != "-"){
            return false;
        }
        return true;
    }

    //saves board to file
    void save_file(string board[][3], string player){
        ofstream myfile;
        myfile.open ("board.txt");
        myfile << player;
        myfile << board[0][0] << board[0][1] << board[0][2];
        myfile << board[1][0] << board[1][1] << board[1][2];
        myfile << board[2][0] << board[2][1] << board[2][2];
        myfile.close();
    }

    //reads board from a file into an array and returns the player turn
    string file(string board[][3], string player){
        string content;
        ifstream myfile;
        myfile.open ("board.txt");
        if (myfile.is_open()){
            myfile >> content;
        } else {
            cout << "file failed to load";
        }
        myfile.close();
        player = content[0];
        for(int i=1; i<10; i++) {
            int row = (i-1)/3;
            int column = (i-1)%3;
            board[row][column] = content[i];
        }
        return player;
    }

    //handles basic function of the game and the calling of other functions
    void run(){
        //basic variables for game function
        bool game=true;
        string player = "x";
        string board[3][3] = {};
        string load;

        //player input to decide to pull game from file
        cout << "load board from file? (y/n)";
        cin >> load;
        if(load == "y"){
            player = file(board, player);
        }
        else {
            init_board(board);
        }
        display(board);

        //main loop that contains the playing of the game
        while(game == true){
            int change = move(player);
            set(board, change, player);
            game = check(board);
            display(board);
            
            //game end
            if (game == false) {
                cout << "player " << player << " wins!";
                break;
            }

            //switch player
            if (player == "x"){
                player = "o";
            } else {
                player = "x";
            }

            //save to file functionality - also ends game
            string save = "";
            cout << "would you like to save the progress of the game and quit? (y/n)";
            cin >> save;
            if (save == "y") {
                save_file(board, player);
                game = false;
            }
        }
    }
};

//main function to create an instance and run the game
int main() {
    game tic_tac;
    tic_tac.run();
    return 0;
}