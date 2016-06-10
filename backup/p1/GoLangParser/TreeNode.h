#include <string>
#include <iostream>

namespace ast{

	enum nodeType{
		//non-terminals
		nt_startingPoint = 0, nt_packageClause, nt_packageName, 
		nt_importdecl, nt_ImportPackageName, 
		nt_functionDecl, nt_functionName, nt_function, nt_functionBody, nt_block, nt_statementList,
		nt_statement, nt_functionCall, nt_functionCallCont, nt_arguments, nt_argumentsCont, nt_argument,

		//terminals
		nt_identifier = 100,
		
		//literals
		nt_literal = 200, /* anything that is encased in "" */
		nt_signature, 
	    nt_keyword, /* import, package, ... */ 
	    nt_symbol /* ;, (, ), {, }, ... */
	};

	enum dataType{
		dt_string, dt_char, dt_int, dt_float
	};

	class TreeNode{
	public:
	    TreeNode(){}
	    virtual nodeType getNodeType() = 0;
	};

	class NonTerminalNode : public TreeNode{
	public:
		NonTerminalNode(TreeNode* _left, TreeNode* _middle, TreeNode* _right, nodeType _nType)
		: left(_left), middle(_middle), right(_right), nType(_nType){}

		virtual nodeType getNodeType(){ return nType; }

		TreeNode* getLeftChild(){ return left; }
		TreeNode* getMiddleChild(){ return middle; }
		TreeNode* getRightChild(){ return right; }
	private:
		TreeNode* left;
		TreeNode* middle;
		TreeNode* right;
		nodeType nType;
	};

	class TerminalNode : public TreeNode{
	public:
		TerminalNode(std::string _name, dataType _dType, nodeType _nType, size_t _symbolTable_index)
		: name(_name), dType(_dType), nType(_nType), symbolTable_index(_symbolTable_index){}

		virtual nodeType getNodeType(){ return nType; }

		std::string getName(){ return name; }
		dataType getDataType(){ return dType; }
	private:
		std::string name;
		dataType dType;	
		nodeType nType;	
		size_t symbolTable_index; //needed??????
	};

	class LiteralNode : public TreeNode{
	public:
		LiteralNode(std::string _value, dataType _dType, nodeType _nType)
		:value(_value), dType(_dType), nType(_nType){}

		virtual nodeType getNodeType(){ return nType; }

		std::string getValue(){ return value; }
		dataType getDataType(){ return dType; }
	private:
		std::string value;	
		dataType dType;
		nodeType nType;
	};

} //namespace