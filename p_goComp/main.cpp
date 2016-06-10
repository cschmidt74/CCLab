#include <iostream>
#include "node.hpp"

using namespace std;

extern NProgramStart* root;
extern int yyparse();

int main(int argc, char const *argv[]){
	
	int x = yyparse();
	cout << root << endl;
	return x;
}