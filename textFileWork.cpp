//
//  main.cpp
//  my_workspace
//
//  Created by Arthur on 09.02.24.
//

#include <iostream>
#include <fstream>
#include <sstream>

void writeIntoFile(const std::string&, const std::string&);
void readingFromFile(const std::string&);
void removeEachSecondLine(const std::string&);
void reverseWords(std::string&);
void reverseWordsInLines(const std::string&);

int main(int argc, const char * argv[]) {
    const std::string txtfile = "/Users/arthur/Desktop/textfile.txt";
    
    const std::string str = "Lorem ipsum dolor sit amet consectetur adipiscing elit\nsed do eiusmod tempor incididunt ut labore et dolore magna\naliqua Ut enim ad minim veniam quis nostrud exercitation\nullamco laboris nisi ut aliquip ex ea commodo consequat\nDuis aute irure dolor in reprehenderit in voluptate velit esse\ncillum dolore eu fugiat nulla pariatur Excepteur sint occaecat\ncupidatat non proident sunt in culpa qui officia deserunt mollit\nanim id est laborum Sed ut perspiciatis unde omnis iste\nnatus error sit voluptatem accusantium doloremque laudantium\ntotam rem aperiam eaque ipsa quae ab illo inventore veritatis\net quasi architecto beatae vitae dicta sunt explicabo Nemo\nenim ipsam voluptatem quia voluptas sit aspernatur aut odit\naut fugit sed quia consequuntur magni dolores eos qui\nratione voluptatem sequi nesciunt Neque porro quisquam est qui\ndolorem ipsum quia dolor sit amet consectetur adipisci velit\nsed quia non numquam eius modi tempora incidunt ut labore\net dolore magnam aliquam quaerat voluptatem";
  
    writeIntoFile(txtfile, str);
    readingFromFile(txtfile);
    removeEachSecondLine(txtfile);
    reverseWordsInLines(txtfile);
    
}

void writeIntoFile(const std::string& fileName, const std::string& str) {
    std::ofstream file(fileName);
    if(!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    for(const char& c : str) {
        file << c;
    }
    file.close();
}
void readingFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if(!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file, line)){
        std::cout << line << std::endl;
    }
    file.close();
}
void removeEachSecondLine(const std::string& fileName) {
    std::ifstream ifile(fileName);
    if(!ifile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(ifile, line)) {
        lines.push_back(line);
    }

    ifile.close();

    std::ofstream ofile(fileName);
    
    if(!ofile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    
    for (size_t i = 0; i < lines.size(); ++i) {
        if (i % 2 == 0) {
            ofile << lines[i] << std::endl;
        }
    }
    
    ofile.close();
}
void reverseWords(std::string& line) {
    std::istringstream iss(line);
    std::cout << iss.str() << std::endl;
    std::vector<std::string> words(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
    
    std::reverse(words.begin(), words.end());

    std::ostringstream oss;
    std::move(words.begin(), words.end(), std::ostream_iterator<std::string>(oss, " "));
    line = oss.str();
}
void reverseWordsInLines(const std::string& fileName) {
    std::ifstream ifile(fileName);
    if(!ifile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    std::vector<std::string> lines;
    std::string line;

    while (std::getline(ifile, line)) {
        reverseWords(line);
        lines.push_back(line);
    }

    ifile.close();
    
    std::ofstream ofile("/Users/arthur/Desktop/ttt.txt");
    if(!ofile.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }
    
    for(const std::string& line: lines) {
        ofile << line << std::endl;
    }
    
    ofile.close();
}

