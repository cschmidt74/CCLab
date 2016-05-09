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
- epsilon: epsilon
- "quotation mark": char / string

## StartingPoint

## terminals / tokens

## grammar
```
StartingPoint -> PackageClause ImportDecl FunctionDecl
```

## PackageClause
[Golang](https://golang.org/ref/spec#PackageClause)
  
### terminals / tokens
- package
- Identifier (string): `(letter|"_")(letter|number|"_")*`
  
### grammar
```
PackageClause -> package PackageName ";" /* for now semicolons are ignored */
PackageName -> Identifier /* consciously keeping redundance, for special checks later on */
Identifier -> string  
```  

## Import declarations
[Golang](https://golang.org/ref/spec#ImportDecl)
  
### terminals / tokens
- import
- Literal (string): `"""(ascii-alphabet)*"""`
  
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

### grammar
```
FunctionDecl -> func FunctionName Function
FunctionName -> Identifier
Function -> Signature FunctionBody
Signature -> "(" ")"                         /* for now */
FunctionBody -> Block
Block -> "{" StatementList "}"
StatementList -> Statement ";" StatementList | epsilon 
```

## Statements
[Golang] (https://golang.org/ref/spec#Statement)
  
### terminals / tokens

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
