#include <string>

enum nodeType{
    nt_startingPoint, nt_packageClause, nt_packageName, nt_identifier
};

class TreeNode{
public:
    TreeNode(){}
    virtual nodeType getNodeType() = 0;
};

/* StartinPoint */
class StartingPointNode : public TreeNode{
public:
	StartingPointNode(TreeNode* _packageclause, TreeNode* _importdecl, TreeNode* _functiondecl)
	: packageclause(_packageclause), importdecl(_importdecl), functiondecl(_functiondecl){}

	virtual nodeType getNodeType(){ return nt_startingPoint; }

	TreeNode* getPackageClause(){ return packageclause; }
	TreeNode* getImportdecl(){ return importdecl; }
	TreeNode* getFunctiondecl(){ return functiondecl; }
private:
	TreeNode* packageclause;
	TreeNode* importdecl;
	TreeNode* functiondecl;
};

/* PackageClause */
class PackageClauseNode : public TreeNode{
public:
	PackageClauseNode(TreeNode* _packageName)
	: packageName(_packageName), keyword("package") {}

	virtual nodeType getNodeType(){ return nt_packageClause; }

	TreeNode* getPackageName(){ return packageName; }
	std::string getKeyword(){return keyword; }

private:
	TreeNode* packageName;
	std::string keyword;
};

class PackageNameNode : public TreeNode{
public:
	PackageNameNode(TreeNode* _identifier)
	: identifier(_identifier){}

	virtual nodeType getNodeType(){ return nt_packageName; }

	TreeNode* getIdentifier(){ return identifier; }

private:
	TreeNode* identifier;
};

class IdentifierNode : public TreeNode{
public:
	IdentifierNode(std::string _identifier)
	: identifier(_identifier) {}

	virtual nodeType getNodeType(){ return nt_identifier; }

	std::string getIdentifier(){ return identifier; }

private:
	std::string identifier;
};

/* Import declarations */

/* Function declarations */

/* Statements */