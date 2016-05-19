https://github.com/cschmidt74/CCLab/blob/master/p_flex_bison/grammar.md
# Grammar
[step-for-step-grammar] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md)

## Syntax
- CamelCase: Non-Terminals
- lowsercase: terminals / tokens
- epsilon: €
- "quotation mark": char / string

## terminals / tokens
- package
- ;
- Identifier (string): `(letter|"_")(letter|number|"_")*`
- import
- Literal (string): `"""(char)*"""`
- func
- (
- )
- {
- }
- €
- .
- ,

## grammar
```
StartingPoint -> PackageClause ImportDecl FunctionDecl
PackageClause -> package PackageName ";" 
PackageName -> Identifier                 /* consciously keeping redundance, for special checks later on */
Identifier -> string  
ImportDecl -> import ImportPackageName ";"  /* for now semicolons are ignored */
ImportPackageName -> Literal                /* consciously keeping redundance, for special checks later on */
Literal -> string
FunctionDecl -> func FunctionName Function
FunctionName -> Identifier
Function -> Signature FunctionBody
Signature -> "(" ")"                              /* for now */
FunctionBody -> Block
Block -> "{" StatementList "}"
StatementList -> Statement ";" StatementList | € 
Statement -> FunctionCall | €                               /* "func main(){;;;;;;}" is valid in go */
FunctionCall -> PackageName "." FunctionCallCont
FunctionCallCont -> FunctionName Arguments
Arguments -> "(" ArgumentsCont ")"
ArgumentsCont -> Argument | Argument "," ArgumentsCont | €
Argument -> Literal 
```
