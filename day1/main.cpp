#include <iostream>
#include <fstream>
#include <string>

int main(){
    std::ifstream file("input.txt");
    if(!file.is_open()){
        std::cerr << "Failed to open the file. \n";
        return 1;
    }

    std::string line;
    bool positive = false;
    int currValue = 50; // The dial starts at 50
    int password = 0;
    int maxValue = 100;
    while(std::getline(file, line)){
        //std::cout<< "Line: " + line <<std::endl;

        if(line[0] == 'R'){
            positive = true;
        }else{
            positive = false;
        }

        // Convert all but the first chars to an integer
        int value = std::stoi(line.substr(1));

        //std::cout<< positive << " VALUE: " << value << std::endl;

        std::cout<< "Dial is rotated ";
        if(positive){
            currValue = (currValue + value) % maxValue;
            std::cout<< "R" << value << " to point at " << currValue << std::endl;
        }else{
            currValue = (currValue - value);
            while(currValue < 0){
                currValue += maxValue;
            }
            std::cout<< "L" << value << " to point at " << currValue << std::endl;
        }

        if(currValue == 0){
            ++password;
        }
    }

    file.close();

    std::cout<<"Password: " << password << std::endl;

    return 0;
}