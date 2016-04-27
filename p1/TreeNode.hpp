enum nodeType{
	ntMAIN, ntTERM, ntSUM, ntFACTOR, ntPRODUCT, ntNUMBER
};

class TreeNode{
public:
	TreeNode(){}
	virtual nodeType getNodeType() = 0;
};

class MainNode: public TreeNode{
public:	
	MainNode(){}
	MainNode(TreeNode* _term, TreeNode* _sum)
	: term(_term), sum(_sum){

	}

	virtual nodeType getNodeType(){
		return ntMAIN;
	};

	TreeNode* term;
	TreeNode* sum;
};

class TermNode: public TreeNode{
public:	
	TermNode(){}
	TermNode(TreeNode* _factor, TreeNode* _product)
	: factor(_factor), product(_product){

	}

	virtual nodeType getNodeType(){
		return ntTERM;
	};

	TreeNode* factor;
	TreeNode* product;
};

class SumNode: public TreeNode{
public:	
	SumNode(){}
	SumNode(TreeNode* _term, TreeNode* _sum)
	: term(_term), sum(_sum){

	}

	virtual nodeType getNodeType(){
		return ntSUM;
	};

	TreeNode* term;
	TreeNode* sum;
};

class FactorNode: public TreeNode{
public:	
	FactorNode(){}
	FactorNode(TreeNode* _child)
	: child(_child){

	}

	virtual nodeType getNodeType(){
		return ntFACTOR;
	};

	TreeNode* child;

	bool isNum(){
		if(child->getNodeType() == ntNUMBER) 
			return 1;
		return 0;
	}
};

class ProductNode: public TreeNode{
public:	
	ProductNode(){}
	ProductNode(TreeNode* _factor, TreeNode* _product)
	: factor(_factor), product(_product){

	}

	virtual nodeType getNodeType(){
		return ntPRODUCT;
	};

	TreeNode* factor;
	TreeNode* product;
};

class NumberNode: public TreeNode{
public:	
	NumberNode(){}
	NumberNode(int _value)
	: value(_value){

	}

	virtual nodeType getNodeType(){
		return ntNUMBER;
	};

	float value;
};