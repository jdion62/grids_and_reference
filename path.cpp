#include <iostream>
#include <fstream>
#include <string>

//DECLARATIONS
int find_min(int r, int c, int **grid, bool r_c);
int find_max(int r, int c, int **grid, bool r_c);
bool is_path(int curr_r, int curr_c, int r, int c, int end_r, int end_c, bool *vis, int **grid);
//int str_to_int(char *str);
void fill_grid(char *fname, int row, int col, int **grid);




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

    bool visited[r*c];

    for(int i = 0; i < r*c; ++i)
        visited[i] = 0;

    fill_grid(argv[1], r, c, grid);

    int min_r = find_min(r, c, grid, true);
    int min_c = find_min(r, c, grid, false);

    int max_r = find_max(r, c, grid, true);
    int max_c = find_max(r, c, grid, false);

    bool fin = is_path(min_r, min_c, r, c, max_r, max_c, visited, grid);

    std::cout << min_r+1 << ' ' << min_c+1 << ' ' << max_r+1 << ' ' << max_c+1 << ' ';

    if(fin)
        std::cout << "yes" << std::endl;

    else
        std::cout << "no" << std::endl;

    // free up heap
    for(int i = 0; i < r; i++)
        delete[] grid[i];

    delete[] grid;
    return 0;
}




//DEFINITIONS
int find_min(int r, int c, int **grid, bool r_c)
{
    int min = grid[0][0];
    int x = 0;
    int y = 0;

    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
            if(min > grid[i][j])
            {
                min = grid[i][j];
                y = i;
                x = j;
            }

    if(r_c)
        return y;

    return x;
}

int find_max(int r, int c, int **grid, bool r_c)
{
    int max = grid[0][0];
    int x = 0;
    int y = 0;

    for(int i = 0; i < r; ++i)
        for(int j = 0; j < c; ++j)
            if(max < grid[i][j])
            {
                max = grid[i][j];
                y = i;
                x = j;
            }

    if(r_c)
        return y;

    return x;
}


bool is_path(int curr_r, int curr_c, int r, int c, int end_r, int end_c, bool *vis, int **grid)
{
    bool done = false;

    if(grid[curr_r][curr_c] == grid[end_r][end_c])
        return true;

    if(curr_r != 0)
        if(grid[curr_r][curr_c] <= grid[curr_r-1][curr_c] && !vis[c * (curr_r-1) + curr_c])
        {
            vis[c * curr_r + curr_c] = true;
            done = is_path(curr_r-1, curr_c, r, c, end_r, end_c, vis, grid);
            if(done) return done;
        }
    if(curr_c != c-1)
        if(grid[curr_r][curr_c] <= grid[curr_r][curr_c+1] && !vis[c * curr_r + curr_c + 1])
        {
            vis[c * curr_r + curr_c] = true;
            done = is_path(curr_r, curr_c+1, r, c, end_r, end_c, vis, grid);
            if(done) return done;
        }
    if(curr_c != 0)
        if(grid[curr_r][curr_c] <= grid[curr_r][curr_c-1] && !vis[c * curr_r + curr_c - 1])
        {
            vis[c * curr_r + curr_c] = true;
            done = is_path(curr_r, curr_c-1, r, c, end_r, end_c, vis, grid);
            if(done) return done;
        }
    if(curr_r != r-1)
        if(grid[curr_r][curr_c] <= grid[curr_r+1][curr_c] && !vis[c * (curr_r+1) + curr_c])
        {
            vis[c * curr_r + curr_c] = true;
            done = is_path(curr_r+1, curr_c, r, c, end_r, end_c, vis, grid);
            if(done) return done;
        }

    if(curr_r == end_r && curr_c == end_c)
        return true;

    return false;
}

//I kept getting weird errors and I asked my friend if he made a function like this and
//my friend told me I was an idiot and should just use atoi()
/*
int str_to_int(char *str)
{
    if(!str[1])
        return str[0] - 48;
    //add 10 if is 2 digits
    if(!str[2])
        return (str[1] - 48) + ((str[0]-48)*10);

    return 100;
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