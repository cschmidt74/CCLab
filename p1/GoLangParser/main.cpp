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
#include <iostream>
#include "Parser.h"

/*
 * Main function
 */
int main(int argc, char** argv) {
   
   	Parser p;
    p.start("/vagrant/sourcecode.txt");

    /*
    if(argc == 2) {
        Parser p;
        //p.start(argv[1]);
        p.start("/vagrant/sourcecode.txt");
    }
    */
    return 0;
}