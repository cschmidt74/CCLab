# Grammar
[official go-lang notation documentation] (https://golang.org/ref/spec#Notation)

## PackageClause
### [from Golang](https://golang.org/ref/spec#PackageClause)
'''  
PackageClause  = "package" PackageName .  
PackageName    = identifier .  
identifier = letter { letter | unicode_digit } .  
letter        = unicode_letter | "_" .  
unicode_digit  = /* a Unicode code point classified as "Number, decimal digit" */ .  
unicode_letter = /* a Unicode code point classified as "Letter" */ .  
'''  

### converted
PackageClause -> 'package' PackageName  
PackageName -> Identifier  

Identifier -> Letter IdenCont 
IdenCont -> Letter IdenCont | Unicode_digit IdentCont | epsilon  
Letter -> Unicode_letter | "_"  
  
