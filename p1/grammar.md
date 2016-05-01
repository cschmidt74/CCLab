# Grammar
[official go-lang notation documentation] (https://golang.org/ref/spec#Notation)
- [Package Clause] (https://github.com/cschmidt74/CCLab/blob/master/p1/grammar.md#grammar-1)
## Syntax
- CamelCase: Non-Terminals
- lowsercase: terminals / tokens
- epsilon: epsilon
- "quotation mark": char / string

## PackageClause
### [from Golang](https://golang.org/ref/spec#PackageClause)
```  
PackageClause  = "package" PackageName .  
PackageName    = identifier .  
identifier = letter { letter | unicode_digit } .  
letter        = unicode_letter | "_" .  
unicode_digit  = /* a Unicode code point classified as "Number, decimal digit" */ .  
unicode_letter = /* a Unicode code point classified as "Letter" */ .  
```  

### converted
#### tokens
- package
- unicode_digit
- unicode_letter
  
#### grammar
```
PackageClause -> package PackageName  
PackageName -> Identifier  

Identifier -> Letter IdenCont 
IdenCont -> Letter IdenCont | unicode_digit IdentCont | epsilon  
Letter -> unicode_letter | "_"  
```  

## Import declarations
### [from Golang](https://golang.org/ref/spec#ImportDecl)
```
ImportDecl       = "import" ( ImportSpec | "(" { ImportSpec ";" } ")" ) .
ImportSpec       = [ "." | PackageName ] ImportPath .
ImportPath       = string_lit .
string_lit             = raw_string_lit | interpreted_string_lit .
raw_string_lit         = "`" { unicode_char | newline } "`" .
interpreted_string_lit = `"` { unicode_value | byte_value } `"` .
unicode_char   = /* an arbitrary Unicode code point except newline */ .
newline        = /* the Unicode code point U+000A */ .
unicode_value    = unicode_char | little_u_value | big_u_value | escaped_char .
byte_value       = octal_byte_value | hex_byte_value .
octal_byte_value = `\` octal_digit octal_digit octal_digit .
hex_byte_value   = `\` "x" hex_digit hex_digit .
little_u_value   = `\` "u" hex_digit hex_digit hex_digit hex_digit .
big_u_value      = `\` "U" hex_digit hex_digit hex_digit hex_digit
                           hex_digit hex_digit hex_digit hex_digit .
escaped_char     = `\` ( "a" | "b" | "f" | "n" | "r" | "t" | "v" | `\` | "'" | `"` ) .
/* PackageName: see #PackageClause  */
```

### converted (& simplified)
#### tokens
- import
  
#### grammar
```
ImportDecl -> import PackageName
/* PackageName: see #PackageClause */
```
## Function declarations
### [from Golang](https://golang.org/ref/spec#Function_declarations)
```
FunctionDecl = "func" FunctionName ( Function | Signature ) .
FunctionName = identifier .
Function     = Signature FunctionBody .
FunctionBody = Block .
Block = "{" StatementList "}" .
StatementList = { Statement ";" } .
```
### converted (& simplified)
#### tokens
- func

#### grammar
```
FunctionDecl -> func Identifier Function
Function -> Signature Block
Signature -> "()"                         /* for now */
Block -> "{" StatementList "}"
StatementList -> Statement ";" StatementList | epsilon  /* unsure about this one! */
```

## Statements
### [from Golang] (https://golang.org/ref/spec#Statement)
```
Statement =
	Declaration | LabeledStmt | SimpleStmt |
	GoStmt | ReturnStmt | BreakStmt | ContinueStmt | GotoStmt |
	FallthroughStmt | Block | IfStmt | SwitchStmt | SelectStmt | ForStmt |
	DeferStmt .

SimpleStmt = EmptyStmt | ExpressionStmt | SendStmt | IncDecStmt | Assignment | ShortVarDecl .
```

###converted (& simplified)
#### tokens

#### grammar
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
