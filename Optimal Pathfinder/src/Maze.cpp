#include "Maze.h"
#include <stack>
#include <iostream>

//variable and function declaration
extern int G_CONSOLE_WIDTH;
void separator(int size, bool type);

Maze::Maze() : m_costMin(99999), m_costMax(-99999), m_costPath(1){}
Maze::~Maze(){}

int Maze::pathFind(int sRow, int sCol)
{
    //alias for Current and all 4 adjacent locations
    auto& CURRENT = m_array(sRow, sCol);
    const auto& RIGHT = m_array(sRow, sCol+1);
    const auto& LEFT = m_array(sRow, sCol-1);
    const auto& UP = m_array(sRow-1, sCol);
    const auto& DOWN = m_array(sRow+1, sCol);

    //bolean for if adjacent is End(e) or Path(1)
    bool CHECK_END = (G_END == UP || G_END == DOWN || G_END == LEFT || G_END == RIGHT);
    bool CHECK_PATH = (G_PATH == UP || G_PATH == DOWN || G_PATH == LEFT || G_PATH == RIGHT);

    //if the current position is on End(e) then end path finding
    if(CURRENT == G_END)
    {
        //traverse the path and find its cost
        separator(G_CONSOLE_WIDTH, 1);
        m_array.display();
        std::cout << "\n";

        m_pathStack.display();
        printPoint(sRow, sCol);
        std::cout << "--END-- \n";

        std::cout << "Cost: " << m_costPath << "\n";
        std::cout << "\n";

        //find if current path has maximum or minimum cost
        if(m_costPath < m_costMin)
            m_costMin = m_costPath;
        if(m_costPath > m_costMax)
            m_costMax = m_costPath;

        return 0;
    }

    //if any adjacent position is the End(e) then go there
    if(CHECK_END)
    {
        //push point onto stack and add 1 to cost
        m_pathStack.push(sRow);
        m_pathStack.push(sCol);
        ++m_costPath;

        //set path to visited after traversing a path
        if(CURRENT != G_START)
            CURRENT = G_VISITED;

        //goto the end
        if(G_END == RIGHT)
            pathFind(sRow, sCol+1);
        else if(G_END == DOWN)
            pathFind(sRow+1, sCol);
        else if(G_END == LEFT)
            pathFind(sRow, sCol-1);
        else if(G_END == UP)
            pathFind(sRow-1, sCol);

        //set path to unvisited after traversing a path
        if(CURRENT != G_START)
            CURRENT = G_PATH;

        //pop the point and decrement cost
        m_pathStack.pop();
        m_pathStack.pop();
        --m_costPath;
    }

    //if any adjacent position is the Path(1) then go there
    if(CHECK_PATH)
    {
        //push point and increment cost
        m_pathStack.push(sRow);
        m_pathStack.push(sCol);
        ++m_costPath;

        //set current path to visited before traversing
        if(CURRENT != G_START)
            CURRENT = G_VISITED;

        //goto available paths
        if(G_PATH == RIGHT)
            pathFind(sRow, sCol+1);
        if(G_PATH == DOWN)
            pathFind(sRow+1, sCol);
        if(G_PATH == LEFT)
            pathFind(sRow, sCol-1);
        if(G_PATH == UP)
            pathFind(sRow-1, sCol);

        //set current path to visited before traversing
        if(CURRENT != G_START)
            CURRENT = G_PATH;

        //pop value and decrement cost
        m_pathStack.pop();
        m_pathStack.pop();
        --m_costPath;
    }

    //if there is no path remaining then end pathFinding
    return 0;
}

//print a point
void Maze::printPoint(int i, int j) { std::cout << i << j << " "; }


