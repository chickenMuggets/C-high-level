#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <regex>

//compiler
void compile(const std::string& source_code) {
    //
    std::regex print_regex(R"(^\s*print\((?:\"(.*)\"|(\d+))\)\s*$)");
    std::regex function_regex(R"(^\s*function\(\) \{(.*)\}\s*$)");
    std::smatch match;
    std::ofstream out("output.cpp");
    out << "#include <iostream>\n";
    out << "int main() {\n";

    if (std::regex_match(source_code, match, function_regex)) {
        std::string body = match[1].str();
        if (std::regex_match(body, match, print_regex)) {
            out << "    std::cout << \"" << match[1].str() << "\\n\";\n";
        }
    }

    out << "    return 0;\n";
    out << "}\n";
    out.close();

    if (system("g++ output.cpp -o output.exe") != 0) {
        std::cerr << "Compilation failed." << std::endl;
        return;
    }
    std::cout << "Compilation finished. Run ./output.exe to execute." << std::endl;
}

int main() {
    std::string code;
    std::cout << "Enter your code: ";
    std::getline(std::cin, code);
    compile(code);
    return 0;
}
