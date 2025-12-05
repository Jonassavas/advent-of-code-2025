#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool paperInPos(const char & c);
unsigned long long analyzeGrid(const std::vector<std::string> &grid);
void printVector(const std::vector<std::string>& v);

int main(){

    std::fstream file("../input.txt");
    if(!file.is_open()){
        std::cerr << "Could not open file. \n";
        return 1;
    }

    std::string line;
    std::vector<std::string> paperGrid;
    while(std::getline(file, line)){
        paperGrid.push_back(line);
    }

    file.close();
    
    std::cout<< "Free paper rolls: " << analyzeGrid(paperGrid) <<std::endl;

    return 0;
}


unsigned long long analyzeGrid(const std::vector<std::string> &grid){
    std::vector<std::string> resultGrid = grid;
    unsigned long long sumAccessablePaperRolls = 0;
    for(size_t i = 0; i < grid.size(); ++i){
        for(size_t j = 0; j < grid[i].size(); ++j){
            int adjacentPaperRolls = 0;
            if(!paperInPos(grid[i][j])){
                continue;;
            }
            // Up one step == grid[i-1][j]
            // Down one step == grid[i+1][j]
            // Left one step == grid[i][j-1]
            // Left one step == grid[i][j+1]
            // Diagonals
            // Up diagonal left == grid[i-1][j-1]
            // Up diagonal right == grid[i-1][j+1]
            // Down diagonal left == grid[i+1][j-1]
            // Up diagonal right == grid[i+1][j+1]

            // We can't go up one step if i == 0
            if(i != 0){
                // Up one step
                if(paperInPos(grid[i-1][j])){
                    ++adjacentPaperRolls;
                }
                // Up diagonal left
                if(j != 0){
                    if(paperInPos(grid[i-1][j-1])){
                        ++adjacentPaperRolls;
                    }
                }
                // Up diagonal right
                if(j != grid[i].size() - 1){
                    if(paperInPos(grid[i-1][j+1])){
                        ++adjacentPaperRolls;
                    }
                }
            }
            // We can't go down one step if i == grid.size()-1
            if(i != grid.size()-1){
                if(paperInPos(grid[i+1][j])){
                    ++adjacentPaperRolls;
                }

                // Down diagonal left
                if(j != 0){
                    if(paperInPos(grid[i+1][j-1])){
                        ++adjacentPaperRolls;
                    }
                }
                // Down diagonal right
                if(j != grid[i].size() - 1){
                    if(paperInPos(grid[i+1][j+1])){
                        ++adjacentPaperRolls;
                    }
                }
            }
            // we can't go left one step if j == 0
            if(j != 0){
                if(paperInPos(grid[i][j-1])){
                    ++adjacentPaperRolls;
                }
            }
            // We can't go to the right if j == grid[i].size()-1
            if(j != grid[i].size()-1){
                if(paperInPos(grid[i][j+1])){
                    ++adjacentPaperRolls;
                }
            }

            if(adjacentPaperRolls < 4){
                resultGrid[i][j] = 'x';
                ++sumAccessablePaperRolls;
            }
        }
    }
    //printVector(resultGrid);
    return sumAccessablePaperRolls;
}

bool paperInPos(const char & c){
    char paper = '@';
    char freePos = '.';
    if(c == paper){
        return true;
    }
    return false;
}

void printVector(const std::vector<std::string>& v) {
    for (const auto& s : v) {
        std::cout << s << '\n';
    }
}