#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int mostJoltage(const std::string &s);

int main(){

    std::ifstream file("../input.txt");
    if(!file.is_open()){
        std::cerr<< "Could not open file. \n";
        return 1;
    }

    std::string line;
    unsigned long long sumJoltage = 0;

    while(std::getline(file, line)){
        int currJoltage = mostJoltage(line);
        //std::cout<< "CURR: " <<currJoltage <<std::endl;
        sumJoltage += currJoltage;
    }


    file.close();

    std::cout<< "Sum Joltage: " << sumJoltage << std::endl;

    return 0;
}


int mostJoltage(const std::string &s){
    int firstNum = 0;
    int secondNum = 0;
    int firstNumIndex = 0;
    for(int i = 0; i <= s.size() - 2; ++i){
        // Find the max number
        if(s[i]  - '0' > firstNum){
            firstNum = s[i]  - '0';
            firstNumIndex = i;
        }
    }
    //std::cout<<"Found first num: " << firstNum << std::endl;
    if(firstNumIndex == s.size() - 2){
        secondNum = s[s.size() - 1] - '0';
    }else{
        int secondNumIndex = firstNumIndex + 1;
        while(secondNumIndex <= s.size() - 1){
            if(s[secondNumIndex] - '0' > secondNum){
                secondNum = s[secondNumIndex] - '0';
            }
            secondNumIndex++;
        }
    }
    //std::cout << "FOUND second num: " << secondNum << std::endl;
    int result = firstNum*10 + secondNum;
    return result;

}