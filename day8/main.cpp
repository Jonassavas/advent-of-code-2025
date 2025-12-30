#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

/*
    Each row is the position in 3D space
    x, y, z
*/


int main(){
    std::fstream file("../input.txt");

    if(!file.is_open()){
        std::cerr << "Could not open file. \n";
        return 1;
    }

    std::vector<std::vector<int>> boxPositions;
    std::vector<int> boxConnections(0);

    std::string line;
    while(std::getline(file, line)){
        std::stringstream ss(line);

        std::string token;

        std::vector<int> row;
        while(std::getline(ss, token, ',')){
            row.push_back(std::stoi(token));
        }

        if(row.size() == 3){
            boxPositions.push_back(row);
        }

    }

    file.close();

    return 0;
}