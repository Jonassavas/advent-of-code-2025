#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void printVector(const std::vector<std::string>& v) {
    std::cout<<"NEW" <<std::endl;
    for (const auto& s : v) {
        std::cout << s << '\n';
    }
}

void sendBeam(int stringPos, int vectorPos, std::vector<std::string> &inputLines){
    // We send where we want to shoot
    char currChar = inputLines[vectorPos][stringPos];
    if(currChar == '|') return;

    if(currChar == '.') inputLines[vectorPos][stringPos] = '|';
    else if(currChar == '^'){
        sendBeam(stringPos+1, vectorPos, inputLines);
        sendBeam(stringPos-1, vectorPos, inputLines);
    }
    printVector(inputLines);
}


long long calcBeamSplit(int beamStart, std::vector<std::string> &inputLines){
    // Check below the beamStart, or currBeam
    // If there is a splitter there, then again check for a splitter next to it
    // If its empty, then put the beam there

    sendBeam(beamStart, 1, inputLines); // Send the first beam under S

    // Skip the first line
    for(int i = 1; i<inputLines.size(); ++i){
        for(auto &c : inputLines[i]){
            
        }
    }

    return 1;
}


int main(){
    std::fstream file("../input1.txt");

    if(!file.is_open()){
        std::cerr << "Could not open file. \n";
        return 1;
    }

    std::string line;
    std::vector<std::string> inputLines;
    while(std::getline(file, line)){
        inputLines.push_back(line);
    }

    // Find the beam entrance location
    int beamStart = 0;
    for(int i = 0; i<inputLines[0].size(); ++i){
        char c = inputLines[0][i];
        if(c == 'S'){
            beamStart = i;
            break;
        }
    }

    long long result = calcBeamSplit(beamStart, inputLines);

    file.close();

    return 0;
}