//
//  main.cpp
//  Parser Pexex Lab
//
//  Created by Kevin Tan on 5/2/17.
//  Copyright © 2017 Caked. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

bool isHexLetter(char c) {
    if (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f')
        return true;
    else
        return false;
}

int main(int argc, const char * argv[]) {
    
    ifstream inputStream;
    inputStream.open("/Users/kevintan/Desktop/dataToParse.txt");
    
    if (inputStream.fail()) {
        cout << "fail to load file" << endl;
        exit(1);
    }
    
    string stringToParse = "";
    
    string result = "";
    int column = 1;
    bool skipAhead = false;
    bool reachedFirstNum = false;
    
    while (getline(inputStream, stringToParse)) {
        
        if (stringToParse == "---Type <return> to continue, or q <return> to quit---")
            continue;
        
        for (int i = 0; i < stringToParse.size(); i++) {
            
            if (skipAhead) {
                
                if (stringToParse[i] != ':')
                    continue;
                else {
                    skipAhead = false;
                    column++;
                    continue;
                }
                
            }
            
            switch (column) {
                case 1: {
                    if (!reachedFirstNum && (isHexLetter(stringToParse[i]) || (stringToParse[i] != '0' &&isdigit(stringToParse[i])))) {
                        
                        reachedFirstNum = true;
                        result += stringToParse[i];
                        continue;
                        
                    }
                    else if (reachedFirstNum) {
                        
                        if (stringToParse[i] != ' ') {
                            
                            result += stringToParse[i];
                            continue;
                            
                        }
                        
                        else {
                            
                            skipAhead = true;
                            reachedFirstNum = false;
                            continue;
                            
                        }
                        
                    }
                    break;
                }
                    
                case 2:
                    result += stringToParse[i];
                    if (stringToParse[i] == '\t')
                        column++;
                    break;
                    
                case 3:
                    if (stringToParse[i] == ' ') {
                        while (stringToParse[i] == ' ') {
                            i++;
                        }
                        result += ' ';
                        result += stringToParse[i];
                        continue;
                    }
                    else
                        result += stringToParse[i];
                    break;
                    
            }
            
        }
        
        result += '\n';
        column = 1;
        
    }
    
    cout << result << endl;
    inputStream.close();
    
}
