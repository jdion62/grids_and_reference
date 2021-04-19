#include <iostream>
#include <fstream>
#include <string>

//DECLARATIONS
//int str_to_int(char *str);
void fill_grid(char *fname, int r, int c, int **grid);
void remove_blob(int x, int y, int r, int c, int con, int **grid);


//MAIN METHOD
int main(int argc, char *argv[])
{
    // rows and column, converted from ASCII to dec
    int r = atoi(argv[2]);
    int c = atoi(argv[3]);

    // 2d grid on heap, will function as input from file
    int **grid = new int*[r];
    for(int i = 0; i < r; ++i)
        grid[i] = new int[c];

    fill_grid(argv[1], r, c, grid);

    int result = 0;

    // could have turned these values into more variables, but we only used them once so I was ok with this
    for(int y = 0; y < r; ++y)
        for(int x = 0; x < c; ++x)
            if(grid[y][x] == 1)
            {
                remove_blob(x, y, r, c, atoi(argv[4]), grid);
                ++result;
            }

    std::cout << result << std::endl;

    // free up heap
    for(int i = 0; i < r; i++)
        delete[] grid[i];

    delete[] grid;
    return 0;
}


//DEFINITIONS

//I kept getting weird errors and I asked my friend if he made a function like this and
//my friend told me I was an idiot and should just use atoi()
/*
int str_to_int(char *str)
{
    if(!str[1])
        return str[0] - 48;
    //add 10 to ones place if is 2 digits (largest posible number is 16)
    return str[1] - 38;
}
*/

// reads from file and put in 2d array
void fill_grid(char *fname, int row, int col, int **grid)
{
    std::ifstream infile;
    infile.open(fname);
    int r = 0;
    int c = 0;
    int val = 0;
    std::string line;
    std::string curr;

    while(std::getline(infile, line))
    {
        for(int i = 0; i<= line.length(); ++i)
        {
            if(*&line[i] != '\0' && *&line[i] != '\n' && *&line[i] != ' ')
                curr += *&line[i];
            else
            {
                val = std::stoi(curr);
                curr.clear();
                grid[r][c] = val;
                c++;
                if(c == col)
                {
                    r++;
                    c = 0;
                }
            }
        }
    }
    infile.close();
}

// counts size of blob
void remove_blob(int x, int y, int r, int c, int con, int **grid)
{
    // if it finds a 0, no need to check surrounding values
    if(grid[y][x] == 0)
        return;

    // turns to a zero so we don't double count the element
    grid[y][x] = 0;


    // will check adjacent (up, down, left, right) to see if it exists, if it does, recursivly checks that number
    if(x != 0)
        remove_blob(x-1, y, r, c, con, grid);
    if(x != r-1)
        remove_blob(x+1, y, r, c, con, grid);

    if(y != 0)
        remove_blob(x, y-1, r, c, con, grid);
    if(y != c-1)
        remove_blob(x, y+1, r, c, con, grid);


    // if connectivity is eight we must also check the diagonal
    if(con == 8)
    {
        if(x != 0)
        {
            if(y != 0)
                remove_blob(x-1, y-1, r, c, con, grid);
            if(y != c-1)
                remove_blob(x-1, y+1, r, c, con, grid);
        }

        if(x != r-1)
        {
            if(y != 0)
                remove_blob(x+1, y-1, r, c, con, grid);
            if(y != c-1)
                remove_blob(x+1, y+1, r, c, con, grid);
        }

    }
}