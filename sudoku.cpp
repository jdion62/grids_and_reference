#include <iostream>
#include <fstream>

//DECLARATIONS
bool is_safe(int x, int y, int curr, int *grid);
bool zeroes(int *grid);
int *spookdoku(int x, int y, int *grid);
int next_zero(int *grid, char r_c);
void fill_grid(char *fname, int *grid);


//MAIN METHOD
int main(int argc, char *argv[])
{
    /*
    int **grid = new int*[9];
    for(int i = 0; i < 9; ++i)
        grid[i] = new int[9];
    */
    int grid[81];

    fill_grid(argv[1], grid);

    int *fin = spookdoku(0, 0, grid);

    for(int i = 0; i < 9; ++i)
    {
        for(int j = 0; j < 9; ++j)
        {
            std::cout << fin[9 * i + j];
            if(j != 8)
                std::cout << ',';
        }

        std::cout << std::endl;
    }

     // free up heap
    //for(int i = 0; i < 9; i++)
        //delete[] grid[i];

    //delete[] grid;
    return 0;
}



//DEFINITIONS
bool is_safe(int x, int y, int curr, int *grid)
{
    //checks enire row and entire column simoultaniously, pretty cool eh?
    for(int i = 0; i < 9; ++i)
        if(grid[9 * y + i] == curr || grid[9 * i + x] == curr)
            return false;

    // /3, possible 0, 1, 2
    int temp_r = 3 * (y / 3);
    int temp_c = 3 * (x / 3);
    //check whole box
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            //9 is number of rows, desired row is y/3 to get box number, *3 to get to begining of box, +i to go through box
            if(grid[9 * (i+temp_r) + (j+temp_c)] == curr)
                return false;
    //grid[9 * y + x] = curr;
    return true;
}

bool zeroes(int *grid)
{
    for(int i = 0; i < 81; ++i)
        //if it finds a zero
        if(!grid[i])
            return true;

    return false;
}

int *spookdoku(int x, int y, int *grid)
{
    //if we are passed a solved grid
    if(!zeroes(grid)) return grid;
    //finds the row and column of next zero and stores row and col coordinates
    x = next_zero(grid, 'c');
    y = next_zero(grid, 'r');

    //atempting to put 1-9 in
    for(int k = 0; k < 9; ++k)
    {
        if(is_safe(x, y, k+1, grid))
        {
            grid[9 * y + x] = k+1;

            grid = spookdoku(x, y, grid);
            //if there are no zeroes left, we're done
            if(!zeroes(grid)) return grid;

            //so we can backtrack
            grid[9 * y + x] = 0;
        }
    }
    return grid;
    /*
    *the below are failed implementations, but they're cool enough to hang
    *in the event that I want to try to fix them later
    */
    /*if(!grid[9 * y + x])
        for(int k = test; k < 9; ++k)
            if(is_safe(x, y, k+1, grid))
                grid[9 * y + x] = k + 1;

    if(!zeroes(grid))
        return grid;

    if(x < 8)
        grid = spookdoku(x+1, y, test+1, grid);
    else
        grid = spookdoku(0, y+1, test+1, grid);
*/
    /*for(int i = y; i < 9; ++i)
        for(int j = x; j < 9; ++j)
        {
            if(grid[9 * i + j] == 0)
            {
                for(int k = 0; k < 9; ++k)
                {
                    if(is_safe(j, i, k+1, grid))
                    {
                        grid[9 * i + j] = k+1;

                        if(j < 8) grid = spookdoku(j+1, i, k+1, grid);
                        else grid = spookdoku(0, i+1, k+1, grid);

                        if(!zeroes(grid)) return grid;

                        grid[9 * i + j] = 0;
                    }
                }
            }
        }*/
}

int next_zero(int *grid, char r_c)
{
    //i is row j is coloumn
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
            if (grid[9 * i + j] == 0)
            {
                if (r_c == 'r')
                    return i;

                else
                    return j;
            }

    return -1;
}

// reads from file and put in 2d array
void fill_grid(char *fname, int *grid)
{
    std::ifstream infile;
    infile.open(fname);

    char a;
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < 9; ++j)
        {
            infile.get(a);
            if(47 < a && a < 58)
                grid[9 * i + j] = (a-48);

            // this else ensures the space, commas, and new line characters will not be counted in the dimensions
            else
                --j;
        }
    infile.close();
}