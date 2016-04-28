#include "parser.hpp"
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	
	Parser p;

	p.parse_file("/Users/christopherseanschmidt/BitTorrent\ Sync/H15/hda/s5-ss16/cc/p/git/CCLab/p1/testfile.txt");

	p.print_tree(p.getRoot(), 0);

	return 0;
}