#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <chrono>
std::vector<char> tokenize(const std::string& sentence) {
   return std::vector<char>(sentence.c_str(), sentence.c_str() + sentence.length() + 1);
}


int main() {
   std::chrono::time_point<std::chrono::system_clock> start, end;
   std::string line;

   // Find the comma in the vector
   //auto it = std::find(arr.begin(), arr.end(), ',');
   std::fstream output("main.cpp");
   while (getline(output, line)) {
      std::cout << line << std::endl;
   }
   output.close();

   return 0;
}