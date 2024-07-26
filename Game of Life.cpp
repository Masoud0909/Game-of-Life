/*The “game of life” simulates the behaviour of a population of living cells that evolves from one generation to
the next.
A population is represented by a n x m two-dimensional array of cells, each cell being in one of two different
states: alive or dead.
Each cell has 8 neighbouring cells surrounding it, and the next generation of cells is generated according to
the following rules:
1. Any live cell with fewer than 2 live neighbours dies, as if caused by under-population.
2. Any live cell with more than 3 live neighbours dies, as if by overcrowding.
3. Any live cell with 2 or 3 live neighbours lives on to the next generation.
4. Any dead cell with exactly 3 live neighbours becomes a live cell, as if by reproduction.
You are asked to write a program to simulate the game of life*/

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

//Global Constants 
const int MAXGEN = 3; //maximum number of generations
const int n = 10;     //no. of rows
const int m = 10;     //no. of columns

//Function to intialize the grid with user input
void initialize(int arr[n][m]) {
    cout << "Enter the initial configuration of the grid (0 for dead, 1 for alive): " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
}
//function to initilize the grid randomly based on a density precentage
void  initialize2(int arr[n][m], int density) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m;j++) {
            int num = rand() % 100; //Generate a number between 0 to 99
            if (num < density) {
                arr[i][j] = 1;//Cell is alive
            }
            else {
                arr[i][j] = 0;//Cell is dead
            }
        }
    }
}

//Function to count the number of live neighbours around a given cell
int countNeighbour(int arr[n][m], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0)//Skip the current cell
                continue;
            int newX = (x + i + n) % n;//Wrap around the grid horizontally
            int newY = (y + j + m) % m;//Wrap around the grid vertically
            count += arr[newX][newY];
        }
    }
    return count;
}

//Function to check if all the cell in the grid are dead
bool allDead(int arr[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 1)//if any cell is alive
                return false;
        }
    }
    return true; // all cells are dead
}

//Function to create the next generation of the grid
void reproduce(int arr[n][m], int nextGen[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int liveNeighbours = countNeighbour(arr, i, j);//count live neighbours
            if (arr[i][j] == 1 && (liveNeighbours < 2 || liveNeighbours> 3)) {
                nextGen[i][j] = 0; //cell Dies!
            }
            else if (arr[i][j] == 0 && liveNeighbours == 3) {
                nextGen[i][j] = 1;//Cell becomes alive!
            }
            else {
                nextGen[i][j] = arr[i][j];//cell state remains the same
            }
        }
    }
}

//Function to print the grid

void print(int arr[n][m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 1) {
                cout << '1' << " ";//Alive cell
            }
            else {
                cout << '0' << " ";//dead cell
            }
        }
        cout << endl;
    }
}
int main()
{
    int grid[n][m];     //current generation grid
    int nextGen[n][m];  //Next generation grid 
    int choice;

    //prompt user to choose intializiation method:
    cout << "Choose initialization method (1 for manual, 2 for random): ";
    cin >> choice;
    if (choice == 1) {
        initialize(grid);//Manual initialization    
    }
    else {
        int density;
        //prompt user for density in random initialization
        cout << "Enter the density for random initialization (0-100): ";
        cin >> density;
        initialize2(grid, density);//Random initialization
    }
    //Print the initial population
    cout << "Initial Population: \n";
    print(grid);

    int gen = 1;

    while (gen <= MAXGEN && !allDead(grid)) {
        cout << "gen = " << gen << endl;
        reproduce(grid, nextGen);//Create next Generation

        //Copy the next generation to the current grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                grid[i][j] = nextGen[i][j];
            }
        }
        print(grid);//Print the current generation
        gen++;//Increment generation count
    }
    return 0;
}
