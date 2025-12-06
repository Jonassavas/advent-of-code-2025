#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>


std::vector<std::tuple<long long, long long>> mergeRanges(
                        std::vector<std::tuple<long long, long long>> rangesVec) {
                            
    if (rangesVec.empty()) return {};

    // Sort ranges by first element
    std::sort(rangesVec.begin(), rangesVec.end(),
              [](const std::tuple<long long,long long>& a, const std::tuple<long long,long long>& b){
                  return std::get<0>(a) < std::get<0>(b);
              });

    std::vector<std::tuple<long long,long long>> merged;
    long long currentStart = std::get<0>(rangesVec[0]);
    long long currentEnd = std::get<1>(rangesVec[0]);

    for (size_t i = 1; i < rangesVec.size(); ++i) {
        long long start = std::get<0>(rangesVec[i]);
        long long end = std::get<1>(rangesVec[i]);

        if (start <= currentEnd + 1) { // overlap or adjacent
            currentEnd = std::max(currentEnd, end);
        } else {
            merged.push_back({currentStart, currentEnd});
            currentStart = start;
            currentEnd = end;
        }
    }

    merged.push_back({currentStart, currentEnd});
    return merged;
}

// Function to calculate the total number of IDs
long long nrValidIds(const std::vector<std::tuple<long long, long long>>& rangesVec) {
    auto mergedRanges = mergeRanges(rangesVec);

    long long sumOfIds = 0;
    for (const auto& range : mergedRanges) {
        long long first = std::get<0>(range);
        long long second = std::get<1>(range);
        sumOfIds += (second - first + 1);
    }


    return sumOfIds;
}

int main() {
    std::ifstream file("../input.txt");
    if(!file.is_open()){
        std::cerr << "Could not open file.\n";
        return 1;
    }

    std::vector<std::tuple<long long,long long>> rangesVec;
    std::string line;
    bool readRanges = true;

    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty()) {
            readRanges = false;
            continue;
        }

        if (readRanges) {
            size_t dashPos = line.find('-');
            if (dashPos == std::string::npos) {
                std::cerr << "Bad range format: " << line << "\n";
                return 1;
            }

            long long firstNum = std::stoll(line.substr(0, dashPos));
            long long secondNum = std::stoll(line.substr(dashPos+1));

            rangesVec.push_back({firstNum, secondNum});
        } else {
            break; // you can process IDs if needed in second part
        }
    }

    file.close();

    long long sumValidIds = nrValidIds(rangesVec);
    std::cout << "Nr valid IDs: " << sumValidIds << std::endl;

    return 0;
}
