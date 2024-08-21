%{
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include "parser.tab.h"

using namespace std;

std::stack<int> indentStk;
std::stack<int> impjoinStk;
int curr_indent = -1;
int done_flag = 0;

extern void yyerror(const char *message);

// int yylex();
// #define YY_DECL int orig_yylex(void)

%}

%option yylineno

%x EXPJOIN IMPJOIN
%x CHECKINDENTS CHECKDEDENTS DEDENTEOF

%%
<*>^[ \t]*"#".*\n  { /* cout << "COMMENT "; */ }
<INITIAL>^[ \t\v\r]*\n          {  /*cout << "empty LINE "; */ }    
<*><<EOF>>              {
                            
                             if(done_flag!=1) {
                                unput('$');
                                BEGIN(DEDENTEOF);                            
                            }
                            else{
                                                               
                                yyterminate();
                            }
                        }
<DEDENTEOF>"$"          {
                            // cout << "consumed$"    << endl;
                            if(indentStk.empty()){indentStk.push(0);}

                            while(indentStk.top()!=0){

                                indentStk.pop();
                                unput('$');
                                // cout << "DEDENT ";
                                return DEDENT;
                            }
                            if(indentStk.top()==0){
                                // cout << "ENDMARKER ";
                                done_flag = 1;
                                return ENDMARKER;
                                // return 0;
                            }
                        } 
<IMPJOIN>\n                 {}    
<IMPJOIN>\n[ \t]*           {/*cout <<"impjoin nl khaa gya\n";*/}
<IMPJOIN>^[ \t]*            {}
                   
<INITIAL>\n             { 
                            // cout << "nl\n";
                            BEGIN(CHECKINDENTS);

                            // cout << "NEWLINE\n";
                            
                            return NEWLINE;

                        }

<CHECKINDENTS>[ \t]*[^ \t\n\r\f\v] {
                            if(indentStk.empty()){indentStk.push(0);}

                            string temp = yytext;
                            int length = temp.length();

                            unput(temp[length-1]);
                            length = length-1;
                            
                            if(length > indentStk.top()){
                                indentStk.push(length);
                                BEGIN(INITIAL);

                                // cout << "INDENT ";
                                
                                return INDENT;

                            }
                            else if (length == indentStk.top()){
                                BEGIN(INITIAL);
                            }
                            else{
                                curr_indent = length;
                                unput('$');
                                BEGIN(CHECKDEDENTS);
                            }
}

<CHECKDEDENTS>"$"       {   
                            if(curr_indent < indentStk.top()){
                                indentStk.pop();
                                unput('$');
                                // cout << "DEDENT ";
                                return DEDENT;
                            }
                            else if(curr_indent == indentStk.top()){
                                curr_indent = -1;
                                BEGIN(INITIAL);
                            }
                            else{
                                cerr << "ERR indent ";
                                yyerror("Indentation fault");
                                BEGIN(INITIAL);
                            }
}


<INITIAL>\\[ \t]*\n   {BEGIN(EXPJOIN);}
<EXPJOIN>[ \t]*     {}
<EXPJOIN>\n         {BEGIN(INITIAL);}
<EXPJOIN>#.*           {}



<INITIAL,IMPJOIN>"("      {BEGIN(IMPJOIN); impjoinStk.push(1); /* cout << "LPAREN "; */ return LPAREN;}
<INITIAL,IMPJOIN>"["      {BEGIN(IMPJOIN); impjoinStk.push(1);/* cout << "LSQUARE "; */ return LSQUARE;}
<INITIAL,IMPJOIN>"{"      {BEGIN(IMPJOIN); impjoinStk.push(1); /* cout << "LCURLY "; */ return LCURLY;}

<INITIAL,IMPJOIN>")"      {
                    if(!impjoinStk.empty()){
                        impjoinStk.pop(); 
                        if(impjoinStk.empty()){
                            BEGIN(INITIAL);
                        }
                        else{
                            BEGIN(IMPJOIN);
                        }
                        return RPAREN;
                    }else{
                        yyerror("Unmatched paranthesis");
                    }
                    }
<INITIAL,IMPJOIN>"]"    {

                    if(!impjoinStk.empty()){
                        impjoinStk.pop(); 
                        if(impjoinStk.empty()){
                            BEGIN(INITIAL);
                        }
                        else{
                            BEGIN(IMPJOIN);
                        }
                        return RSQUARE;
                    }else{
                        yyerror("Unmatched Square brackets");
                    }
                    }
<INITIAL,IMPJOIN>"}"      {
                    if(!impjoinStk.empty()){
                        impjoinStk.pop(); 
                        if(impjoinStk.empty()){
                            BEGIN(INITIAL);
                        }
                        else{
                            BEGIN(IMPJOIN);
                        }
                        return RCURLY;
                    }else{
                        yyerror("Unmatched Curly brackets");
                    }
}

<INITIAL,IMPJOIN>","      { /* cout << "COMMA "; */ return COMMA; }
<INITIAL,IMPJOIN>":"      {  /*cout << "COLON "; */ return COLON; }
<INITIAL,IMPJOIN>";"      { /* cout << "SEMICOLON "; */ return SEMICOLON; }
<INITIAL,IMPJOIN>"->"     { /* cout << "RARR "; */ return RARR; }
<INITIAL,IMPJOIN>"@="     { /* cout << "AT_EQ "; */ return AT_EQ; }



<INITIAL,IMPJOIN>#.*                 {}
<INITIAL,IMPJOIN>"False"      {/* cout << "FALSE "; */ return FALSE;}
<INITIAL,IMPJOIN>"class"      {/* cout << "CLASS "; */ return CLASS;}
<INITIAL,IMPJOIN>"finally"    {/* cout << "FINALLY "; */ return FINALLY;}
<INITIAL,IMPJOIN>"is"         {/* cout << "IS "; */ return IS;}
<INITIAL,IMPJOIN>"return"     {/* cout << "RETURN "; */ return RETURN;}
<INITIAL,IMPJOIN>"None"       {/* cout << "NONE "; */ return NONE;}
<INITIAL,IMPJOIN>"continue"   {/* cout << "CONTINUE "; */ return CONTINUE;}
<INITIAL,IMPJOIN>"for"        {/* cout << "FOR "; */ return FOR;}
<INITIAL,IMPJOIN>"lambda"     {/* cout << "LAMBDA "; */ return LAMBDA;}
<INITIAL,IMPJOIN>"try"        {/* cout << "TRY "; */ return TRY;}
<INITIAL,IMPJOIN>"True"       {/* cout << "TRUE "; */ return TRUE;}
<INITIAL,IMPJOIN>"def"        {/* cout << "DEF "; */ return DEF;}
<INITIAL,IMPJOIN>"from"       {/* cout << "FROM "; */ return FROM;}
<INITIAL,IMPJOIN>"nonlocal"   {/* cout << "NONLOCAL "; */ return NONLOCAL;}
<INITIAL,IMPJOIN>"while"      {/* cout << "WHILE "; */ return WHILE;}
<INITIAL,IMPJOIN>"del"        {/* cout << "DEL "; */ return DEL;}
<INITIAL,IMPJOIN>"global"     {/* cout << "GLOBAL "; */ return GLOBAL;}
<INITIAL,IMPJOIN>"with"       {/* cout << "WITH "; */ return WITH;}
<INITIAL,IMPJOIN>"as"         {/* cout << "AS "; */ return AS;}
<INITIAL,IMPJOIN>"elif"       {/* cout << "ELIF "; */ return ELIF;}
<INITIAL,IMPJOIN>"if"         {/* cout << "IF "; */ return IF;}
<INITIAL,IMPJOIN>"yield"      {/* cout << "YIELD "; */ return YIELD;}
<INITIAL,IMPJOIN>"assert"     {/* cout << "ASSERT "; */ return ASSERT;}
<INITIAL,IMPJOIN>"else"       {/* cout << "ELSE "; */ return ELSE;}
<INITIAL,IMPJOIN>"import"     {/* cout << "IMPORT "; */ return IMPORT;}
<INITIAL,IMPJOIN>"pass"       {/* cout << "PASS "; */ return PASS;}
<INITIAL,IMPJOIN>"break"      {/* cout << "BREAK "; */ return BREAK;}
<INITIAL,IMPJOIN>"except"     {/* cout << "EXCEPT "; */ return EXCEPT;}
<INITIAL,IMPJOIN>"in"         {/* cout << "IN "; */ return IN;}
<INITIAL,IMPJOIN>"raise"      {/* cout << "RAISE "; */ return RAISE;}
<INITIAL,IMPJOIN>"async"      {/* cout << "ASYNC "; */ return ASYNC;}
<INITIAL,IMPJOIN>"await"      {/* cout << "AWAIT "; */ return AWAIT;}



<INITIAL,IMPJOIN>"range"      {/* cout << "AWAIT "; */ return RANGE;}
<INITIAL,IMPJOIN>"print"      {/* cout << "AWAIT "; */ return PRINT;}
<INITIAL,IMPJOIN>"len"      {/* cout << "AWAIT "; */ return LEN;}

 

<INITIAL,IMPJOIN>"__name__"   {std::string s=yytext; yylval.text=strdup(s.c_str()); return NAME;}
<INITIAL,IMPJOIN>"__main__"   {string s=yytext; yylval.text=strdup(s.c_str()); return NAME;}
<INITIAL,IMPJOIN>"__init__"   {string s=yytext; yylval.text=strdup(s.c_str()); return NAME;}

<INITIAL,IMPJOIN>"int"        {string s=yytext; yylval.text=strdup(s.c_str()); return INT;}
<INITIAL,IMPJOIN>"float"      {string s=yytext; yylval.text=strdup(s.c_str()); return FLOAT;}
<INITIAL,IMPJOIN>"str"        {string s=yytext; yylval.text=strdup(s.c_str()); return STR;}
<INITIAL,IMPJOIN>"bool"       {string s=yytext; yylval.text=strdup(s.c_str()); return BOOL;}
<INITIAL,IMPJOIN>"list"       {string s=yytext; yylval.text=strdup(s.c_str()); return LIST;}

<INITIAL,IMPJOIN>"+"          {/* cout << "PLUS "; */ return PLUS;}
<INITIAL,IMPJOIN>"-"          {/* cout << "MINUS "; */ return MINUS;}
<INITIAL,IMPJOIN>"*"          {/* cout << "ASTERISK "; */ return ASTERISK;}
<INITIAL,IMPJOIN>"**"         {/* cout << "DOUBLE_STAR "; */ return DOUBLE_STAR;}
<INITIAL,IMPJOIN>"/"          {/* cout << "FORWARDSLASH "; */ return FORWARDSLASH;}
<INITIAL,IMPJOIN>"//"         {/* cout << "DOUBLESLASH "; */ return DOUBLESLASH;}
<INITIAL,IMPJOIN>"%"          {/* cout << "PERCENT "; */ return PERCENT;}
<INITIAL,IMPJOIN>"=="         {/* cout << "EQ_EQ "; */ return EQ_EQ;}
<INITIAL,IMPJOIN>"!="         {/* cout << "NOT_EQ "; */ return NOT_EQ;}
<INITIAL,IMPJOIN>">"          {/* cout << "GT "; */ return GT;}
<INITIAL,IMPJOIN>"<"          {/* cout << "LT "; */ return LT;}
<INITIAL,IMPJOIN>">="         {/* cout << "GT_EQ "; */ return GT_EQ;}
<INITIAL,IMPJOIN>"<="         {/* cout << "LT_EQ "; */ return LT_EQ;}
<INITIAL,IMPJOIN>"and"        {/* cout << "AND "; */ return AND;}
<INITIAL,IMPJOIN>"or"         {/* cout << "OR "; */ return OR;}
<INITIAL,IMPJOIN>"not"        {/* cout << "NOT "; */ return NOT;}
<INITIAL,IMPJOIN>"="          {/* cout << "EQUALS ";*/ return EQUALS;}
<INITIAL,IMPJOIN>"+="         {/* cout << "PLUS_EQ "; */ return PLUS_EQ;}
<INITIAL,IMPJOIN>"-="         {/* cout << "MINUS_EQ "; */ return MINUS_EQ;}
<INITIAL,IMPJOIN>"*="         {/* cout << "STAR_EQ "; */ return STAR_EQ;}
<INITIAL,IMPJOIN>"/="         {/* cout << "FORWARDSLASH_EQ "; */ return FORWARDSLASH_EQ;}
<INITIAL,IMPJOIN>"//="        {/* cout << "DOUBLE_SLASH_EQ "; */ return DOUBLE_SLASH_EQ;}
<INITIAL,IMPJOIN>"%="         {/* cout << "PERCENT_EQ "; */ return PERCENT_EQ;}
<INITIAL,IMPJOIN>"**="        {/* cout << "DOUBLE_STAR_EQ "; */ return DOUBLE_STAR_EQ;}
<INITIAL,IMPJOIN>"&="         {/* cout << "AMPERSAND_EQ "; */ return AMPERSAND_EQ;}
<INITIAL,IMPJOIN>"|="         {/* cout << "PIPE_EQ "; */ return PIPE_EQ;}
<INITIAL,IMPJOIN>"^="         {/* cout << "CAP_EQ "; */ return CAP_EQ;}
<INITIAL,IMPJOIN>"<<="        {/* cout << "LT_LT_EQ "; */ return LT_LT_EQ;}
<INITIAL,IMPJOIN>">>="            {/* cout << "RT_RT_EQ "; */ return RT_RT_EQ;}
<INITIAL,IMPJOIN>"<>"            {/* cout << "LT_GT "; */ return LT_GT;}



<INITIAL,IMPJOIN>"&"          {/* cout << "AMPERSAND "; */ return AMPERSAND;}
<INITIAL,IMPJOIN>"|"          {/* cout << "BAR "; */ return BAR;}
<INITIAL,IMPJOIN>"^"          {/* cout << "CAP "; */ return CAP;}
<INITIAL,IMPJOIN>"~"          {/* cout << "TILDE "; */ return TILDE;}
<INITIAL,IMPJOIN>"<<"         {/* cout << "LT_LT "; */ return LT_LT;}
<INITIAL,IMPJOIN>">>"             {/* cout << "GT_GT "; */ return GT_GT;}
<INITIAL,IMPJOIN>"@"          {/* cout << "AT "; */ return AT;}



<INITIAL,IMPJOIN>([1-9][_0-9]*|0+[_0]*)   {string s=yytext; yylval.text=strdup(s.c_str()); return NUMBER_INT;}

<INITIAL,IMPJOIN>([0-9][_0-9]*"."[0-9][_0-9]*|[0-9][_0-9]*".")|(([0-9][_0-9]*|[0-9][_0-9]*"."[0-9][_0-9]*|[0-9][_0-9]*".")[eE][+-][0-9][_0-9]*)  {string s=yytext; yylval.text=strdup(s.c_str()); return NUMBER_FLOAT;}

<INITIAL,IMPJOIN>(([0-9][_0-9]*"."[0-9][_0-9]*|[0-9][_0-9]*".")|(([0-9][_0-9]*|[0-9][_0-9]*"."[0-9][_0-9]*|[0-9][_0-9]*".")[eE][+-][0-9][_0-9]*)|[0-9][_0-9]*)[jJ]   {string s=yytext; yylval.text=strdup(s.c_str()); return NUMBER;}


<INITIAL,IMPJOIN>"."      {/*cout << "DOT ";*/ return DOT;}
<INITIAL,IMPJOIN>"..."      {/*cout << "TRIPLE_DOT ";*/ return TRIPLE_DOT;}

<INITIAL,IMPJOIN>[a-zA-Z_][a-zA-Z_0-9]*   {string s=yytext; yylval.text=strdup(s.c_str()); return NAME; }


<INITIAL,IMPJOIN>\'(\\\'|[^'])*\'      {string s=yytext; yylval.text=strdup(s.c_str()); return STRING;}
<INITIAL,IMPJOIN>\"(\\\"|[^"])*\"      {string s=yytext; yylval.text=strdup(s.c_str()); return STRING;}
<INITIAL,IMPJOIN>\"\"\"(.|\n)*\"\"\"   {string s=yytext; yylval.text=strdup(s.c_str()); return STRING;}

<INITIAL,IMPJOIN>"'"|\"|\"\"\"   {cerr << "malformed string ";}

<INITIAL,IMPJOIN>[ \t\v\r]                  {}
<INITIAL,IMPJOIN>.                    {yyerror("Unrecognizable Token");}

%%

// string tokenToString(int token)
// {
//     switch(token){
//         case NEWLINE: return "NEWLINE";
//         case INDENT: return "INDENT";
//         case DEDENT: return "DEDENT";
//         case ENDMARKER: return "ENDMARKER";
//         default: return "UNKNOWN";
//     }

// }

// int yylex(){
//     cout << "yylex" << endl;
//     int token = orig_yylex();
//     cout << "token " << tokenToString(token) << " for: " << yytext << endl;
//     return token;
// }

int yywrap(){
    // cout << "yywrap "  << endl;
    return 1;
}
