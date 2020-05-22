/* 
 * Created on September 21, 2018, 4:05 PM */
#include <iostream>
#include "Maze.h"
#include <windows.h>

//global variable for console Width
extern int G_CONSOLE_WIDTH = 0;

//function to print separator
void separator(int size, bool type);

int main()
{
    //get width of console for separator size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    G_CONSOLE_WIDTH = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    Maze maze;
    //the maze array is read from the file named "Input.txt"
    maze.readFile("Input.txt");

    //display maze
    separator(G_CONSOLE_WIDTH, 0);
    std::cout << "MAZE\n\n";
    maze.displayMaze();
    std::cout << "\n";

    //find all possible path
    maze.pathFind(maze.findStartRow(), maze.findStartCol());

    //print maximum and minimum cost
    separator(G_CONSOLE_WIDTH, 0);
    std::cout << "Min Cost: " << maze.getMinCost() << "\n";
    std::cout << "Max Cost: " << maze.getMaxCost() << "\n\n";
    separator(G_CONSOLE_WIDTH, 0);
    return 0;
}

//if type is 0 then print (=), else print (-)
void separator(int size, bool type)
{
    for(int i = 0; i < size; ++i)
        if(!type)
            std::cout << "=";
        else
            std::cout << "-";
    std::cout << "\n";
}

