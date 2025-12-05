#include <iostream>
#include <fstream>
#include <string>
#include <vector>


int main(){

    std::fstream file("../input.txt");
    if(!file.is_open()){
        std::cerr << "Could not open file. \n";
        return 1;
    }

    std::string line;
    while(std::getline(file, line)){




    }

    file.close()

    return 0;
}