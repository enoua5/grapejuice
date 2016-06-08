#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>

#include <cmath>
#include <unistd.h>
#include <algorithm>

using namespace std;
int randomNumber()
{	
	return rand()%256;
}
string remove_char( string str, char ch )
{
    // remove all occurrences of char ch from str
    str.erase( std::remove( str.begin(), str.end(), ch ), str.end() ) ;
    return str ;
}
bool searchText(string textToSearch, string lookingFor)
{
	bool foundText=false;
	for(int searchIndex=0; searchIndex<(textToSearch.length()-lookingFor.length()); searchIndex++)
	{
		bool couldBe=true;
		for(int check=0; check<lookingFor.length(); check++)
		{
			if(lookingFor[check]!=textToSearch[check+searchIndex])
			{
				couldBe=false;
			}
		}
		if(couldBe)
		{
			foundText=true;
		}
	}
	return foundText;
}
int getIndex(string textToSearch, string lookingFor)
{
	int index=0;
	bool foundText=false;
	int check;
	int foundAt;
	for(int searchIndex=0; searchIndex<(textToSearch.length()-lookingFor.length()); searchIndex++)
	{
		bool couldBe=true;
		for(check=0; check<lookingFor.length(); check++)
		{
			if(lookingFor[check]!=textToSearch[check+searchIndex])
			{
				couldBe=false;
			}
			foundAt=check;
		}
		if(couldBe)
		{
			if(!foundText)
			{
				index=foundAt+searchIndex;
			}
			foundText=true;
		}
	}
	return index;
}
string createLine(string grapevine)
{
	string output;
	//we have a comment
	if(grapevine[0]=='$'){}
	//we have a definition
	else if(searchText(grapevine," -> "))
	{
		//determine whether initialization of modification
		if(grapevine[0]=='[')
		{
			//initialization
			int i=1;
			while(grapevine[i]!=']')
			{
				output=output+grapevine[i];
				i++;
			}
			i++;
			output=output+' ';
			//find var name
			int j=getIndex(grapevine," -> ")+1;
			while(j<grapevine.length())
			{
				if(grapevine[j]!='\00')
					output=output+grapevine[j];
				j++;
			}
			if(grapevine[i]=='{')
			{
				output=output+"[]";
			}
			output=output+'=';
			//find value
			while(grapevine[i]!=' '||grapevine[i+1]!='-'||grapevine[i+2]!='>'||grapevine[i+3]!=' ')
			{
				if(grapevine[i]=='F'&&grapevine[i+1]=='_')
				{
					i+=2;
					while(grapevine[i]!=' '&&i<grapevine.length())
					{
						output=output+grapevine[i];
						i++;
					}
					output=output+"(";
					while(grapevine[i]!=' '||grapevine[i+1]!='-'||grapevine[i+2]!='>'||grapevine[i+3]!=' ')
					{
						i++;
						if(grapevine[i]==' '&&(grapevine[i]!=' '||grapevine[i+1]!='-'||grapevine[i+2]!='>'||grapevine[i+3]!=' '))
						{
							output=output+",";
						}
						else
						{
							output=output+grapevine[i];
						}
					}
					output=output+");\n0";
				}
				else
				{
				bool ignorethis=false;
				if(grapevine[i]=='@')
				{
					i++;
					if(grapevine[i]=='A')
					{
						output=output+"@";
					}
					else if(grapevine[i]=='_')
					{
						output=output+" ";
					}
					else
					{
						cout<<"Unrecognized escape character: "<<grapevine[i]<<endl;
					}
					i++;
				}
				//array stuffs
				else if(grapevine[i]==' ')
				{
					output=output+",";
				}
				//bool stuffs
				if(grapevine[i]=='|')
				{
					output=output+"|";
				}
				if(grapevine[i]=='&')
				{
					output=output+"&";
				}
				if(grapevine[i]=='='&&grapevine[i-1]!='!')
				{
					output=output+"=";
				}
				if(grapevine[i]=='\24')
				{
					i=grapevine.length();
				}
				if(grapevine[i]!='\00'&&grapevine[i]!='\24'&&!ignorethis)
					output=output+grapevine[i];
				i++;
				}
			}
			output=output+";\n";
		}
		else
		{
			//modification
			//find var name
			int i=0;
			int j=getIndex(grapevine," -> ")+1;
			while(j<grapevine.length())
			{
				if(grapevine[j]!='\00')
					output=output+grapevine[j];
				j++;
			}
			output=output+'=';
			//find value
			while(grapevine[i]!=' '||grapevine[i+1]!='-'||grapevine[i+2]!='>'||grapevine[i+3]!=' ')
			{
				if(grapevine[i]=='F'&&grapevine[i+1]=='_')
				{
					i+=2;
					while(grapevine[i]!=' '&&i<grapevine.length())
					{
						output=output+grapevine[i];
						i++;
					}
					output=output+"(";
					while(grapevine[i]!=' '||grapevine[i+1]!='-'||grapevine[i+2]!='>'||grapevine[i+3]!=' ')
					{
						i++;
						if(grapevine[i]==' '&&(grapevine[i]!=' '||grapevine[i+1]!='-'||grapevine[i+2]!='>'||grapevine[i+3]!=' '))
						{
							output=output+",";
						}
						else
						{
							output=output+grapevine[i];
						}
					}
					output=output+");\n0";
				}
				else
				{
				bool ignorethis=false;
				if(grapevine[i]=='@')
				{
					i++;
					if(grapevine[i]=='A')
					{
						output=output+"@";
					}
					else if(grapevine[i]=='_')
					{
						output=output+" ";
					}
					else
					{
						cout<<"Unrecognized escape character: "<<grapevine[i]<<endl;
					}
					i++;
				}
				//array stuffs
				else if(grapevine[i]==' ')
				{
					output=output+",";
				}
				//bool stuffs
				if(grapevine[i]=='|')
				{
					output=output+"|";
				}
				if(grapevine[i]=='&')
				{
					output=output+"&";
				}
				if(grapevine[i]=='='&&grapevine[i-1]!='!')
				{
					output=output+"=";
				}
				if(grapevine[i]=='\24')
				{
					i=grapevine.length();
				}
				if(grapevine[i]!='\00'&&grapevine[i]!='\24'&&!ignorethis)
					output=output+grapevine[i];
				i++;
				}
			}
			output=output+";\n";
		}
	}
	//we have a function
	else if(grapevine[0]=='F'&&grapevine[1]=='_')
	{
		int nameEndIndex;
		for(int i=2; i<grapevine.length(); i++)
		{
			if(grapevine[i]==' ')
			{
				//found end of function name
				nameEndIndex=i;
				i=grapevine.length();
			}
			else if(grapevine[i]=='\00'){}
			else
			{
				output=output+grapevine[i];
			}
		}
		output=output+"(";
		for(int i=nameEndIndex+1; i<grapevine.length(); i++)
		{
			if(grapevine[i]==' ')
			{
				output=output+",";
			}
			//escape
			else if(grapevine[i]=='@')
			{
				i++;
				if(grapevine[i]=='A')
				{
					output=output+"@";
				}
				else if(grapevine[i]=='_')
				{
					output=output+" ";
				}
				else
				{
					cout<<"Unrecognized escape character: "<<grapevine[i]<<endl;
				}
				i++;
			}
			//array stuffs
			else if(grapevine[i]=='{')
			{
				output=output+"[";
			}
			else if(grapevine[i]=='}')
			{
				output=output+"]";
			}
			else if(grapevine[i]==' ')
			{
				output=output+",";
			}
			else if(grapevine[i]!='\00'&&grapevine[i]!='\24')
			{
				output=output+grapevine[i];
			}
		}
		output=output+");\n";
	}
	//group ending
	else if(grapevine=="ENDIF"||grapevine=="ENDELSEIF"||grapevine=="ENDELSE"||grapevine=="ENDWHILE")
	{
		output=output+"}\n";
	}
	//if statement
	else if(grapevine[0]=='I'&&grapevine[1]=='F'&&grapevine[2]==' ')
	{
		output=output+"if(";
		for(int i=3;i<grapevine.length(); i++)
		{
			if(grapevine[i]=='|')
			{
				output=output+"|";
			}
			if(grapevine[i]=='&')
			{
				output=output+"&";
			}
			if(grapevine[i]=='='&&grapevine[i-1]!='!')
			{
				output=output+"=";
			}
			if(grapevine[i]!='\00'&&grapevine[i]!='\24')
			output=output+grapevine[i];
		}
		output=output+"){\n";
	}
	//else if statement
	else if(grapevine[0]=='E'&&grapevine[1]=='L'&&grapevine[2]=='S'&&grapevine[3]=='E'&&grapevine[4]=='I'&&grapevine[5]=='F'&&grapevine[6]==' ')
	{
		output=output+"else if(";
		for(int i=7;i<grapevine.length(); i++)
		{
			if(grapevine[i]=='|')
			{
				output=output+"|";
			}
			if(grapevine[i]=='&')
			{
				output=output+"&";
			}
			if(grapevine[i]=='='&&grapevine[i-1]!='!')
			{
				output=output+"=";
			}
			if(grapevine[i]!='\00'&&grapevine[i]!='\24')
			output=output+grapevine[i];
		}
		output=output+"){\n";
	}
	//else statement
	else if(grapevine[0]=='E'&&grapevine[1]=='L'&&grapevine[2]=='S'&&grapevine[3]=='E')
	{
		output=output+"else";
		for(int i=5;i<grapevine.length(); i++)
		{
			if(grapevine[i]=='|')
			{
				output=output+"|";
			}
			if(grapevine[i]=='&')
			{
				output=output+"&";
			}
			if(grapevine[i]=='='&&grapevine[i-1]!='!')
			{
				output=output+"=";
			}
			if(grapevine[i]!='\00'&&grapevine[i]!='\24')
			output=output+grapevine[i];
		}
		output=output+"{\n";
	}
	//while statement
	else if(grapevine[0]=='W'&&grapevine[1]=='H'&&grapevine[2]=='I'&&grapevine[3]=='L'&&grapevine[4]=='E'&&grapevine[5]==' ')
	{
		output=output+"while(";
		for(int i=6;i<grapevine.length(); i++)
		{
			if(grapevine[i]=='|')
			{
				output=output+"|";
			}
			if(grapevine[i]=='&')
			{
				output=output+"&";
			}
			if(grapevine[i]=='='&&grapevine[i-1]!='!')
			{
				output=output+"=";
			}
			if(grapevine[i]!='\00'&&grapevine[i]!='\24')
			output=output+grapevine[i];
		}
		output=output+"){\n";
	}
	//wait command
	else if(grapevine[0]=='W'&&grapevine[1]=='A'&&grapevine[2]=='I'&&grapevine[3]=='T'&&grapevine[4]==' ')
	{
		output=output+"sleep(";
		for(int i=5; i<grapevine.length();i++)
		{
			if(grapevine[i]!='\00'&&grapevine[i]!='\24')
			{
				output=output+grapevine[i];
			}
		}
		output=output+");\n";
	}
	//line is a return
	else if(grapevine[0]=='T'&&grapevine[1]=='O'&&grapevine[2]=='S'&&grapevine[3]=='S'&&grapevine[4]==' ')
	{
		output=output+"return ";
		for(int i=5; i<grapevine.length();i++)
		{
			if(grapevine[i]!='\00'&&grapevine[i]!='\24')
			{
				output=output+grapevine[i];
			}
		}
		output=output+";\n";
	}
	//line is invalid
	else
	{
		cout<<"The following line is invalid: "<<grapevine<<endl;
		return "\n";
	}
	return output;
}
int main(int argc, char* argv[])
{
	//srand(time(NULL));
	//arg 1 = fileToCompile
	//arg 2 = filename
	//cout<<randomNumber()<<endl;
	//read .grapejuice
	cout<<"reading file..."<<endl;
	string line;
	vector<string> filetext;
	ifstream myfile (argv[1]);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			//cout << line << '\n';
			char tab='	';
			string newLine=remove_char(line,tab);
			cout<<newLine<<endl;
			filetext.push_back(newLine);
		}
		myfile.close();
		cout<<"read "<<filetext.size()<<" vines."<<endl;
	}
	else
	{
		cout << "Unable to read file"<<endl;
		return EXIT_FAILURE;
	}
	//we now have an array "filetext" with a line in each spot
	//create cpp file
	cout<<"creating header..."<<endl;
	ofstream cfile;
	cfile.open(argv[2]);
	cfile<<"#include <iostream>\n";
	cfile<<"#include <string>\n";
	cfile<<"#include <stdio.h>\n";
	cfile<<"#include <stdlib.h>\n";
	cfile<<"#include <time.h>\n";
	cfile<<"#include <cmath>\n";
	cfile<<"#include <unistd.h>\n";
	//sleep(seconds)
	cfile<<"using namespace std;\n";
	cfile<<"int RAND()\n";
	cfile<<"{\n";
	cfile<<"return rand()%256;\n";
	cfile<<"}\n";
	cfile<<"string RAND_char()\n";
	cfile<<"{\n";
	cfile<<"string letters[]={\"a\",\"b\",\"c\",\"d\",\"e\",\"f\",\"g\",\"h\",\"i\",\"j\",\"k\",\"l\",\"m\",\"n\",\"o\",\"p\",\"q\",\"r\",\"s\",\"t\",\"u\",\"v\",\"w\",\"x\",\"y\",\"z\"};\n";
	cfile<<"return letters[rand()%26];\n";
	cfile<<"}\n";
	cfile<<"template <typename UNSPEC>\n";
	cfile<<"void PRINT(UNSPEC output)\n";
	cfile<<"{\n";
	cfile<<"cout<<output;\n";
	cfile<<"}\n";
	cfile<<"void NL()\n";
	cfile<<"{\n";
	cfile<<"cout<<endl;\n";
	cfile<<"}\n";
	cfile<<"void BEEP()\n";
	cfile<<"{\n";
	cfile<<"cout<<'\\a';\n";
	cfile<<"}\n";
	cfile<<"string GET_string()\n";
	cfile<<"{\n";
	cfile<<"cout<<\"::\";\n";
	cfile<<"string output;\n";
	cfile<<"cin>>output;\n";
	cfile<<"return output;\n";
	cfile<<"}\n";
	cfile<<"float GET_float()\n";
	cfile<<"{\n";
	cfile<<"cout<<\"::\";\n";
	cfile<<"float output;\n";
	cfile<<"cin>>output;\n";
	cfile<<"return output;\n";
	cfile<<"}\n";
	cfile<<"void PAUSE()\n";
	cfile<<"{\n";
	cfile<<"cin.ignore();\n";
	cfile<<"}\n";
	cfile<<"char INT_TO_CHAR(int fromNumber)\n";
	cfile<<"{\n";
	cfile<<"return (char)fromNumber;\n";
	cfile<<"}\n";
	cfile<<"int CHAR_TO_INT(char fromChar)\n";
	cfile<<"{\n";
	cfile<<"return (int)fromChar;\n";
	cfile<<"}\n";
	int i=0;
	string workingline;
	string cppline="";
	//prepare functions
	cout<<"preparing functions..."<<endl;
	while(filetext[i]!="ENTRY"&&i<=filetext.size())
	{
		workingline=filetext[i];
		//if it's not a comment
		if(workingline[0]!='$')
		{
			//read type
			int c=1;
			while(c<=workingline.length()&&workingline[c]!=']')
			{
				cppline=cppline+workingline[c];
				c++;
			}
			cppline=cppline+" ";
			//skip F_
			c=c+3;
			while(c<=workingline.length()&&workingline[c]!=' ')
			{
				cppline=cppline+workingline[c];
				c++;
			}
			cppline=cppline+"(";
			while(c<=workingline.length())
			{
				c++;
				if(workingline[c]!='['&&workingline[c]!='\00')
				{
					if(workingline[c]==' ')
					{
						cppline=cppline+",";
					}
					else if(workingline[c]==']')
					{
						cppline=cppline+" ";
					}
					else
					{
						cppline=cppline+workingline[c];
					}
				}
			}
			cppline=cppline+"){";
			cfile<<cppline+"\n";
			i++;
			while(filetext[i]!="ENDDEF")
			{
				cfile<<createLine(filetext[i]);
				i++;
			}
			cfile<<"}\n";
		}
		i++;
	}
	i++;
	cout<<"writting main code..."<<endl;
	cfile<<"int main()\n";
	cfile<<"{\n";	
	cfile<<"srand(time(NULL));\n";
	//write main code
	for(i=i; i<filetext.size(); i++)
	{
		workingline=filetext[i];
		cfile<<createLine(workingline);
	}
	cfile<<"return 0;\n}";
	cfile.close();
	cout<<"done!"<<endl;
	return 0;
}
