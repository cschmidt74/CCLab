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

/*
 * Main function
 */
int main(int argc, char** argv) {
    if(argc == 2) {
        Parser p;
        //p.start(argv[1]);
        p.start("C:/Users/CSean/syncthing/H15/hda/s5-ss16/cc/p/git/CCLab/p1/sourcecode.txt");
    }
    return 0;
}