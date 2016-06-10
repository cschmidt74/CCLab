#Grammar
```
ProgramStart -> PackageClause FunctionDecl
_
PackageClause -> "package" identifier ";"
identifier -> letter(letter|number|"_")*
_
FunctionDecl -> "func" identifier Function
Function -> "(" ParameterList ")" FunctionBody
ParameterList -> ParameterList "," Parameter | Parameter | €
Parameter -> string_literal | Expression
string_literal -> """ letter(letter|number|"_")* """
_
FunctionBody -> "{" StatementList "}"
StatementList -> StatementList Statement ";" | €
_
Statement -> Decleration | FunctionBody | Expression | Assignment | Call
_
Decleration -> "var" identifier "int" "=" Expression 
			 | "var" identifier "string" "=" string_literal
			 | "var" identifier "string" "=" identifier
_
Expression -> Term | Expression "+" Term | Expression "-" Term
Term -> Number | Term "*" Number | Term "/" Number
Number -> integer | identifier
integer -> (0-9)(0-9)*
_
Assignment -> identifier "=" Expression 
_
Call -> identifier "(" ParameterList ")"
```