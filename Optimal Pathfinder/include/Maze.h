#include "DynamicArray.h"
#include "Stack.h"
#include <iostream>
#include <cstring>

#ifndef MAZE_H
#define MAZE_H

class Maze
{
    public:
        Maze();
        ~Maze();

        void readFile(const char * str) { m_array.readFile(str); }
        int findStartRow() {return m_array.findRow('s'); }
        int findStartCol() {return m_array.findCol('s'); }

        int getMinCost() const { return m_costMin; }
        int getMaxCost() const { return m_costMax; }

        int pathFind(int sRow, int sCol);
        void printPoint(int i, int j);
        void displayMaze() const { m_array.display(); }
        void printSeparator(int n);

    private:
        int m_costPath;
        int m_costMin;
        int m_costMax;
        Dynamic2dArray m_array;
        Stack<int, 100> m_pathStack;

        //Alias for different type of characters in the array
        const char G_PATH = '1';
        const char G_WALL = '0';
        const char G_START = 's';
        const char G_END = 'e';
        const char G_VISITED = 'x';
        const char G_VISITED2 = '-';
};

#endif // MAZE_H
