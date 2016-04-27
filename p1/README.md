The Compiler will only handle code belonging to the main() function.  
This means, that the input will be any Go-Code that would usually be put in the main-method.  
Everything else (if needed) will be added around that code to effectivly build a working Go-programm.  
  
  
syntax for Grammar:  
Items beginning with an uppercase Letter are non-terminals, otherwise they are terminals.  



# TAKING CARE OF MAIN

## baseline
```
package main  
func main(){}  
```

## Tokens
- startclause := "package main \n func main()"  
- {
- }
- epsilon

## Grammar
Root -> startclause { Main }  
Main -> OtherInput  

## Implementation
The first transition will be added automatically by the compiler.  
Example: Input = Something  
after Lexing and Parsing the compiler will add "package main /n func main(){" at the beginning of 'Something' and end it with "}"  
_______________________________________________________________________________________


# ADDING BASIC ARITHMETIC

## baseline
MAIN, Addition, Multiplikation, Parenthesis

example input: " 5.4*(4.3+3.4) "
 
note: - Technically this is not correct 'Go', but at this stage it should suffice
      - All Numbers are floats

## Tokens
Symbol := Token  
- l := (
- r := )
- m := *
- p := +
- n := number
- e := epsilon


## Grammar
Main      -> Term Sum
Sum       -> + Term Sum | epsilon
Term      -> Factor Product
Product   -> * Factor Product | epsilon 
Factor    -> ( Main ) | number

## Regular expression
n((p|m)n)*((p|n)ln((p|m)n)*r)*
