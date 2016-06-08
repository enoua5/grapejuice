# grapejuice
Grapejuice installer for linux<br>
Grapejuice is a language that I made, which compiles into c++<br>
My friend is currently working on a Windows version<br>
<h3>INSTALLATION:</h3>
	In terminal, as root user, cd to grapejuice_release file.
	from here, run "source installer"
<h3>USE OF COMPILER:</h3>
	"winepress"
		opens winepress compiler
	"winepress2 grapename juicename"
		compilers with parameters
<h3>DOCUMENTATION:</h3>
	misc.:
		every line must end with an enter press
		tabs are ignored
		$ as the first character in a line denotes a comment
	"head" and "body":
		every program must include the following line:
		ENTRY
		
		everything before it is the head. everything after is the body.
	Functions:
		defining a function:
			In head of file:
			[datatype (any c++ data type, or "string"]F_FunctionName [datatype]param1 [datatype]param2 ...
				code
				TOSS returnvalue
			ENDDEF
			
			for example:
			[float]F_add [float]num1 [float]num2
				[float]num1+num2 -> total
				TOSS total
			ENDDEF
		calling a function:
			In body:
			F_functionName param1 param2 ...
			(note that the parameters must be variables, not literals)
			for example:
			F_add one two
		built-in functions:
			F_RAND
				returns a random number from 0 to 256
			F_RAND_char
				returns a random letter
			F_PRINT message
				prints message to the console
			F_NL
				prints a line break
			F_BEEP
				produces hard drive beep
			F_GET_string
				prints "::", gets user input, and returns value as string.
			F_GET_float
				prints "::", gets user input, and returns value as float
			F_PAUSE
				waits for user to press enter
			F_INT_TO_CHAR int
				returns a character with assci value of int
			F_CHAR_TO_INT char
				returns ascii value of char
	logic:
		use one per line with no spaces
		multiply
			*
		divide
			/
		add
			+
		subtract
			-
		and
			&
		or
			|
		not
			!
		greater than
			>
		less than
			<
		equal to
			=
	flow:
		if/else if/else:
			IF booleanVarible
				code
			ENDIF
			ELSEIF booleanVarible
				code
			ENDELSEIF
			ELSE
				code
			ENDELSE
		while:
			WHILE booleanVariable
				code
			ENDWHILE
		timer:
			WAIT intVariableSeconds
	variables:
		declaring a varible:
			[datatype]valueOrExpression -> name
			
			examples:
			[int]5 -> five
			[int]3+3 -> six
		changing a varible:
			valueOrExpression -> name
			
			example:
			4 -> five
		declaring an array:
			[datatype]{index0 index1 index2 ...} -> name
			
			example:
			[int]{1 2 3 4 5} -> oneToFive
		calling an array:
			name{index}
			
			example:
			oneToFive{1}
		strings:
			the value for a string must be between quotes.
			the symbol @ is the esape character
			@_ is a space
			@A is @
				
			example:
			[string]"strings@_and@_@A's" -> derp


example programs can be found in /projects
each folder contains a .grape which is the uncompiled version, and a .juice which is the compiled version.

<h3>quick example</h3>
[int]F_foo [int]number<br/>
	number+1 -> out<br/>
	TOSS out<br/>
ENDDEF<br/>
$comment<br/>
ENTRY<br/>
[int]F_GET_float -> picked<br/>
[int]F_foo picked -> thing<br/>
F_PRINT thing<br/>
F_NL<br/>
F_PAUSE<br/>
