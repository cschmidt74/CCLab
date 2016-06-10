# Minimal Grammar
NT.count=12
T.count=2
```
StartingPoint -> PackageClause ImportDecl FunctionDecl
PackageClause -> "package" identifier ";"
identifier -> letter{letter|digit|"_"}*
_
ImportDecl -> "import" string_literal ";"
string_literal -> ""{char}*""
_
FunctionDecl -> "func" identifier Function
Function -> Arguments FunctionBody
FunctionBody -> "{" StatementList "}" 
StatementList -> StatementList Statement ";" | €

_
Statement -> FunctionCall | €
FunctionCall -> identifier "." identifier Arguments
Arguments -> "(" ArgumentList ")"
ArgumentList -> ArgumentList Argument ";" | €
Argument -> string_literal
```