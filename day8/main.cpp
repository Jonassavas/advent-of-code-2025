#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

struct Point{
    public:
        std::vector<int> m_pos;
};


/*
    Each row is the position in 3D space
    x, y, z
*/
int calcShortestDistance(std::vector<std::vector<Point>> connectedBoxes){
    std::vector<std::vector<Point>> initialBoxes = connectedBoxes;
    double savedDistance = INT_MAX;
    
    for(size_t i = 0; i < connectedBoxes.size(); ++i){
        for( size_t j = 0; j < points.size(); ++j){
            // If we are at the same point --> skip
            if(i == j){
                continue;
            }
            
            if(connectedBoxes[i].size() >= 2){
                continue;
            }

            double distance = std::sqrt(
                            (points[j].m_pos[0] - points[i].m_pos[0]) * (points[j].m_pos[0] - points[i].m_pos[0]) + 
                            (points[j].m_pos[1] - points[i].m_pos[1]) * (points[j].m_pos[1] - points[i].m_pos[1]) +
                            (points[j].m_pos[2] - points[i].m_pos[2]) * (points[j].m_pos[2] - points[i].m_pos[2])
                        );
            
            if(savedDistance > distance){
                savedDistance = distance;
            }
        }
    }
    
}

int main(){
    std::fstream file("../input.txt");

    if(!file.is_open()){
        std::cerr << "Could not open file. \n";
        return 1;
    }
    // [[P1, P5],[P2, P4]]
    std::vector<std::vector<Point>> connectedBoxes;
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
            std::vector<Point> points;
            points.push_back(Point{row});
            connectedBoxes.push_back(points);
        }else{
            std::cerr<< "Row did not contain the correct elements";
            return 1;
        }

    }

    file.close();



    return 0;
}