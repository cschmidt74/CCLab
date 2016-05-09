# Grammar
[official go-lang notation documentation] (https://golang.org/ref/spec#Notation)
- [Starting Point] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#startingpoint)
- [Package Clause] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#packageclause)  
- [Import declarations] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#import-declarations)
- [Function declarations] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#function-declarations)
- [Statements] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#statements)

## Syntax
- CamelCase: Non-Terminals
- lowsercase: terminals / tokens
- epsilon: e
- "quotation mark": char / string

## StartingPoint

## grammar
```
StartingPoint -> PackageClause ImportDecl FunctionDecl
```

## PackageClause
[Golang](https://golang.org/ref/spec#PackageClause)
  
### terminals / tokens
- package
- ;
- Identifier (string): `(letter|"_")(letter|number|"_")*`
  
### grammar
```
PackageClause -> package PackageName ";" 
PackageName -> Identifier /* consciously keeping redundance, for special checks later on */
Identifier -> string  
```  

## Import declarations
[Golang](https://golang.org/ref/spec#ImportDecl)
  
### terminals / tokens
- import
- Literal (string): `"""(char)*"""`
  
### grammar
```
ImportDecl -> import ImportPackageName ";" /* for now semicolons are ignored */
ImportPackageName -> Literal /* consciously keeping redundance, for special checks later on */
Literal -> string
```
## Function declarations
[Golang](https://golang.org/ref/spec#Function_declarations)
  
### terminals / tokens
- func
- (
- )
- {
- }
- e

### grammar
```
FunctionDecl -> func FunctionName Function
FunctionName -> Identifier
Function -> Signature FunctionBody
Signature -> "(" ")"                         /* for now */
FunctionBody -> Block
Block -> "{" StatementList "}"
StatementList -> Statement ";" StatementList | e 
```

## Statements
[Golang] (https://golang.org/ref/spec#Statement)

### terminals / tokens
- .
- ,

### grammar
```
Statement -> FunctionCall | epsilon
FunctionCall -> PackageName "." FunctionCallCont
FunctionCallCont -> FunctionName Arguments
Arguments -> "(" ArgumentsCont ")"
ArgumentsCont -> Argument | Argument "," ArgumentsCont | epsilon
Argument -> Literal 
```
