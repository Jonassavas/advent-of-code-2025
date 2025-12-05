#include <iostream>
#include <fstream>
#include <string>
#include <vector>

unsigned long long mostJoltage(const std::string &s);

int main(){

    std::ifstream file("../input.txt");
    if(!file.is_open()){
        std::cerr<< "Could not open file. \n";
        return 1;
    }

    std::string line;
    unsigned long long sumJoltage = 0;

    while(std::getline(file, line)){
        unsigned long long currJoltage = mostJoltage(line);
        std::cout<< "CURR JOLTAGE: " << currJoltage << std::endl;
        //std::cout<< "CURR: " <<currJoltage <<std::endl;
        sumJoltage += currJoltage;
    }


    file.close();

    std::cout<< "Sum Joltage: " << sumJoltage << std::endl;

    return 0;
}


unsigned long long mostJoltage(const std::string &s){
    int numsLeft = 12;
    unsigned long long maxJoltage = 0;

    // We iterate 12 times
    // We check from 0 to (s.size()-1)-12 == currIndex
    // Then we check from currIndex+1 --> (s.size()-1)-11 etc

    int currNumberIndex = 0;
    
    while(numsLeft > 0){
        int startIndex = currNumberIndex;
        int endIndex = s.size() - numsLeft; // 12 - 1
        int currNumber = 0;
        while(startIndex <= endIndex){
            if(s[startIndex]  - '0' > currNumber){
                currNumber = (s[startIndex]  - '0');
                currNumberIndex = startIndex;
            }
            startIndex++;
        }
        //std::cout<<"FOUND NUMBER: " << currNumber << std::endl;
        currNumberIndex++;
        maxJoltage = (maxJoltage * 10) + currNumber;
        //std::cout<<"MAX JOLTAGE: " << maxJoltage << std::endl;
        numsLeft--;
    }
    return maxJoltage;

}