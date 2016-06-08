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
<h3>example program</h3>
<code>
[int]F_add [int]num1 [int]num2
	[int]num1+num2 -> total
	TOSS total
ENDDEF
ENTRY
[string]"This@_Is@_A@_Test@_Program" -> greeting
F_PRINT greeting
F_NL
F_BEEP
$comment
F_PAUSE
[string]"Would@_You@_Tell@_Me@_Your@_Name?" -> question
F_PRINT question
F_NL
[string]F_GET_string -> name
[string]"That's@_A@_Nice@_Name,@_Mine@_Is@_" -> tellname
[string]F_RAND_char -> cname1
[string]F_RAND_char -> cname2
F_PRINT tellname
F_PRINT cname1
F_PRINT cname2
F_NL
F_PAUSE
[string]"What@_Is@_Your@_Favorite@_Number?" -> numquestion
F_PRINT numquestion
F_NL
[float]F_GET_float -> favenum
[int]F_RAND -> cfavenum
IF cfavenum>favenum
	[string]{"Your@_Favorite,@_" ",@_Is@_Smaller@_Than@_My@_Favorite,@_"} -> favecompare
	F_PRINT favecompare{0}
F_PRINT favenum
F_PRINT favecompare{1}
F_PRINT cfavenum
F_NL
	F_PAUSE
ENDIF
ELSEIF cfavenum<favenum
	[string]{"Your@_Favorite,@_" ",@_Is@_Larger@_Than@_My@_Favorite,@_"} -> favecompare
	F_PRINT favecompare{0}
F_PRINT favenum
F_PRINT favecompare{1}
F_PRINT cfavenum
F_NL
	F_PAUSE
ENDELSEIF
ELSE
	[string]”Hey,@_Mine@_Too!” ->favecompare
	F_PRINT favecompare
	F_NL
	F_PAUSE
ENDELSE
[float]favenum+2 -> plus
[float]favenum-2 -> minus
[float]favenum*2 -> mult
[float]favenum/2 -> div
F_PRINT plus
F_PRINT minus
F_PRINT mult
F_PRINT div
F_NL
F_PAUSE
[int]F_add plus minus -> cool
F_PRINT cool
F_NL
F_PAUSE
</code>
<h3>example program 2</h3>
<code>
ENTRY
[int]F_RAND -> number
[int]0 -> guesses
[string]"I'm@_thinking@_of@_a@_number@_between@_0@_and@_255" -> prompt
[int]256 -> guess
[string]"" -> response
WHILE guess!=number 
F_PRINT prompt
F_NL
F_GET_float -> guess
guesses+1 -> guesses
IF guess<0|guess>255
	"that@_is@_out@_of@_range!" -> response
ENDIF
ELSEIF number>guess
	"that@_is@_too@_low" -> response
ENDELSEIF
ELSEIF number<guess
	"that@_is@_too@_high" -> response
ENDELSEIF
ELSE
	"that@_is@_correct!!!" -> response
ENDELSE
F_PRINT response
F_NL
F_PAUSE
ENDWHILE
[bool]false -> passed
$like it should
IF guess=number
	"@Aguesses:@_" -> prompt
	F_PRINT prompt
	F_PRINT guesses
	F_NL
	true -> passed
ENDIF
IF !passed
	"wat?" -> prompt
	F_PRINT prompt
	F_NL
ENDIF
WAIT 5
[string]"Thank@_You!" -> endSay
F_PRINT endSay
F_NL
</code>
