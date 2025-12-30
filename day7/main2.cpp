#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void printVector(const std::vector<std::string>& v) {
    //std::cout<<"NEW" <<std::endl;
    for (const auto& s : v) {
        std::cout << s << '\n';
    }
}

void sendBeam(int stringPos, int vectorPos, std::vector<std::string> &inputLines, long long &nrSplits){
    // We send where we want to shoot
    char currChar = inputLines[vectorPos][stringPos];
    if(currChar == '|') return;

    if(currChar == '.') inputLines[vectorPos][stringPos] = '|';
    else if(currChar == '^'){
        ++nrSplits;
        sendBeam(stringPos+1, vectorPos, inputLines, nrSplits);
        sendBeam(stringPos-1, vectorPos, inputLines, nrSplits);
    }
}


long long calcBeamSplit(int beamStart, std::vector<std::string> &inputLines, long long &nrSplits){
    // Check below the beamStart, or currBeam
    // If there is a splitter there, then again check for a splitter next to it
    // If its empty, then put the beam there

    sendBeam(beamStart, 1, inputLines, nrSplits); // Send the first beam under S
    // Skip the first line
    for(int i = 1; i<inputLines.size()-1; ++i){
        for(int j = 0; j < inputLines[i].size(); ++j){
            char currChar = inputLines[i][j];
            if(currChar == '|'){
                sendBeam(j, i+1, inputLines, nrSplits); // Go down one step and send the beam
            }
        }
        std::cout<<"Nr splits: " << nrSplits << std::endl;
        printVector(inputLines);
    }


    // calculate part 2:
    bool containsCaret = false;
    long long timeLines = 0;
    for(int i = 0; i<inputLines.size(); ++i){
        long long currTimeLines = 0;
        for(int j = 0; j < inputLines[i].size(); ++j){
            char currChar = inputLines[i][j];
            if(currChar == '^') containsCaret = true;
            if(currChar == '|'){
                currTimeLines++;
            }
        }
        if(containsCaret){
            timeLines += currTimeLines;
        }
        containsCaret = false;
    }

    return timeLines;
}

long long countTimelines(const std::vector<std::string>& grid) {
    int gridHeight = grid.size();
    int gridWidth = grid[0].size();

    std::vector<std::vector<long long>> ways(
        gridHeight, std::vector<long long>(gridWidth, 0)
    );

    int start = grid[0].find('S');
    ways[0][start] = 1;

    for (int row = 0; row < gridHeight - 1; ++row) {
        for (int col = 0; col < gridWidth; ++col) {
            long long w = ways[row][col]; // Take the current ways to get to a position
            if (w == 0) continue; // No way to get there, skip

            if (grid[row][col] == '^') { // Beam splits, add the ways to get there to the sides
                ways[row + 1][col - 1] += w;
                ways[row + 1][col + 1] += w;
            } else {
                ways[row + 1][col] += w; // Just continue downwards
            }
        }
    }

    // Count the ways to reach each position at the end.
    long long result = 0;
    for (int col = 0; col < gridWidth; ++col) {
        result += ways[gridHeight - 1][col];
    }
    return result;
}



int main(){
    std::fstream file("../input.txt");

    if(!file.is_open()){
        std::cerr << "Could not open file. \n";
        return 1;
    }

    std::string line;
    std::vector<std::string> inputLines;
    while(std::getline(file, line)){
        inputLines.push_back(line);
    }
    file.close();

    // Find the beam entrance location
    int beamStart = 0;
    for(int i = 0; i<inputLines[0].size(); ++i){
        char c = inputLines[0][i];
        if(c == 'S'){
            beamStart = i;
            break;
        }
    }

    long long timeLines = 0;
    timeLines = countTimelines(inputLines);
    

    long long result = 0;
    result = calcBeamSplit(beamStart, inputLines, result);
    std::cout<< "RESULT: " << result << std::endl;
    std::cout<< "TIMELINES: " << timeLines << std::endl;
    return 0;
}