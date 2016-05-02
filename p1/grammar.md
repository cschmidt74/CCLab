# Grammar
[official go-lang notation documentation] (https://golang.org/ref/spec#Notation)
- [Package Clause] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#grammar-1)  
- [Import declarations] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#grammar-2)
- [Function declarations] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#grammar-3)
- [Statements] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#grammar-4)

## Syntax
- CamelCase: Non-Terminals
- lowsercase: terminals / tokens
- epsilon: epsilon
- "quotation mark": char / string

## PackageClause
[Golang](https://golang.org/ref/spec#PackageClause)
  
### tokens
- package
- string
  
### grammar
```
PackageClause -> package PackageName  
PackageName -> Identifier   /* consciously kept redundance, in case PackageName has special errorchecking or the like*/
Identifier -> string  
```  

## Import declarations
[Golang](https://golang.org/ref/spec#ImportDecl)
  
### tokens
- import
  
### grammar
```
ImportDecl -> import PackageName
/* PackageName: see #PackageClause */
```
## Function declarations
[Golang](https://golang.org/ref/spec#Function_declarations)
  
### tokens
- func

### grammar
```
FunctionDecl -> func FunctionName Function
FunctionName -> Identifier
Function -> Signature FunctionBody
Signature -> "()"                         /* for now */
FunctionBody -> Block
Block -> "{" StatementList "}"
StatementList -> Statement ";" StatementList | epsilon 
```

## Statements
[Golang] (https://golang.org/ref/spec#Statement)
  
### tokens

### grammar
```
Statement -> Declaration | SimpleStmt | ReturnStmt    /* see link above for more options */
SimpleStmt -> EmptyStmt | ExpressionStmt | Assignment 
EmptyStmt -> epsilon                                  /* this means that "func main(){;;;;;}" is legal in GO */
Declaration -> EmptyStmt            ______
SimpleStmt -> EmptyStmt                   |
ReturnStmt -> EmptyStmt                   |
EmptyStmt -> EmptyStmt                     > waiting for implementation
ExpressionStmt -> EmptyStmt               |
Assignment ->EmptyStmt              ______|
```
