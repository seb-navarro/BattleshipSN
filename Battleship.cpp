#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

// Potential Boats = ⛵, 🛥, ⛴, 🚢, 🛥️, 🚤

class Board {
    public:

        string grid[5][7] = {
            {"A", "O", "O", "O", "O", "O", "O"}, 
            {"B", "O", "O", "O", "O", "O", "O"}, 
            {"C", "O", "O", "O", "O", "O", "O"}, 
            {"D", "O", "O", "O", "O", "O", "O"}, 
            {" ", "1", "2", "3", "4", "5", "6"}
        };

        void show_board() {
            cout << endl;
            for (int a = 0; a < 5; a++) {
                for (int b = 0; b < 7; b++) {
                    cout << grid[a][b] << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

        void mark_grid(string x, string y, bool is_shot) {
            for (int a = 0; a < 5; a++) {
                if (y == grid[a][0]){
                    for (int b = 0; b < 7; b++) {
                        if (x == grid[4][b]){
                            if (is_shot == true){
                                cout << endl;
                                cout << "HIT";
                                cout << endl;
                                grid[a][b] = "X";
                            } else {
                                grid[a][b] = "⛴";
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
};


Board PlayerBoard;
Board EnemyBoard;


void startmenu(){
    cout << endl;
    cout << "******        **       ********    ********    **          ********     ******     **    **    **    ******    \n";
    cout << "**    **     ** **        **          **       **          **          **          **    **    **    **    **  \n";
    cout << "**    **    **   **       **          **       **          **          **          **    **    **    **    **  \n";
    cout << "******      *******       **          **       **          ********     ******     ********    **    ******    \n";
    cout << "**    **    **   **       **          **       **          **                **    **    **    **    **        \n";
    cout << "**    **    **   **       **          **       **          **                **    **    **    **    **        \n";
    cout << "******      **   **       **          **       ********    ********     ******     **    **    **    **        \n";
    cout << endl;
    sleep_for(seconds(2));

    cout << "Press ENTER to Start";
    cin.get();

    cout << endl;
    cout << "INSTRUCTIONS: \n";
    cout << "1. Position your ships on the grid (10 ships total ⛴ ). \n";
    cout << "2. Take turns attempting to sink the enemy ships by specifying firing coordinates. \n";
    cout << "3. A miss will be indicated by a 'O' and a hit will be indicated by an 'X'. \n";
    cout << "4. The enemy will try to sink your ships. \n";
    cout << "5. First to sink all the opposing ships wins! \n";
    cout << endl;
    sleep_for(seconds(2));

    cout << "Press ENTER to Acknowledge";
    cin.get();
}


void show_player_board() {
    cout << endl;
    cout << "PLAYER BOARD \n";
    PlayerBoard.show_board();
    cout << endl;
}


void show_enemy_board() {
    cout << endl;
    cout << "ENEMY BOARD \n";
    EnemyBoard.show_board();
    cout << endl;
}



string get_coordinate_x() {
    string coordinate;
    cout << "Input X Coordinate: ";
    cin >> coordinate;

    while (coordinate != "1" && coordinate != "2" && coordinate != "3" && coordinate != "4" && coordinate != "5" && coordinate != "6"){
        cout << "Please select 1, 2, 3, 4, 5, or 6: ";
        cin >> coordinate;
    }

    return coordinate;
}


string get_coordinate_y() {
    string coordinate;
    cout << "Input Y Coordinate: ";
    cin >> coordinate;

    while (coordinate != "a" && coordinate != "A" && coordinate != "b" && coordinate != "B" && coordinate != "c" && coordinate != "C" && coordinate != "d" && coordinate != "D"){
        cout << "Please select A, B, C, or D: ";
        cin >> coordinate;
    }

    if (coordinate == "a"){
        coordinate = "A";
    } else if (coordinate == "b"){
        coordinate = "B";
    } else if (coordinate == "c"){
        coordinate = "C";
    } else if (coordinate == "d"){
        coordinate = "D";
    }

    return coordinate;
}


void position_player_ships() {
    for (int a = 5; a > 0; a--) {
        show_player_board();
        cout << "Position Ship ("; cout << a; cout << " Remaining) \n";
        string ship_x = get_coordinate_x();
        string ship_y = get_coordinate_y();
        PlayerBoard.mark_grid(ship_x, ship_y, false);
    }
}


void fire() {
    string coordinate_x = get_coordinate_x();
    string coordinate_y = get_coordinate_y();

    EnemyBoard.mark_grid(coordinate_x, coordinate_y, true);
}


void enemy_fire() {
   string x_coordinates[6] = {"1", "2", "3", "4", "5", "6"};
   string y_coordinates[4] = {"A", "B", "C", "D"};

    srand(time(NULL));

    int x_index = (rand() % 6);
    int y_index = (rand() % 4);

    string x_pick = x_coordinates[x_index];
    string y_pick = y_coordinates[y_index];

    PlayerBoard.mark_grid(x_pick, y_pick, true);
}



int main() {

    startmenu();

    position_player_ships();

    sleep_for(seconds(1));
    show_enemy_board();
    show_player_board();

    fire();
    sleep_for(seconds(1));
    enemy_fire();
    sleep_for(seconds(1));

    show_enemy_board();

    show_player_board();

    return 0;
}