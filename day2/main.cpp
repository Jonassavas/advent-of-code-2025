#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string incrementStringNumber(std::string s);

int main(){
    std::ifstream file("../input.txt");
    if(!file.is_open()){
        std::cerr << "Failed to open the file. \n";
        return 1;
    }

    // Its just one line
    std::string range;
    std::vector<std::string> idRanges;
    int invalidIds = 0;
    long long sumInvalidIds = 0;
    while(std::getline(file, range, ',')){
        // We now get ranges like: 1231-2342
        // We split that again
        if(!range.empty() && range.back() == '\n'){
            range.pop_back();
        }

        size_t dashPos = range.find('-');
        if(dashPos == std::string::npos){
            std::cerr << "Bad range format: " << range << "\n";
            continue;
        }

        std::string firstStr = range.substr(0, dashPos);
        std::string lastStr = range.substr(dashPos+1);
        std::cout << "Range: " << firstStr << " to " << lastStr << "\n";

        long long first = std::stoll(firstStr);
        long long last = std::stoll(lastStr);

        // Analyze Range
        std::string firstHalf;
        std::string secondHalf;
        while(first <= last){
            firstHalf = firstStr.substr(0, firstStr.size()/2);
            secondHalf = firstStr.substr(firstStr.size()/2);
            if(firstHalf == secondHalf){
                ++invalidIds;
                sumInvalidIds += first;
                std::cout<<"FOUND: " << firstHalf << secondHalf << std::endl;
            }
            ++first;
            firstStr = incrementStringNumber(firstStr);
        }


        
        //std::cout<< "FIRSTHALF: " << firstStr.substr(0, firstStr.size()/2) << std::endl;
        //std::cout<< "SECONDHALF: " << firstStr.substr(firstStr.size()/2) << std::endl;
        std::cout<< "Invalid IDs: " << invalidIds << std::endl;
    }

    std::cout<< "Total Number of Invalid IDs: " << invalidIds << std::endl;
    std::cout<< "Sum Invalid IDs: " << sumInvalidIds << std::endl;
}


std::string incrementStringNumber(std::string s){
    long long stringNumber = std::stoll(s);
    stringNumber++;
    return std::to_string(stringNumber);
}