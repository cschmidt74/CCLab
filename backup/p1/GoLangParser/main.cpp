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

bool does_file_exist(const std::string& name);

/*
 * Main function
 */
int main(int argc, char** argv) {
    
    std::string pathCases = "/vagrant/testcases/";

    if(test) {

        size_t false_reports = 0;

        std::cout << "Testing Valid Testcases..." << std::endl;
        int caseCount = 1;
        std::string path_ =  pathCases + "valid/valid_" + std::to_string(caseCount) + ".txt";
        while(does_file_exist(path_)){

            Parser p;
            std::cout << "Testing: " << path_ << std::endl;
            bool hadErrors = p.start(path_);
            if(hadErrors){
                std::cout << "N: Lexer/Parser mistakenly found errors!" << std::endl;
                ++false_reports;
            } else {
                std::cout << "Y: Lexer/Parser correctly found no errors!" << std::endl;
            }

            std::cout << std::endl;
            ++caseCount;
            path_ =  pathCases + "valid/valid_" + std::to_string(caseCount) + ".txt";
        }

        std::cout << std::endl << std::endl;

        std::cout << "Testing Invalid Testcases..." << std::endl;
        caseCount = 1;
        path_ =  pathCases + "invalid/invalid_" + std::to_string(caseCount) + ".txt";
        while(does_file_exist(path_)){

            Parser p;
            std::cout << "Testing: " << path_ << std::endl;
            bool hadErrors = p.start(path_);
            if(hadErrors){
                std::cout << "Y: Lexer/Parser correctly found errors!" << std::endl;
            } else {
                std::cout << "N: Lexer/Parser mistakenly found no errors!" << std::endl;
                ++false_reports;
            }

            std::cout << std::endl;
            ++caseCount;
            path_ =  pathCases + "invalid/invalid_" + std::to_string(caseCount) + ".txt";
        }        

        std::cout << std::endl << std::endl;

        if(false_reports)
            std::cout << "Parser/Lexer failed " << false_reports << " tests" << std::endl;
        else
            std::cout << "Parser/Lexer passed all tests" << std::endl;
        
        
        
    } else if(argc == 2) {
        Parser p;
        p.start(argv[1]);
    }
    return 0;
}

bool does_file_exist(const std::string& name){
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }  
}