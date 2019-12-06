
# Ghost Programming Language

## Preface
This project takes me about two whole weeks to design and implement, including reconstruct for two times. Merely a piece of markdown documentation is far from enough to articulate either my design or implementation, so I deeply hope instructors could get into my source code and give me some suggestions on how to improve. Suggestions from marcro structural designs to micro code re-using and naming is welcome. (Bug reporting is also welcome : )

## Introduction
**Ghost** is an interpreted, dynamically-typed programming language designed and developed by Hao Jiang.

There're two modes supported for Ghost language, command mode and file mode.

For command mode, just launch ```./Ghost``` at the terminal.
For file mode, run ```./Ghost testfile.ghost```  and hit enter.
Attention, ghost file must end with ```.ghost``` suffix.
 
 PS: Since I haven't totally handle the uncomment in file mode(which I expected to contain both line comment and block comment), it's better to test and use in command line mode.

## Basic data type

Ghost language has its own built-in data types, variables may be categorized into one of them.
- Ghost_intObj: holds integer variables, with built-in long long type supported.
	 - Specifically, prefix and postfix increment and decrement is contained in Ghost_intObj. 
	 ```
	var intObj = 1;
	--intObj // 0
	intObj-- // -1
	++intObj // 0
	intObj++ // 1
	```
- Ghost_floatObj: holds float variables, with built-in double type supported.
	- For Ghost_intObj and Ghost_floatObj, basic numerical operation as addition, subtraction, multiplication and division are all supported, with other in prospect.
- Ghost_stringObj: holds string variables, with built-in std::string type supported.
- Ghost_listObj: a container data type, which can hold Ghost_intObj, Ghost_floatObj and Ghost_stringObj within.
- Functor: all functions are represented in the form of Expression Tree, which is a full binary tree. Every part of this expression tree is a subtree with operator as parent node and operands as child nodes.

## Built-in function

Ghost supports several built-in functions.

- toupper(): takes a Ghost_stringObj, return its uppercase
- tolower(): takes a Ghost_stringObj, return its lowercase
- len(): takes a Ghost_stringObj and Ghost_listObj, return its length
- val(): take a variable as argument, display its value
- type(): take a variable as argument, display its type
- query(): take a variable as argument, display its naming, type and value
- show_local(): take no arguments, show all variables in the current scope, in the form of variable naming, type and value
- show_var(): take no arguments, show all variables in the global scope, in the form of variable naming, type and value
- print(): take one or multiple constant values or variables, print their value one by one. Users are allowed to add self-defined ending with the default argument "end="

## Variable declaration and assignment
Ghost use "var" as the keyword to declare variable member, so that users don't need to handle inner variable type, such as integer, float ,etc.

```
var intVar = 10 // integer variable
var floatVar = 49.7 // float variable
var stringVar = "Hao Jiang" // string variable
var listVar = [1, 1.5, "ECE751"] // list variable
```
Assignment may implicitly alter the original data type, and users don't have to care about that.
```
intVar = [1, 2, 3] // intVar is internally changed to Ghost_listObj
```
Built-in function type(), val() and query() are supported to check the status of existant variables at any time.

## Function declaration and execution
- Ghost use ```var``` as the keyword to declare a function.
```
def f1(a,b) = a * b - 2 / y
```
 It also supports one function defined upon another.

```
def f2(x,y)= x * y - x;
def f(a,b,c,d)= f1(a, b) - f2(c, d)

// execution
f(1, 2, 3, 4) // may return -6
```
 
## Error handle and error message
Error message has been implanted to give fundamental but important hint on user input or file content, which I expect may easily to erase mis-typing.
```
var obj=10
objj = 10 // will report "The variable is not declared or is not integer type"
var while = 10 // will report "Cannot use keywords as variable name"
```
Something like that.

Currently error handle can only guard superficially grammer mis-match, while malicious input which may cause program breakdown are able to cause great damage.


## Scope management

Everytime user hit a "{" or enter into a "if" or "while" statement block, a new scope is created, which has the concept of local variable and global variable.

Two features need to pay attention:
(1) A default scope is created once user successfully step into the program, so variables and function declared outmost may be globally visible.
(2) Curly brace for scope management must be the only token of a new line.

```
{
	var x = 10 // legal
}

var x=10; { // illegal
```

scope management example:
```
var globalVar = 10
{
	var localVar = 20
	show_local() => localVar
	show_var() => localVar & globalVar
}
show_var() => globalVar
```

## Control flow
- if statement
At present Ghost only supports single variable(any datatype except functor) and comparision between comparable variables.
```
// single variable as boolean value 
var val1 = 10
if(val1) { // may execute if statement
}

// comparison expression as boolean value
var val = 20
if(val < boolean) { 
// this won't be executed
// anything between two curly braces will be ignored
}
```
- while statement
	While loop syntax is similar to that of if statement.
	But something different with if statement is
	
	Entering into if block, lines of code will be executed line by line and get immediate result or error message warning.
	
	But for while block, all instructions between beginning and ending curly brace will be temporarily store in a vector, and execute after no new instructions in between.
	Also, to avoid dead while which never ends, a MAX_DEPTH_ITERATION threshold has been set. Once exceeded, while loop will be forced to exit, state flags also be reset.
```
// single variable as boolean value 
var val1 = 10
while(val1) { // may execute while statement
}

// comparison expression as boolean value
var val = 20
while(val < boolean) { 
// this won't be executed
// anything between two curly braces will be ignored
}
```



## Detailed grammer
- Once you input a single variable(including functor), its value will appear on the screen.

For functors, things are slightly different; it may appear as ```<Function object>```.

```
var val1=10
def f(a) = a

val1 => 10
f => <Function object>
[1, 2, 3] => [1, 2, 3]
```

- Semicolon is accecptable but not required
```
var var1 = 10; // acceptable
var var2 = 10 // also acceptable
```
- No tab or space requirement
	- Some programming language, say, Python, requires pre-indentation alignment, but Ghost don't. It's tokenized and parsed line by line.

- String concatenation(only double string) is supported in Ghost.
```
"Hao" "Jiang" => "Hao Jiang"
```
- Comparable
	- If and while statement block both depend on boolean comparison.
	- Objects of same data type can be compared(except functor).
	- Integer type and float type can be compared with each other. 
- About control flow grammer, "{" must follow right after the boolean statement, or as the first and only token at the first line after the boolean statement.
```
// Two valid control flow statement
if(val1==val2) { // "{" follow right after if evaluation statement

while(val1 == val2)
{ // "{" as the first and only token at the next line after if evaluation statement
```


## Source code illustration

### BasicDataManager
The fundamental and one of the most struct in my project. All other classes depends on type checking, type fetching, etc. All these work are based on varType, a enum class specifying data type.

It also includes ```findMatched()``` and ```getVarType()```, two commonly used functions.

### Ghost_intObj
Use long long as internal data type

### Ghost_floatObj
Use float as internal data type

### Ghost_stringObj
Use string as internal data type

### Ghost_listObj
Use vector as internal data type, which can hold Ghost_intObj, Ghost_floatObj and Ghost_stringObj as its member.

### ExprTree
The expression tree is a structural representation of a numerical function, with operator and the root of subtree and operands play as child node.

Return type is an important issue for my design : (
Pre-determining return type is carried out after building the tree, merely on input constant variables.

For variables, argTbl and argMap are responsible for variable value replacement, in other words, formal arguments are merely placeholders.

For function called by function, a new expression tree will be generated by the completely spanned expression.

### ExitHandler
This class handles exit-related issues, since the first thing for parser is to determine whether quit the program or not.

### ErrorHandler
Take charge of error report message.
```err_no``` is set default to ```INVALID_INPUT``` when initializing, and may spread out to main execution after parsing.

### Comparator
Single comparison statement and if/while statement decision expression all rely on comparator.

In Ghost language, comparable is defined as between same type, with an exception -- Ghost_intObj to Ghost_floatObj 

The reason why I apply overload on ```compare()``` is that
(1) comparison is the core function of a comparator, while output to std::cout is just accessory, so it's viable to part them
(2) if/while statement needs only the result of comparison, not the result of comparison execution

### Uncommenter
Remove the comment of input commands or read strings. Ar present, only line command and in-line block comment is supported.

### Tokenizer
Split every string into tokens, ready for parser to execute.

### Parser
After tokenizing input strings into tokens, parser categorize into different slots.

Catogorization is defined by fixed-length commands and uncertain ones.

For example, ```show_local() ``` is bound to be tokens of length of three, while ```var nnum = 3``` variable declaration is bound to be of four, etc.

Every time, tokens will be trid fixed-length one, if applicable and multiple tokens one, if return type and error message indicates the instruction hasn't been handled properly.

### Data manager
Core data structure of the whole project is the scopeManager and scope manager array, which stores variables and functions within every scope.

### Scope manager
A scope manager is created everytime a new scope is created. 

Scope manager provides interface for Data manager, meanwhile Data manager provides interface for parser to call.

## Future prospect


Confined to not-so-good OO design(like Ghost_object common class), program scale and limited time, there're still much to improve.
- Debug: I've tested after finishing every module, but not applying regression test... But I've comfirmed I've removed every bug I've found.
- Comment: currently only line comment ```//``` and ```/* */``` are supported. I expect line comment in Command mode and both line and block comment in File mode.
- OO design: use Ghost_object as a common data class for all basic data types, which will greatly reduce code size and be helpful to evaluate. BTW, I think it much more convenient in Java/C#.
- data type should add map/dict, which could store key-value pair.
- integer type should contain Ghost_bigIntObj class, which inherits from Ghost_intObj to handle big integer.
- Ghost_listObj is supposed to contain Ghost_listObj, which can only be implemented by pointer.
- Every member of Ghost_listObj is a struct, which contains union and type to indicate. Since union is a data structure more economical to memory.
- more natural and flexible declaration and assignment
```
var variable = f(val1, val2); // declare variable by function return value
variable = g(val1, val2); // assign variable by function return value
```
- string  slicing and list subscripting
```
// list subscripting
var listVar = [1, 3.4, "Hao Jiang"]
listVar[1] => 3.4 Ghost_floatObj
listVar[1:2] => [3.4, "Hao Jiang"] Ghost_listObj

// string slicing
var stringVar = "HaoJiang"
stringVar[3] => "J" Ghost_stringObj
stringVar[3:5] => "Jia" Ghost_stringObj
```
- validility check and error handle
 At present, validility error handle is quite weak; in other weak, Ghost can only provide basic and meager protection against wrong mistake.
- function representation should be implemented in a more general way, and it should support all possible pre-defined operations. For generalization, it should include ```return```, recursive function call, high-order function.
