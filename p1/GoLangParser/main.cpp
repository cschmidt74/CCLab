/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Luqzn
 *
 * Created on 15. April 2016, 17:55
 */

#include <cstdlib>

#include "Parser.h"

#define test true

/*
 * Main function
 */
int main(int argc, char** argv) {
    
    std::string pathCases = "D:\\CompilerConstruction\\testcases\\";
    if(test) {
        struct testcase {
            std::string file;
            int result;
        };
            
        testcase tc;
        std::vector<testcase> testcases;
        
        tc.file="valid\\valid_1";
        tc.result = 0;
        testcases.push_back(tc);
        
        tc.file="invalid\\invalid_comment.txt";
        tc.result = 3;
        testcases.push_back(tc);
                
        tc.file="invalid\\invalid_literal.txt";
        tc.result = 9;
        testcases.push_back(tc);
        
        
        for(int i = 1; i<=testcases.size(); i++) {
            Parser p;
            p.start(pathCases+testcases[i].file);
            std::cout << "Result should be " << testcases[i].result << " and was " << "TODO: RETVAL" << std::endl;
        }
        
        
    } else if(argc == 2) {
        Parser p;
        p.start(argv[1]);
    }
    return 0;
}