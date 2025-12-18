#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <cstdlib>

long long add(long long a, long long b) { return a + b; }
long long sub(long long a, long long b) { return a - b; }
long long mul(long long a, long long b) { return a * b; }
long long divi(long long a, long long b) { return a / b; }

std::unordered_map<char, long long(*)(long long, long long)> op = {
    {'+', add},
    {'-', sub},
    {'*', mul},
    {'/', divi}
};

int main() {
    std::ifstream file("../input.txt");
    if (!file.is_open()) {
        std::cerr << "Could not open file\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) lines.push_back(line);
    file.close();

    int rows = lines.size() - 1;
    std::string &symBolLine = lines.back();
    int nrSymbols = symBolLine.size();

    // Gets the character in the in a specific lines string
    auto char_at = [&](int r, int c) {
        if (r < 0 || r >= (int)lines.size()) return ' ';
        if (c < 0 || c >= (int)lines[r].size()) return ' ';
        return lines[r][c];
    };

    long long grandTotal = 0;

    int currChar = 0;
    while (currChar < nrSymbols) {
        char sym = char_at(rows, currChar);

        if (sym!='+' && sym!='-' && sym!='*' && sym!='/') {
            currChar++;
            continue;
        }

        // We found a number
        int start = currChar;

        // Determine the width of the column
        // Move right until we hit a column where ALL *digit rows* are space
        int end = start;
        // Look at the column to the right
        while (end + 1 < nrSymbols) {
            bool blank = true;
            // Each row above the symbol line
            for (int currRow = 0; currRow < rows; ++currRow) {
                if (char_at(currRow, end + 1) != ' ') {
                    blank = false;
                    break;
                }
            }
            // If every row was blank, then we found the column length
            if (blank) break;
            end++;
        }

        // Now columns [start..end] belong to this problem.
        // Build numbers right→left
        std::vector<long long> nums;

        for (int col = end; col >= start; --col) {
            std::string num;
            for (int r = 0; r < rows; ++r) {
                char ch = char_at(r, col);
                if (std::isdigit((unsigned char)ch)) num.push_back(ch);
            }
            if (num.empty()) num = "0";
            nums.push_back(std::stoll(num));
        }

        // Evaluate
        auto f = op[sym];
        long long curr = nums[0];
        for (size_t i = 1; i < nums.size(); ++i) {
            long long rhs = nums[i];
            if (sym=='/' && rhs==0) continue;
            curr = f(curr, rhs);
        }

        // Debug
        std::cout << "Problem (op '" << sym << "'): ";
        for (size_t k = 0; k < nums.size(); ++k) {
            if (k) std::cout << " " << sym << " ";
            std::cout << nums[k];
        }
        std::cout << " = " << curr << "\n";

        grandTotal += curr;

        // continue after the block
        currChar = end + 1;
    }

    std::cout << "GRAND TOTAL: " << grandTotal << "\n";
    return 0;
}
