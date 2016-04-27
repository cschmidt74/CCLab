#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <map>
#include <vector>

using namespace std;
//struct oder enum für tokens
enum Token {
	tok_eof = -1,
	// commands
			tok_def = -2, tok_extern = -3,
	// primary
			tok_identifier = -4, tok_number = -5,
};

class lexer
{
public:
	string read_file(string file_path){
		ifstream file(file_path.c_str());
		string input((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
		return input;
	}

	lexer(std::string filePath){
		input_position = -1;
		file_input = read_file(filePath);
	}


	char get_next_character(){
		input_position++;
		return file_input[input_position];
	}

	int getToken() {
		static int LastChar = ' ';

		// Skip any whitespace.
		while (isspace(LastChar))
			LastChar = get_next_character(); //soll nächsten character from string holen

		if (isalpha(LastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
			IdentifierStr = LastChar;
			while (isalnum((LastChar = get_next_character())))
				IdentifierStr += LastChar;
			if (IdentifierStr == "def") return tok_def;
			if (IdentifierStr == "extern") return tok_extern;

			return tok_identifier;
		}

		if (isdigit(LastChar) || LastChar == '.') { // Number: [0-9.]+
			std::string NumStr;
			do {
				NumStr += LastChar;
				LastChar = get_next_character();
			} while (isdigit(LastChar) || LastChar == '.');
			NumVal = strtod(NumStr.c_str(), 0);
			return tok_number;
		}

		if (LastChar == '#') {
			// Comment until end of line.
			do
				LastChar = get_next_character();
			while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
			if (LastChar != EOF)
				return getToken();
		}

		// Check for end of file. Don't eat the EOF.
		if (LastChar == EOF) return tok_eof;

		// Otherwise, just return the character as its ascii value.
		int ThisChar = LastChar;
		LastChar = get_next_character();

		return ThisChar;
	}
private:
	int input_position;
	string file_input;
	std::string IdentifierStr; // Filled in if tok_identifier
	float NumVal; // Filled in if tok_number

	//public int für number-token-value
	//public string für identifier-token-value
};