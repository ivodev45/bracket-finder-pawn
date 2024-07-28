/*
              ____                 _        _     _____ _           _             _____ _               
             | __ ) _ __ __ _  ___| | _____| |_  |  ___(_)_ __   __| | ___ _ __  |  ___(_)_  _____ _ __ 
             |  _ \| '__/ _` |/ __| |/ / _ \ __| | |_  | | '_ \ / _` |/ _ \ '__| | |_  | \ \/ / _ \ '__|
             | |_) | | | (_| | (__|   <  __/ |_  |  _| | | | | | (_| |  __/ |    |  _| | |>  <  __/ |   
             |____/|_|  \__,_|\___|_|\_\___|\__| |_|   |_|_| |_|\__,_|\___|_|    |_|   |_/_/\_\___|_|   
                                                                                           
                        @Date : 28.7.2024
                        @Author : ivodev45
                        @Github : github.com/ivodev45

                        Info : Simple Bracket Finder Fix koji ispravlja zagrade u vasem gamemodu

                        Setup : Sve sto je potrebno jeste da bracket-finder-pawn.exe ubacite u gamemodes folder,
                            pa ga onda pokrenete kad ste ga ubacili i kucate npr test.pwn

                        @Credits : https://github.com/zile42O         
*/

#include <iostream>
#include <fstream>
#include <stack>
#include <string>

// Function to check and fix missing parentheses, braces, and brackets
void checkAndFixBrackets(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string content;
    std::string line;
    std::stack<std::pair<char, int>> brackets;
    int lineNumber = 0;

    // Read the file content and identify mismatched brackets
    while (std::getline(inputFile, line)) {
        lineNumber++;
        for (size_t i = 0; i < line.length(); ++i) {
            char ch = line[i];
            if (ch == '(' || ch == '{' || ch == '[') {
                brackets.push({ ch, content.size() });
            }
            else if (ch == ')' || ch == '}' || ch == ']') {
                if (!brackets.empty() &&
                    ((ch == ')' && brackets.top().first == '(') ||
                        (ch == '}' && brackets.top().first == '{') ||
                        (ch == ']' && brackets.top().first == '['))) {
                    brackets.pop();
                }
                else {
                    std::cout << "Unmatched closing bracket " << ch << " at line " << lineNumber << ", position " << i + 1 << std::endl;
                }
            }
            content += ch;
        }
        content += '\n';
    }

    inputFile.close();

    // Report unmatched opening brackets
    while (!brackets.empty()) {
        char openBracket = brackets.top().first;
        int position = brackets.top().second;
        brackets.pop();
        std::cout << "Unmatched opening bracket " << openBracket << " at position " << position << std::endl;

        // Append the corresponding closing bracket at the end of content
        if (openBracket == '(') {
            content += ')';
        }
        else if (openBracket == '{') {
            content += '}';
        }
        else if (openBracket == '[') {
            content += ']';
        }
    }

    // Write the fixed content back to the file
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
        return;
    }

    outputFile << content;
    outputFile.close();

    std::cout << "Brackets checked and file updated successfully." << std::endl;
}

int main() {
    std::string filename;
    std::cout << "Enter the filename of the .pwn script: ";
    std::cin >> filename;
    checkAndFixBrackets(filename);
    return 0;
}