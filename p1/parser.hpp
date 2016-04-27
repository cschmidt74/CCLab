#include <string>
#include <vector>
#include "lexer.hpp"
#include "TreeNode.hpp"

class Parser {
public:
	Parser(){
		hasParsed = false;
		hasErrors = false;
	}

	void init(std::string filePath){
		lex = new lexer(filePath);
		next_token = lex->getToken();
		errorList.clear();
		hasParsed = false;
	}

	TreeNode* parseMain(){
		hasParsed = true;

		return new MainNode(parseTerm(), parseSum()); // Main    -> Term Sum
	}

	TreeNode* parseSum(){
		switch(next_token){
			case '+': next_token = lex->getToken(); // consume +
			          return new SumNode( parseTerm(), parseSum()); // Sum     -> + Term Sum
			default : return nullptr; // Sum     -> epsilon
		}
	}

	TreeNode* parseTerm(){
		return new TermNode(parseFactor(), parseProduct()); // Term    -> Factor Product
	}

	TreeNode* parseProduct(){
		switch(next_token){
			case '*': next_token = lex->getToken(); //consume *
			          return new ProductNode(parseFactor(), parseProduct()); //Product -> * Factor Product
			default : return nullptr; // Product -> epsilon 
		}
	}

	TreeNode* parseFactor(){
		TreeNode* result;
		switch(next_token){
			case '(': next_token = lex->getToken(); //consume (
				      result = parseMain();
				      if(next_token == ')'){
				      	next_token = lex->getToken(); //consume )
					    return result; //Factor   -> ( Main )
				      }
				      hasErrors = true;
				      addErrorMsg("Expected Right Parenthesis");
				      return nullptr;
			case tok_number: result = new NumberNode(lex->getNumVal()); 
			                 next_token = lex->getToken();
			                 return result;
			default: hasErrors = true;
					 addErrorMsg("Expected Left Parenthesis or a Number");
					 return nullptr;
		}
	}

	void addErrorMsg(std::string msg){
		errorList.push_back(msg);
	}

	bool hasParsed;

	bool hasErrors;
	std::vector<std::string> errorList;

	lexer* lex;
	int next_token;

};