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
//======================================================================
void print(int i, int j)
{
    std::cout << "(" << i << ", " << j << ")\n";
}
//===================================================================================================

//Alias for different type of characters in the array
const char G_PATH = '-';
const char G_WALL = '*';
const char G_START = 's';
const char G_END = 'e';
const char G_VISITED = '!';
const char G_VISITED2 = 'o';

Dynamic2dArray pathFind(Dynamic2dArray arr, int sRow, int sCol)
{
    //alias for Current and all 4 adjacent locations
    const auto& CURRENT = arr(sRow, sCol);
    const auto& RIGHT = arr(sRow, sCol+1);
    const auto& LEFT = arr(sRow, sCol-1);
    const auto& UP = arr(sRow-1, sCol);
    const auto& DOWN = arr(sRow+1, sCol);

    print(sRow, sCol);
    arr.writeFile("Output.txt", sRow, sCol);
    
    //if the current position is on End(e) then end pathfinding
    if(CURRENT == G_END)
    {
        std::cout << "Destination Reached\n";
        arr.writeFile("Output.txt", "Destination Reached");
        return arr;
    }
    //if current position is Path(-) or the Start(s) then mark this position as visited 
    if(CURRENT == G_PATH || CURRENT == G_START)
        arr(sRow, sCol) = G_VISITED;
    
    //if any adjacent position is the End(e) then go there
    if(G_END == UP)
        return pathFind(arr, sRow-1, sCol);
    else if(G_END == DOWN)
        return pathFind(arr, sRow+1, sCol);
    else if(G_END == LEFT)
        return pathFind(arr, sRow, sCol-1);
    else if(G_END == RIGHT)
        return pathFind(arr, sRow, sCol+1);
        
    //if any adjacent position is the Path(-) then go there
    else if(G_PATH == UP)
        return pathFind(arr, sRow-1, sCol);
    else if(G_PATH == DOWN)
        return pathFind(arr, sRow+1, sCol);
    else if(G_PATH == LEFT)
        return pathFind(arr, sRow, sCol-1);
    else if(G_PATH == RIGHT)
        return pathFind(arr, sRow, sCol+1);
    
    //if any adjacent position is the previously Visited(!) then go there and mark current as Visited Twice (o)
    else if(G_VISITED == UP || G_VISITED == DOWN || G_VISITED == LEFT || G_VISITED == RIGHT)
    {
        arr(sRow, sCol) = G_VISITED2;
        
        if(G_VISITED == UP)
            return pathFind(arr, sRow-1, sCol);
        else if(G_VISITED == DOWN)
            return pathFind(arr, sRow+1, sCol);
        else if(G_VISITED == LEFT)
            return pathFind(arr, sRow, sCol-1);
        else if(G_VISITED == RIGHT)
            return pathFind(arr, sRow, sCol+1);      
    }
    
    //if there is no path remaining then end pathFinding
    else
    {
        std::cout << "No path Remaining.\n";
        arr.writeFile("Output.txt", "No path Remaining");
        return arr;
    }
}
//===================================================================================================

int main()
{
    //remove old output file
    remove("Output.txt");
    
    Dynamic2dArray oldMaze;
    //the maze array is read from the file named "Input.txt"
    oldMaze.readFile("Input.txt");
    
    oldMaze.display();
    
    Dynamic2dArray newMaze;
    newMaze = pathFind(oldMaze, oldMaze.findRow('s'), oldMaze.findCol('s'));
    newMaze.display();
    
    //the coordinates and updated maze are saved in the file named "Output.txt"
    newMaze.writeFile("Output.txt");
    
    return 0;
}
//===================================================================================================

