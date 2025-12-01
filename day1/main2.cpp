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
    int passesZero = 0;
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

        //std::cout<< "Dial is rotated ";
        if(positive){
            int nrTimesPassingZero = (currValue + value) / maxValue;

            currValue = (currValue + value) % maxValue;

            if(currValue == 0){
                // if we ended up at 0, we remove 1 from nrTimesPassingZero
                passesZero += (nrTimesPassingZero > 0 ? nrTimesPassingZero - 1 : 0);
                password++;
            }else{
                passesZero += nrTimesPassingZero;
            }
        
            //currValue = currValue % maxValue;
            std::cout<< "R" << value << " to point at " << currValue << std::endl;
        }else{
            int nrTimesPassingZero = 0;
            if(currValue == 0){
                nrTimesPassingZero = value / maxValue;
            }else{
                if(value >= currValue){
                    // We hit 0 at least once, at currValue steps, then # (value-currvalue) / maxValue
                    nrTimesPassingZero = (value - currValue) / maxValue + 1;
                }else{
                    // Not enough to hit 0 if we don't go above currValue backwards
                    nrTimesPassingZero = 0;
                }
            }
            // Modulo for negative values
            currValue = ((currValue - value) % maxValue + maxValue) % maxValue;
            if(currValue == 0){
                passesZero += (nrTimesPassingZero > 0 ? nrTimesPassingZero - 1 : 0);
                password++;
            }else{
                passesZero += nrTimesPassingZero;
            }
        }
    }
    int finalPassword = password + passesZero;

    file.close();

    std::cout<<"\nDial rotated to 0: " << password << std::endl;
    std::cout <<"Dial passing 0 during rotation: " << passesZero << std::endl;
    std::cout << "FINAL PASSWORD: " << finalPassword << std::endl;

    return 0;
}