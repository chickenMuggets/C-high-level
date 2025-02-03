#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>  // For setprecision

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    std::string outputFile = "main.cpp";
    std::string inputFile = "input.chllang";
    std::cout << "Opening file" << "\n";
    std::ifstream file(inputFile);

    if (!file.is_open()) {
        std::cerr << "Error opening " << inputFile << ".\n";
        return 1;
    }
    else {
        std::cout << "Opened file" << "\n";
    }


    std::ostringstream buffer;
    buffer << "#include <iostream>\n\nint main() {\n";

    std::string line;
    size_t printPos;
    size_t intvarPos;
    size_t commentPos;
    size_t floatvarPos;
    int lineNumber = 0;
    std::cout << "Begginning compilation" << "\n";
    while (std::getline(file, line)) {
        lineNumber++;
        printPos = line.find("print(\"");
        intvarPos = line.find("int ");
        floatvarPos = line.find("float ");
        commentPos = line.find("//");

        if (printPos != std::string::npos) {
            size_t start = printPos + 7;  // Move past `print("`
            size_t end = line.find("\")", start);
            if (end != std::string::npos) {
                std::string extractedText = line.substr(start, end - start);
                buffer << "    std::cout << \"" << extractedText << "\\n\";\n";
            }
        }


        else if (commentPos != std::string::npos) {
            buffer << "    " << line << "\n";
        }


        else if (intvarPos != std::string::npos) {
            //Extract variable name from the line (after 'int')
            size_t varStart = intvarPos + 4;  // Skip past 'int '
            size_t varEnd = line.find(" ");
            std::cout << line.find(" ") << "\n";
            if (varEnd == std::string::npos) {
                varEnd = line.length();  // If no space, the variable name goes until the end of the line
            }
            std::string varibleContents = line.substr(varStart, varEnd - varStart);
            if (line.find("=") == std::string::npos) {

                buffer << "    int " << varibleContents << ";\n";
            }
            else {
                buffer << "    float " << varibleContents << ";\n";

            }
        }


        else if (floatvarPos != std::string::npos) {
            //Extract variable name from the line (after 'float')
            size_t varStart = floatvarPos + 6;  // Skip past 'float '
            size_t varEnd = line.find(" ");
            if (varEnd == std::string::npos) {
                varEnd = line.length();  // If no space, the variable name goes until the end of the line
            }
            std::string varibleContents = line.substr(varStart, varEnd - varStart);
            if (line.find("=") == std::string::npos) {

                buffer << "    float " << varibleContents << ";\n";
            }
            else {
                buffer << "    float " << varibleContents << ";\n";
            }
        }


        else {
            std::cerr << "Syntax error: No matching construct found on line " << lineNumber << ".\n";
            return 1;
        }
    }

    buffer << "    return 0;\n}\n";
    file.close();

    std::ofstream outFile(outputFile, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error creating " << outputFile << ".\n";
        return 1;
    }
    //difference
    outFile << buffer.str();
    outFile.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Generated " << outputFile << " in "
              << std::fixed << std::setprecision(2) << duration.count() << " seconds.\n";

    return 0;
}
