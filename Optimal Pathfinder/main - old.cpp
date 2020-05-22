/* 
 * Created on September 21, 2018, 4:05 PM */
#include <iostream>
#include <string.h>
#include <fstream>
//===================================================================================================

class Dynamic2dArray {
private:
    char **m_array;
    int m_row;
    int m_col;
    char m_invalidMem = 0;    //a variable to be returned in bound check overload to show invalid data

private:
    void clearArray()
    {
        //if array is not empty than delete allocated memory
        if(m_array != nullptr)
        {
            for(int i = m_row - 1; i >= 0; --i)
            {
                if(m_array[i] != nullptr)
                {
                    delete[] m_array[i];
                    m_array[i] = nullptr;
                }
            }
            delete[] m_array;
        }
        m_array = nullptr;
    }

public:
    Dynamic2dArray()
    {
        m_array = nullptr;
        m_row = 0;
        m_col = 0;
    }
    Dynamic2dArray(const Dynamic2dArray &obj)
    {
        m_array = nullptr;
        m_row = 0;
        m_col = 0;
        *this = obj;    //call = operator
    }
    Dynamic2dArray(int r, int c)
    {
        m_row = r;
        m_col = c;
        m_array = new char*[m_row];

        for(int i = 0; i < m_row; ++i)
        {
            m_array[i] = new char[m_col];
            //initialize 2d array to character '?'
            for(int j = 0; j < m_col; ++j)
                m_array[i][j] = '?';
        }
    }
    ~Dynamic2dArray()
    {
        clearArray();
    }

    int getRow() const {return m_row;}
    int getCol() const {return m_col;}

    //read data from the file
    void readFile(const char* fileName)
    {
        std::ifstream inf(fileName);
        //if file cannot open
        if(!inf)
        {
            std::cout << "Cannot open File " << fileName << std::endl;
            std::cin.get();
            exit(1);
        }
        clearArray();

        inf >> m_row;
        inf >> m_col;

        m_array = new char*[m_row];

        for(int i = 0; i < m_row; ++i)
        {
            m_array[i] = new char[m_col];
        }

        for(int i = 0; i < m_row; ++i)
        {
            for(int j = 0; j < m_col; ++j)
            {
                char ch;
                if(!inf)
                {
                    std::cout << "File Format is Invalid for " << fileName << std::endl;
                    std::cin.get();
                    exit(1);
                }
                //read characters from file and save in array
                inf >> ch;
                m_array[i][j] = ch;
            }
        }
    }

    //write the whole array into a file
    void writeFile(const char* fileName)
    {
        std::ofstream outf(fileName, std::ios::app);
        outf << "\n";
        for(int i = 0; i < m_row; ++i)
        {
            for(int j = 0; j < m_col; ++j)
            {
                outf << m_array[i][j] << " ";
            }
            outf << "\n";
        }
    }

    //write only a single coordinate onto file
    void writeFile(const char* fileName, int i, int j)
    {
        std::ofstream outf(fileName, std::ios::app);
        outf << "(" << i << ", " << j << ")\n";
    }

    //write a string on the file
    void writeFile(const char* fileName, const char* str)
    {
        std::ofstream outf(fileName, std::ios::app);
        outf << str << "\n";
    }

    //return the row in which the character is found
    int findRow(char find)
    {
        for(int i = 0; i < m_row; ++i)
        {
            for(int j = 0; j < m_col; ++j)
            {
                if(m_array[i][j] == find)
                    return i;
            }
        }
        std::cout << "Character " << find << " not found\n";
        return -1;
    }

    //return the column in which the character is found
    int findCol(char find)
    {
        for(int i = 0; i < m_row; ++i)
        {
            for(int j = 0; j < m_col; ++j)
            {
                if(m_array[i][j] == find)
                    return j;
            }
        }
        std::cout << "Character " << find << " not found\n";
        return -1;
    }

    //fill the whole array with a character provided by user
    void fillArray(char ch)
    {
        for(int i = 0; i < m_row; ++i)
            for(int j = 0; j < m_col; ++j)
                m_array[i][j] = ch;
    }

    //display the array
    void display()
    {
        for(int i = 0; i < m_row; ++i)
        {
            for(int j = 0; j < m_col; ++j)
            {
                std::cout << m_array[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    //make sure the array is inside bound
    char& operator() (int i, int j)
    {
        if((i >= 0 && i < m_row) && (j >= 0 && j < m_col))
            return m_array[i][j];
        else
            return m_invalidMem;    //return address of invalid memory if array is out of bound
    }


    Dynamic2dArray& operator= (const Dynamic2dArray &obj)
    {
        if(this == &obj)
            return *this;

        //clear data from array
        clearArray();
        this->m_row = obj.m_row;
        this->m_col = obj.m_col;
        m_array = new char*[m_row];

        //copy data from object to current object
        for(int i = 0; i < m_row; ++i)
        {
            m_array[i] = new char[m_col];
            memcpy(m_array[i], obj.m_array[i], sizeof(char) * m_col);
        }
        return *this;
    }
};
//===================================================================================================
void print(int i, int j)
{
    std::cout << i << j << " -> ";
}
//===================================================================================================

//Alias for different type of characters in the array
const char G_PATH = '1';
const char G_WALL = '0';
const char G_START = 's';
const char G_END = 'e';
const char G_VISITED = 'x';
const char G_VISITED2 = '-';

//===================================================================================================
int printPath(Dynamic2dArray arr, int i, int j)
{
    int cost = 0;
    //while path does not end
    while(arr(i, j) != G_END)
    {
        print(i, j);

        //if adjecent is End(e) then go there
        if(arr(i-1, j) == G_END)
            --i;
        else if(arr(i+1, j) == G_END)
            ++i;
        else if(arr(i, j-1) == G_END)
            --j;
        else if(arr(i, j+1) == G_END)
            ++j;

        //if adjecent is Path(1) then go there
        else if(arr(i-1, j) == G_VISITED || arr(i+1, j) == G_VISITED || arr(i, j-1) == G_VISITED || arr(i, j+1) == G_VISITED)
        {
            arr(i, j) = G_VISITED2;
            if(arr(i-1, j) == G_VISITED)
                --i;
            else if(arr(i+1, j) == G_VISITED)
                ++i;
            else if(arr(i, j-1) == G_VISITED)
                --j;
            else if(arr(i, j+1) == G_VISITED)
                ++j;
        }
        ++cost;
    }
    print(i, j);
    ++cost;
    return cost;
}

//===================================================================================================

int pathFind(Dynamic2dArray arr, int sRow, int sCol)
{
    //alias for Current and all 4 adjacent locations
    auto& CURRENT = arr(sRow, sCol);
    const auto& RIGHT = arr(sRow, sCol+1);
    const auto& LEFT = arr(sRow, sCol-1);
    const auto& UP = arr(sRow-1, sCol);
    const auto& DOWN = arr(sRow+1, sCol);

    //bolean for if adjecent is End(e) or a Path(1)
    bool CHECK_END = (G_END == UP || G_END == DOWN || G_END == LEFT || G_END == RIGHT);
    bool CHECK_PATH = (G_PATH == UP || G_PATH == DOWN || G_PATH == LEFT || G_PATH == RIGHT);

    print(sRow, sCol);

    //if the current position is on End(e) then end pathfinding
    if(CURRENT == G_END)
    {
        //traverse the path and find its cost
        //int cost = printPath(arr, arr.findRow('s'), arr.findCol('s'));
        std::cout << "End \n";
        //std::cout << "(Cost = " << cost << ")\n";
        arr.display();
        std::cout << "\n";

        return 0;
    }

    //if any adjacent position is the End(e) then go there
    if(CHECK_END)
    {
        if(CURRENT != G_START)
            CURRENT = G_VISITED;

        if(G_END == UP)
            pathFind(arr, sRow-1, sCol);
        else if(G_END == DOWN)
            pathFind(arr, sRow+1, sCol);
        else if(G_END == LEFT)
            pathFind(arr, sRow, sCol-1);
        else if(G_END == RIGHT)
            pathFind(arr, sRow, sCol+1);

        if(CURRENT != G_START)
            CURRENT = G_PATH;
    }

    //if any adjacent position is the Path(1) then go there
    if(CHECK_PATH)
    {
        if(CURRENT != G_START)
            CURRENT = G_VISITED;

        if(G_PATH == UP)
            pathFind(arr, sRow-1, sCol);
        if(G_PATH == DOWN)
            pathFind(arr, sRow+1, sCol);
        if(G_PATH == LEFT)
            pathFind(arr, sRow, sCol-1);
        if(G_PATH == RIGHT)
            pathFind(arr, sRow, sCol+1);

        if(CURRENT != G_START)
            CURRENT = G_PATH;
    }

    //if there is no path remaining then end pathFinding
    if(!CHECK_PATH && !CHECK_END)
    {
        std::cout << "No Path \n";
        arr.display();
        return 0;
    }

}
//===================================================================================================

int main()
{
    Dynamic2dArray maze;
    //the maze array is read from the file named "Input.txt"
    maze.readFile("Input.txt");

    std::cout << "Maze\n========\n";
    maze.display();
    std::cout << "\n";

    pathFind(maze, maze.findRow('s'), maze.findCol('s'));

    return 0;
}
//===================================================================================================

