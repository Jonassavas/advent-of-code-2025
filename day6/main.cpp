#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

long long add(long long a, long long b) { return a + b; }
long long sub(long long a, long long b) { return a - b; }
long long mul(long long a, long long b) { return a * b; }
long long divi(long long a, long long b) { return a / b; }

std::unordered_map<char, long long (*)(long long, long long)> op = {
    { '+', add },
    { '-', sub },
    { '*', mul },
    { '/', divi }
};

bool is_number(const std::string &s){
    if(s.empty()){
        return false;
    }
    for(char c : s){
        if(!std::isdigit(static_cast<unsigned char> (c))) return false;
    }
    return true;
}

long long sumOfOperations(std::vector<std::string> numbers, std::vector<char> symbols){
    int numsPerLine = symbols.size();
    long long currNumber = 0;
    long long sumCurrNumber = 0;
    for(int i = 0; i < numsPerLine; ++i){
        int j = numsPerLine + i;
        currNumber = std::stoll(numbers[i]);
        while(j < numbers.size()){
            std::cout<< currNumber << " = " << currNumber << " " << symbols[i] << " " << numbers[j] << std::endl;
            currNumber =  op[symbols[i]](currNumber, std::stoll(numbers[j]));
            std::cout<< "CURR SUM: " << currNumber <<std::endl;
            j += numsPerLine;
        }
        sumCurrNumber += currNumber;
    }

    return sumCurrNumber;
}


int main(){
    std::fstream file("../input.txt");

    if(!file.is_open()){
        std::cerr << "Could not open file. \n";
        return 1;
    }

    std::vector<std::string> numbers;
    std::vector<char> symbols;

    bool symbol_section = false;

    std::string line;
    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string token;
        char symbol;

        while(ss >> token){
            //std::cout<< "TOKEN: " << token << std::endl;
            if(!symbol_section){
                if(is_number(token)){
                    numbers.push_back(token);
                }else{
                    symbol_section = true;
                    symbol = token[0];
                    symbols.push_back(symbol);
                }
            }else{
                symbol = token[0];
                symbols.push_back(symbol);
            }
        }

        //std::cout<< "LINE: " << line << std::endl;

    }

    file.close();

    std::cout << "FINAL RESULT: " << sumOfOperations(numbers, symbols) << std::endl;;

    // std::cout << "NUMBERS:\n";
    // for (auto& n : numbers) std::cout << n << "\n";

    // std::cout << "\nSYMBOLS:\n";
    // for (auto& s : symbols) std::cout << s << "\n";


    return 0;
}