#include <string>
#include <vector>
#include "lexer.hpp"
#include "TreeNode.hpp"


//ntMAIN, ntTERM, ntSUM, ntFACTOR, ntPRODUCT, ntNUMBER

class Parser {
public:
	Parser(){
		hasParsed = false;
		hasErrors = false;
	}


	void print_tree(TreeNode* node, int tabs){

		for(int i = 0; i < tabs; i++)
			cout << "\t";
		cout << endl;

		nodeType nt = node->getNodeType();

		if(nt == ntMAIN){
				MainNode *child = dynamic_cast<MainNode *>(node);
				cout << "Main" << endl;
				print_tree(child->sum, tabs + 1);
				print_tree(child->term, tabs + 1);
		} else if(nt == ntTERM){
				TermNode *child2 = dynamic_cast<TermNode *>(node);
				cout << "Term" << endl;
				print_tree(child2->factor, tabs + 1);
				print_tree(child2->product, tabs + 1);
		} else if(nt == ntSUM){
				SumNode *child3 = dynamic_cast<SumNode *>(node);
				cout << "Sum" << endl;
				print_tree(child3->term, tabs + 1);
				print_tree(child3->sum, tabs + 1);
		} else if(nt == ntFACTOR){
				FactorNode *child4 = dynamic_cast<FactorNode *>(node);
				cout << "Factor" << endl;
				print_tree(child4->child, tabs + 1);
		} else if(nt == ntPRODUCT){
				ProductNode *child5 = dynamic_cast<ProductNode *>(node);
				cout << "Product" << endl;
				print_tree(child5->product, tabs + 1);
				print_tree(child5->factor, tabs + 1);
		} else if(nt == ntNUMBER){
			cout << "number" << endl;
		} else {
			//some kind of error
		}

	}


	void parse_file(std::string filePath){
		lex = new lexer(filePath);
		next_token = lex->getToken();
		errorList.clear();
		root = parseMain();
		hasParsed = true;
	}

	TreeNode* parseMain(){
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

	TreeNode* getRoot(){
		if (hasParsed){	
			return root;
		}
		else {
			//errormsg
			return nullptr;	
		}
	}

	bool hasParsed;

	TreeNode* root;

	bool hasErrors;
	std::vector<std::string> errorList;

	lexer* lex;
	int next_token;

};