enum nodeType{
	ntMAIN, ntTERM, ntSUM, ntFACTOR, ntPRODUCT, ntNUMBER
};

class TreeNode{
public:
	virtual nodeType getNodeType() = 0;
};

class MainNode: TreeNode{
public:	
	virtual nodeType getNodeType(){
		return ntMAIN;
	};

	TreeNode* term;
	TreeNode* sum;
};

class TermNode: TreeNode{
public:	
	virtual nodeType getNodeType(){
		return ntTERM;
	};

	TreeNode* factor;
	TreeNode* product;
};

class SumNode: TreeNode{
public:	
	virtual nodeType getNodeType(){
		return ntSUM;
	};

	TreeNode* term;
	TreeNode* sum;
};

class FactorNode: TreeNode{
public:	
	virtual nodeType getNodeType(){
		return ntFACTOR;
	};

	TreeNode* child;
	bool isNumber;
};

class ProductNode: TreeNode{
public:	
	virtual nodeType getNodeType(){
		return ntPRODUCT;
	};

	TreeNode* factor;
	TreeNode* product;
};

class NumberNode: TreeNode{
public:	
	virtual nodeType getNodeType(){
		return ntNUMBER;
	};

	float value;
};