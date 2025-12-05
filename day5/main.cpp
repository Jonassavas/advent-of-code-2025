#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

bool validID(const std::vector<std::tuple<long long, long long>> &rangesVec, 
            const long long &id);

int main(){
    std::fstream file("../input.txt");

    if(!file.is_open()){
        std::cerr << "Could not open file. \n";
        return 1;
    }

    std::string line;
    bool readRanges = true;
    long long nrValidIds = 0;
    std::vector<std::tuple<long long, long long>> rangesVec;
    while(std::getline(file, line)){
        if(!line.empty() && line.back() == '\r'){
            line.pop_back();
        }

        if(line.empty()){
            readRanges = false;
            continue;
        }

        if(readRanges){
            size_t dashPos = line.find('-');
            if(dashPos == std::string::npos){
                std::cerr << "Bad range format" << line << "\n";
                return 1;
            }
            std::string firstStr = line.substr(0, dashPos);
            std::string secondStr = line.substr(dashPos+1);

            long long firstNum = std::stoll(firstStr);
            long long secondNum = std::stoll(secondStr);

            rangesVec.push_back({firstNum, secondNum});

            //std::cout << "RANGE: " << firstStr << "-" << secondStr << std::endl;
        }else{
            long long idToCheck = std::stoll(line);
            bool valid = validID(rangesVec, idToCheck);
            if(valid){
                nrValidIds++;
            }
            //std::cout<< "LINE: " << idToCheck << " Valid? " << (valid ? "YES" : "NO") << std::endl;
        }
        


    }

    file.close();

    std::cout<< "Nr valid IDs: " << nrValidIds << std::endl;

    return 0;
}

bool validID(const std::vector<std::tuple<long long, long long>> &rangesVec, 
            const long long &id){

    for(int i = 0; i < rangesVec.size(); ++i){
        long long first = std::get<0>(rangesVec[i]);
        long long second = std::get<1>(rangesVec[i]);

        if(id >= first && id <= second){
            return true;
        }
    }
    return false;
}